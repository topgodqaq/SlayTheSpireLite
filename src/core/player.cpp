#include "player.h"
#include <QRandomGenerator>
#include <QDebug>

Player::Player(int maxHP, int maxEnergy)
    : currentHp (maxHP)
    , maxHp (maxHP)
    , currentEnergy (maxEnergy)
    , maxEnergy (maxEnergy)
{
    //初始化卡组
    for (int i = 0; i < 5; i++) {
        deck.append(Card("strike", "打击", Card::Attack, 1, 6));
    }
    for (int i = 0; i < 4; i++) {
        deck.append(Card("defend", "防御", Card::Skill, 1, 5));
    }
    //TODO:痛击效果怎么做？
    deck.append(Card("bash", "痛击", Card::Attack, 2, 8));
}

//打乱抽牌堆
void Player::shuffleDrawPile() {
    for (int i = drawPile.size() - 1; i > 0; i--) {
        int j = QRandomGenerator::global()->bounded(i + 1);
        qSwap(drawPile[i], drawPile[j]);
    }
}

void Player::drawCards(int count) {
    for (int i = 0; i < count; i++) {
        if(drawPile.isEmpty()){
            if(discard.isEmpty()){
                break;
            }
            drawPile = discard;
            discard.clear();
            shuffleDrawPile();

            if (drawPile.isEmpty()){
                break;
            }
        }

        if(!drawPile.isEmpty()){
            hand.append(drawPile.takeFirst());
        }
    }
}

bool Player::playCard (int cardIndex, int targetIndex) {
    if (cardIndex < 0 || cardIndex >= hand.size()) return false;
    Card& card = hand[cardIndex];

    if (!card.canPlay(currentEnergy)) return false;

    currentEnergy -= card.cost;

    //TODO:卡牌效果没实现

    // if (card.id == "bash") {
    //     // 1. 造成伤害
    //     enemies[targetIndex].takeDamage(card.value);  // 8点伤害

    //     // 2. 给予易伤效果
    //     enemies[targetIndex].addStatus("vulnerable", 2);  // 2层易伤
    // }

    discard.append(card);
    hand.removeAt(cardIndex);

    return true;
}

void Player::endTurn() {
    //弃手牌格挡值归零
    discard.append(hand);
    hand.clear();
    //block = 0;
}

void Player::startTurn() {
    currentEnergy = maxEnergy;
    drawCards(5);
}

void Player::takeDamage(int amount) {
    int damage = amount - block;
    if (damage > 0) {
        currentHp -= damage;
        qDebug() << "-"<<damage;
        if (currentHp < 0) currentHp = 0;
        block = 0;
    }
    else block = block - amount;
}

void Player::takeDamage(int times, int amount) {
    for (int i = 0; i < times; i++) {
        takeDamage(amount);
    }
}

void Player::gainBlock(int amount) {
    block += amount;
}

void Player::heal (int amount) {
    currentHp += amount;
    if (currentHp > maxHp) currentHp = maxHp;
}

void Player::addCardToDeck(const Card& card) {
    deck.append(card);

}

void Player::removeCardFromDeck(int index) {
    // 检查索引有效性
    if (index < 0 || index >= deck.size()) {
        return;
    }

    // 从卡组中移除
    deck.removeAt(index);
}

void Player::prepareForBattle() {
    // 1. 清空所有卡牌区域
    hand.clear();
    discard.clear();
    drawPile.clear();

    // 2. 重置抽牌堆为完整卡组
    drawPile = deck;

    // 3. 洗牌
    shuffleDrawPile();

    // 4. 抽起始手牌
    drawCards(5);

    // 5. 重置战斗状态
    block = 0;
    currentEnergy = maxEnergy;
}
























