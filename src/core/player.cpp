#include "player.h"
#include <QRandomGenerator>
#include <QDebug>

Player::Player(int maxHP, int maxEnergy)
    : currentHp(maxHP)
    , maxHp(maxHP)
    , currentEnergy(maxEnergy)
    , maxEnergy(maxEnergy)
{
    // 初始化卡组
    for (int i = 0; i < 5; i++) {
        deck.append(Card("strike", "打击", Card::Attack, 1, 6));
    }
    for (int i = 0; i < 4; i++) {
        deck.append(Card("defend", "防御", Card::Skill, 1, 5));
    }
    // 痛击卡
    deck.append(Card("bash", "痛击", Card::Attack, 2, 8));
}

// 打乱抽牌堆
void Player::shuffleDrawPile() {
    for (int i = drawPile.size() - 1; i > 0; i--) {
        int j = QRandomGenerator::global()->bounded(i + 1);
        qSwap(drawPile[i], drawPile[j]);
    }
}

void Player::drawCards(int count) {
    for (int i = 0; i < count; i++) {
        if (drawPile.isEmpty()) {
            if (discard.isEmpty()) {
                break;
            }
            drawPile = discard;
            discard.clear();
            shuffleDrawPile();

            if (drawPile.isEmpty()) {
                break;
            }
        }

        if (!drawPile.isEmpty()) {
            hand.append(drawPile.takeFirst());
        }
    }
}

bool Player::playCard(int cardIndex, int targetIndex, QVector<Enemy>& enemies) {
    if (cardIndex < 0 || cardIndex >= hand.size()) return false;
    Card& card = hand[cardIndex];

    if (!card.canPlay(currentEnergy)) return false;

    currentEnergy -= card.cost;

    // 应用卡牌效果
    applyCardEffect(card, targetIndex, enemies);

    discard.append(card);
    hand.removeAt(cardIndex);

    return true;
}

void Player::applyCardEffect(const Card& card, int targetIndex, QVector<Enemy>& enemies) {
    qDebug() << "打出卡牌:" << card.name;

    if (card.id == "strike") {
        // 计算实际伤害（考虑虚弱效果）
        int actualDamage = calculateActualDamage(card.value);
        if (targetIndex >= 0 && targetIndex < enemies.size()) {
            enemies[targetIndex].takeDamage(actualDamage);
            qDebug() << "造成" << actualDamage << "点伤害（基础伤害" << card.value << "）";
        }
    }
    else if (card.id == "defend") {
        // 计算实际格挡（考虑脆弱效果）
        int actualBlock = calculateActualBlock(card.value);
        gainBlock(actualBlock);
        qDebug() << "获得" << actualBlock << "点格挡（基础格挡" << card.value << "）";
    }
    else if (card.id == "bash") {
        // 痛击：造成伤害并给予易伤
        int actualDamage = calculateActualDamage(card.value);
        if (targetIndex >= 0 && targetIndex < enemies.size()) {
            enemies[targetIndex].takeDamage(actualDamage);
            // 给予敌人2层易伤
            enemies[targetIndex].addStatus("vulnerable", 2);
            qDebug() << "痛击造成" << actualDamage << "点伤害，并给予2层易伤";
        }
    }
}

void Player::endTurn() {
    // 弃掉手牌
    discard.append(hand);
    hand.clear();

    // 更新状态层数
    endTurnStatusUpdate();
}

void Player::endTurnStatusUpdate() {
    // 减少状态层数
    if (weak > 0) weak--;
    if (vulnerable > 0) vulnerable--;
    if (frail > 0) frail--;

    qDebug() << "回合结束，状态层数更新 - 虚弱:" << weak
             << "易伤:" << vulnerable << "脆弱:" << frail;
}

void Player::startTurn() {
    currentEnergy = maxEnergy;
    drawCards(5);
}

