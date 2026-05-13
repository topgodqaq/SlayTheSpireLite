#include "enemy.h"
#include <QRandomGenerator>
#include <QDebug>

// 构造函数，根据类型设置基础属性
Enemy::Enemy(QString name, int maxHp, Type type, const QString &imagePath)
    : name(name), type(type), maxHp(maxHp), currentHp(maxHp), imagePath(imagePath)
{
    if (this->imagePath.isEmpty())
    {
        switch (type)
        {
        case Slime_A:
            this->imagePath = "images/enemies/slime_a.png";
            break;
        case Slime_B:
            this->imagePath = "images/enemies/slime_b.png";
            break;
        case Cultist:
            this->imagePath = "images/enemies/cultist.png";
            break;
        case Sentinel:
            this->imagePath = "images/enemies/sentinel.png";
            break;
        case Boss:
            this->imagePath = "images/enemies/boss.png";
            break;
        }
    }

    // 根据敌人类型设置初始属性
    switch (type)
    {
    case Slime_A:
    case Slime_B:
        baseAttackDamage = 7;
        break;
    case Cultist:
        baseAttackDamage = 5;
        break;
    case Sentinel:
        baseAttackDamage = 7;
        artifact = 1; // 哨卫初始有1层人工制品
        break;
    case Boss:
        baseAttackDamage = 10;
        break;
    }

    // 生成初始意图
    generateIntent();
}

void Enemy::generateIntent()
{
    switch (type)
    {
    case Slime_A:
        generateSlimeAIntent();
        break;
    case Slime_B:
        generateSlimeBIntent();
        break;
    case Cultist:
        generateCultistIntent();
        break;
    case Sentinel:
        generateSentinelIntent();
        break;
    case Boss:
        // TODO：BOSS可以有更复杂的意图
        nextIntent = (QRandomGenerator::global()->bounded(100) < 70) ? Attack : Block;
        intentValue = (nextIntent == Attack) ? 12 : 8;
        break;
    }
}

// 史莱姆A：60%攻击 40%虚弱
void Enemy::generateSlimeAIntent()
{
    int roll = QRandomGenerator::global()->bounded(100);

    if (roll < 60)
    {
        // 60%概率：攻击
        nextIntent = Attack;
        intentValue = baseAttackDamage;
        intentTimes = 1;
    }
    else
    {
        // 40%概率：施加虚弱
        nextIntent = Debuff_Weak;
        intentValue = 2; // 2层虚弱
        intentTimes = 1;
    }
}

// 史莱姆B：60%攻击 40%易伤
void Enemy::generateSlimeBIntent()
{
    int roll = QRandomGenerator::global()->bounded(100);

    if (roll < 60)
    {
        // 60%概率：攻击
        nextIntent = Attack;
        intentValue = baseAttackDamage;
        intentTimes = 1;
    }
    else
    {
        // 40%概率：施加易伤
        nextIntent = Debuff_Vulnerable;
        intentValue = 2; // 2层易伤
        intentTimes = 1;
    }
}

// 邪教徒：第一回合增益，之后每回合攻击
void Enemy::generateCultistIntent()
{
    if (!ritualStarted)
    {
        // 第一回合：开始仪式
        nextIntent = Buff_RITUAL;
        qDebug("0");
        ritualLevel = 3; // 仪式值
        ritualStarted = true;
        return;
    }
    else
    {
        // 后续回合：攻击
        qDebug("3");
        processCultistRitual();
        nextIntent = Attack;
        intentValue = baseAttackDamage;
        intentTimes = 1;
        return;
    }
}

int Enemy::calculateActualDamage(int baseDamage) const
{
    int damage = baseDamage;

    // 虚弱效果：伤害-25%
    if (weak > 0)
    {
        damage = damage * 0.75;
    }

    return damage;
}

int Enemy::calculateActualBlock(int baseBlock) const
{
    int block = baseBlock;

    // 脆弱效果： 格挡值-25%
    if (frail > 0)
    {
        block = block * 0.75;
    }
    return block;
}

bool Enemy::isBuffIntent()
{
    if (nextIntent == Buff_RITUAL)
        return true;
    // TODO:添加更多buff
    return false;
}

// 处理邪教徒仪式
void Enemy::processCultistRitual()
{
    if (ritualLevel != 0)
    {
        strength += ritualLevel;
        qDebug() << name << "仪式增加" << ritualLevel << "点力量";
    }
}

