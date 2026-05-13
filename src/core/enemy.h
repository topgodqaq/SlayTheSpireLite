#ifndef ENEMY_H
#define ENEMY_H

#include <QString>
#include <QVector>

class Enemy
{
public:
    // 敌人类型
    enum Type
    {
        Slime_A,  // 史莱姆A（虚弱型）
        Slime_B,  // 史莱姆B（易伤型）
        Cultist,  // 邪教徒（仪式机制）
        Sentinel, // 哨卫（人工制品）
        Boss      // BOSS
    };

    // 敌人意图（将 Intent 和 Debuff 合并）
    enum Intent
    {
        // 基础行动
        Attack,      // 攻击
        MultiAttack, // 多段攻击
        Block,       // 防御
        Buff_RITUAL, // 增益

        // Debuff 类型
        Debuff_Weak,       // 给予玩家虚弱
        Debuff_Vulnerable, // 给予玩家易伤
        Debuff_Frail,      // 给予玩家脆弱

        Special // 特殊行动
    };

    Enemy(QString name = "未命名敌人", int maxHp = 30, Type type = Slime_A, const QString &imagePath = QString());

    // 基础属性
    QString getName() const { return name; }
    int getCurrentHp() const { return currentHp; }
    QString getImagePath() const { return imagePath; }
    int getMaxHp() const { return maxHp; }
    int getBlock() const { return block; }
    Type getType() const { return type; }
    bool hasArtifact() const { return artifact > 0; } // 是否有人工制品

    // 意图系统
    Intent getNextIntent() const { return nextIntent; }
    QString getIntentDescription() const;
    int getIntentValue() const { return intentValue; }
    int getIntentTimes() const { return intentTimes; }
    void generateIntent(); // 生成下回合意图

    // 辅助方法
    bool isAttackIntent() const { return nextIntent == Attack; }
    bool isBlockIntent() const { return nextIntent == Block; }
    bool isBuffIntent();
    bool isDebuffIntent() const; // 判断是否是debuff意图
    bool isSpecialIntent() const { return nextIntent == Special; }
    QString getDebuffType() const;

    // 战斗操作
    void takeDamage(int amount);
    void gainBlock(int amount);
    bool isAlive() const { return currentHp > 0; }
    void gainStrength(int amount);

    // 邪教徒仪式系统
    void processCultistRitual();
    bool isRitual() { return ritualLevel > 0; }

    // 状态效果
    int getVulnerable() const { return vulnerable; }
    int getWeak() const { return weak; }
    int getFrail() const { return frail; }
    void addStatus(const QString &status, int value);
    void reduceArtifact() { artifact--; }
    void endTurn(); // 回合结束时减少状态层数

    // 属性操作
    void setAttackDamage(int damage) { baseAttackDamage = damage; }
    int getAttackDamage() const;

    // 文本描述
    QString getStatusText() const;

    // 特殊机制
    void triggerArtifact(); // 触发人工制品

private:
    // 基础属性
    QString name;
    Type type;
    int maxHp;
    int currentHp;
    int block = 0;
    int strength = 0; // 力量
    int artifact = 0; // 人工制品层数

    // 攻击属性
    int baseAttackDamage = 6;
    int intentTimes = 1; // 攻击次数（用于多段攻击）

    // 状态效果
    int vulnerable = 0; // 易伤：受到的伤害+50%
    int weak = 0;       // 虚弱：造成的伤害-25%
    int frail = 0;      // 脆弱：获得的格挡-25%
    QString imagePath;

    // 意图系统
    Intent nextIntent = Attack;
    int intentValue = 0; // 意图数值（攻击伤害、格挡值、仪式层数等）

    // 邪教徒仪式
    int ritualLevel = 0;        // 仪式计数
    bool ritualStarted = false; // 仪式是否开始

    // 计算实际属性（考虑状态影响）
    int calculateActualDamage(int baseDamage) const;
    int calculateActualBlock(int baseBlock) const;

    // 根据类型生成意图
    void generateSlimeAIntent();   // 史莱姆A：60%攻击 40%虚弱
    void generateSlimeBIntent();   // 史莱姆B：60%攻击 40%易伤
    void generateCultistIntent();  // 邪教徒：仪式系统
    void generateSentinelIntent(); // 哨卫：60%多段 40%单段
    void generateBossIntent();     // BOSS
};

#endif // ENEMY_H