void Player::takeDamage(int amount) {
    // 计算实际受到的伤害（考虑易伤效果）
    int actualDamage = calculateDamageTaken(amount);
    qDebug() << "受到" << amount << "点伤害，实际伤害" << actualDamage;

    int damage = actualDamage - block;
    if (damage > 0) {
        currentHp -= damage;
        if (currentHp < 0) currentHp = 0;
        qDebug() << "实际扣血" << damage << "点，剩余生命" << currentHp;
    } else {
        qDebug() << "格挡完全抵挡了伤害";
    }

    block = 0;  // 格挡被消耗
}

void Player::takeDamage(int times, int amount) {
    qDebug() << "受到" << times << "段攻击，每段" << amount << "点伤害";
    for (int i = 0; i < times; i++) {
        int actualDamage = calculateDamageTaken(amount);
        int damage = actualDamage - block;

        if (damage > 0) {
            currentHp -= damage;
            if (currentHp < 0) currentHp = 0;
        }

        block = 0;  // 第一段攻击就消耗完所有格挡
        break;      // 后续攻击直接扣血
    }
}

void Player::gainBlock(int amount) {
    int actualBlock = calculateActualBlock(amount);
    block += actualBlock;
    qDebug() << "获得" << actualBlock << "点格挡（基础" << amount << "点），总格挡" << block;
}

void Player::heal(int amount) {
    currentHp += amount;
    if (currentHp > maxHp) currentHp = maxHp;
    qDebug() << "治疗" << amount << "点生命，剩余生命" << currentHp;
}

void Player::addCardToDeck(const Card& card) {
    deck.append(card);
}

void Player::removeCardFromDeck(int index) {
    if (index < 0 || index >= deck.size()) {
        return;
    }
    deck.removeAt(index);
}

void Player::prepareForBattle() {
    // 清空所有卡牌区域
    hand.clear();
    discard.clear();
    drawPile.clear();

    // 重置抽牌堆为完整卡组
    drawPile = deck;

    // 洗牌
    shuffleDrawPile();

    // 抽起始手牌
    drawCards(5);

    // 重置战斗状态
    block = 0;
    currentEnergy = maxEnergy;

    // 重置状态效果
    weak = 0;
    vulnerable = 0;
    frail = 0;
}

// 计算实际攻击伤害（考虑虚弱效果）
int Player::calculateActualDamage(int baseDamage) const {
    int damage = baseDamage;

    // 虚弱效果：攻击伤害-25%（每层）
    if (weak > 0) {
        damage = damage * 0.75;
        qDebug() << "虚弱效果：攻击伤害减少25%，实际伤害" << damage;
    }

    return damage;
}

// 计算实际格挡（考虑脆弱效果）
int Player::calculateActualBlock(int baseBlock) const {
    int block = baseBlock;

    // 脆弱效果：获得的格挡-25%（每层）
    if (frail > 0) {
        block = block * 0.75;
        qDebug() << "脆弱效果：格挡减少25%，实际格挡" << block;
    }

    return block;
}

// 计算实际受到的伤害（考虑易伤效果）
int Player::calculateDamageTaken(int baseDamage) const {
    int damage = baseDamage;

    // 易伤效果：受到的伤害+50%（每层）
    if (vulnerable > 0) {
        damage = damage * 1.5;
        qDebug() << "易伤效果：受到的伤害增加50%，实际伤害" << damage;
    }

    return damage;
}

// 添加状态效果
void Player::addStatus(const QString& status, int value) {
    if (status == "weak") {
        weak += value;
        qDebug() << "获得" << value << "层虚弱，总层数" << weak;
    } else if (status == "vulnerable") {
        vulnerable += value;
        qDebug() << "获得" << value << "层易伤，总层数" << vulnerable;
    } else if (status == "frail") {
        frail += value;
        qDebug() << "获得" << value << "层脆弱，总层数" << frail;
    }
}

// 获取状态描述文本
QString Player::getStatusText() const {
    QStringList statuses;

    if (weak > 0) statuses << QString("虚弱%1").arg(weak);
    if (vulnerable > 0) statuses << QString("易伤%1").arg(vulnerable);
    if (frail > 0) statuses << QString("脆弱%1").arg(frail);

    if (statuses.isEmpty()) {
        return "无状态";
    }

    return statuses.join(" ");
}