#include "enemy.h"
#include <QRandomGenerator>
#include <QDebug>

Enemy::Enemy(QString name, int maxHp, Type type)
    : name(name)
    , type(type)
    , maxHp(maxHp)
    , currentHp(maxHp)
{
    // 根据敌人类型设置基础属性
    switch (type) {
    case Slime:
        baseAttackDamage = 6;
        break;
    case Goblin:
        baseAttackDamage = 8;
        break;
    case Cultist:
        baseAttackDamage = 5;
        break;
    case Sentinel:
        baseAttackDamage = 7;
        break;
    case Boss:
        baseAttackDamage = 10;
        break;
    }

    // 生成初始意图
    generateIntent();
}

void Enemy::generateIntent() {
    switch (type) {
    case Slime:
        generateSlimeIntent();
        break;
    case Goblin:
        generateGoblinIntent();
        break;
    case Cultist:
        generateCultistIntent();
        break;
    case Sentinel:
        generateSentinelIntent();
        break;
    case Boss:
        // BOSS可以有更复杂的意图
        nextIntent = (QRandomGenerator::global()->bounded(100) < 70) ? Attack : Block;
        intentValue = (nextIntent == Attack) ? 12 : 8;
        break;
    }
}

// 史莱姆：60%攻击，40%防御
void Enemy::generateSlimeIntent() {
    int roll = QRandomGenerator::global()->bounded(100);
    if (roll < 60) {
        nextIntent = Attack;
        intentValue = baseAttackDamage;
    } else {
        nextIntent = Block;
        intentValue = 6;
    }
}

// 哥布林：80%攻击，20%防御
void Enemy::generateGoblinIntent() {
    int roll = QRandomGenerator::global()->bounded(100);
    if (roll < 80) {
        nextIntent = Attack;
        intentValue = baseAttackDamage;
    } else {
        nextIntent = Block;
        intentValue = 4;
    }
}

// 邪教徒：50%攻击，30%增益，20%特殊
void Enemy::generateCultistIntent() {
    int roll = QRandomGenerator::global()->bounded(100);
    if (roll < 50) {
        nextIntent = Attack;
        intentValue = baseAttackDamage;
    } else if (roll < 80) {
        nextIntent = Buff;
        intentValue = 2;  // 增益值
    } else {
        nextIntent = Special;
        intentValue = 1;  // 特殊行动
    }
}

// 哨卫：40%攻击，60%防御
void Enemy::generateSentinelIntent() {
    int roll = QRandomGenerator::global()->bounded(100);
    if (roll < 40) {
        nextIntent = Attack;
        intentValue = baseAttackDamage;
    } else {
        nextIntent = Block;
        intentValue = 9;
    }
}

QString Enemy::getIntentDescription() const {
    switch (nextIntent) {
    case Attack:
        return QString("攻击：%1点伤害").arg(intentValue);
    case Block:
        return QString("防御：获得%1点格挡").arg(intentValue);
    case Buff:
        return QString("增益：强化自身");
    case Debuff:
        return QString("减益：削弱玩家");
    case Special:
        return QString("特殊行动");
    default:
        return "未知意图";
    }
}

void Enemy::takeDamage(int amount) {
    // 考虑易伤效果
    int actualDamage = amount;
    if (vulnerable > 0) {
        actualDamage = amount * 1.5;  // 易伤增加50%伤害
        qDebug() << name << "处于易伤状态，实际伤害:" << actualDamage;
    }

    int damage = actualDamage - block;
    if (damage > 0) {
        currentHp -= damage;
        if (currentHp < 0) currentHp = 0;
        qDebug() << name << "受到" << damage << "点伤害，剩余生命:" << currentHp;
    } else {
        qDebug() << name << "的格挡完全抵挡了伤害";
    }

    // 格挡被消耗
    block = 0;
}

void Enemy::gainBlock(int amount) {
    int actualBlock = calculateActualBlock(amount);
    block += actualBlock;
    qDebug() << name << "获得" << actualBlock << "点格挡，总格挡:" << block;
}

int Enemy::getAttackDamage() const {
    int damage = calculateActualDamage(intentValue);
    return damage;
}

void Enemy::addStatus(const QString& status, int value) {
    if (status == "vulnerable") {
        vulnerable += value;
        qDebug() << name << "获得" << value << "层易伤";
    } else if (status == "weak") {
        weak += value;
        qDebug() << name << "获得" << value << "层虚弱";
    } else if (status == "frail") {
        frail += value;
        qDebug() << name << "获得" << value << "层脆弱";
    }
}

void Enemy::endTurn() {
    // 减少状态层数
    if (vulnerable > 0) vulnerable--;
    if (weak > 0) weak--;
    if (frail > 0) frail--;

    qDebug() << name << "回合结束，状态层数 - 易伤:" << vulnerable
             << "虚弱:" << weak << "脆弱:" << frail;
}

int Enemy::calculateActualDamage(int baseDamage) const {
    int damage = baseDamage;

    // 虚弱效果：伤害-25%
    if (weak > 0) {
        damage = damage * 0.75;
    }

    return damage;
}

int Enemy::calculateActualBlock(int baseBlock) const {
    int block = baseBlock;

    // 脆弱效果：格挡-25%
    if (frail > 0) {
        block = block * 0.75;
    }

    return block;
}

QString Enemy::getStatusText() const {
    QStringList statuses;

    if (vulnerable > 0) statuses << QString("易伤%1").arg(vulnerable);
    if (weak > 0) statuses << QString("虚弱%1").arg(weak);
    if (frail > 0) statuses << QString("脆弱%1").arg(frail);

    if (statuses.isEmpty()) {
        return "无状态";
    }

    return statuses.join(" ");
}