// 哨卫：60%多段伤害40%单段伤害
void Enemy::generateSentinelIntent()
{
    int roll = QRandomGenerator::global()->bounded(100);

    if (roll < 60)
    {
        // 60%概率：多段攻击（3×5伤害）
        nextIntent = MultiAttack;
        intentValue = 5; // 每段伤害
        intentTimes = 3; // 攻击3次
    }
    else
    {
        // 40%概率：单段攻击
        nextIntent = Attack;
        intentValue = baseAttackDamage;
        intentTimes = 1;
    }
}

// 触发人工制品
void Enemy::triggerArtifact()
{
    if (artifact > 0)
    {
        artifact--;
        qDebug() << name << "的人工制品阻挡了一次负面效果";
    }
}

// 添加状态（考虑人工制品）
void Enemy::addStatus(const QString &status, int value)
{
    if (artifact > 0)
    {
        // 有人工制品，阻挡这次负面效果
        triggerArtifact();
        return;
    }

    if (status == "vulnerable")
    {
        vulnerable += value;
        qDebug() << name << "获得" << value << "层易伤";
    }
    else if (status == "weak")
    {
        weak += value;
        qDebug() << name << "获得" << value << "层虚弱";
    }
    else if (status == "frail")
    {
        frail += value;
        qDebug() << name << "获得" << value << "层脆弱";
    }
}

// 获取意图描述
QString Enemy::getIntentDescription() const
{
    switch (nextIntent)
    {
    case Attack:
        return QString("攻击：%1点伤害").arg(getAttackDamage());
    case MultiAttack:
        qDebug("2");
        return QString("多重攻击：%1×%2点伤害").arg(intentTimes).arg(getAttackDamage());
    case Block:
        return QString("防御：获得%1点格挡").arg(intentValue);
    case Buff_RITUAL:
        qDebug("1");
        return QString("获得%1点仪式").arg(ritualLevel);
    case Debuff_Weak:
        return QString("施加虚弱：%1层").arg(intentValue);
    case Debuff_Vulnerable:
        return QString("施加易伤：%1层").arg(intentValue);
    case Special:
        return QString("特殊行动");
    default:
        return "未知意图";
    }
}

void Enemy::endTurn()
{
    // 减少状态层数
    if (vulnerable > 0)
        vulnerable--;
    if (weak > 0)
        weak--;
    if (frail > 0)
        frail--;

    qDebug() << name << "回合结束，状态层数 - 易伤:" << vulnerable
             << "虚弱:" << weak << "脆弱:" << frail;
}

void Enemy::takeDamage(int amount)
{
    // 考虑易伤效果
    int actualDamage = amount;
    if (vulnerable > 0)
    {
        actualDamage = amount * 1.5; // 易伤增加50%伤害
        qDebug() << name << "处于易伤状态，实际伤害:" << actualDamage;
    }

    int damage = actualDamage - block;
    if (damage > 0)
    {
        currentHp -= damage;
        if (currentHp < 0)
            currentHp = 0;
        qDebug() << name << "受到" << damage << "点伤害，剩余生命:" << currentHp;
    }
    else
    {
        qDebug() << name << "的格挡完全抵挡了伤害";
    }

    // 格挡被消耗
    block = 0;
}

void Enemy::gainBlock(int amount)
{
    int actualBlock = calculateActualBlock(amount);
    block += actualBlock;
    qDebug() << name << "获得" << actualBlock << "点格挡，总格挡:" << block;
}

void Enemy::gainStrength(int amount)
{
    strength += amount;
    qDebug() << name << "获得" << amount << "点力量，总力量:" << strength;
}

// 计算实际攻击伤害（考虑力量和状态）
int Enemy::getAttackDamage() const
{
    int damage = intentValue;

    // 加上力量加成
    damage += strength;

    // 虚弱效果
    if (weak > 0)
    {
        damage = damage * 0.75;
    }

    return damage;
}

QString Enemy::getStatusText() const
{
    QString text = "";
    if (vulnerable > 0)
        text += QString("易伤:%1 ").arg(vulnerable);
    if (weak > 0)
        text += QString("虚弱:%1 ").arg(weak);
    if (frail > 0)
        text += QString("脆弱:%1 ").arg(frail);
    if (artifact > 0)
        text += QString("人工制品:%1 ").arg(artifact);
    return text;
}
