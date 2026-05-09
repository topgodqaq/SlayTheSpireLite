#ifndef ENEMY_H
#define ENEMY_H

#include <QString>
#include <QVector>
#include <QMap>

class Enemy {
public:
    // 敌人类型
    enum Type {
        Slime,      // 史莱姆
        Goblin,     // 哥布林
        Cultist,    // 邪教徒
        Sentinel,   // 哨卫
        Boss        // BOSS
    };

    // 敌人意图
    enum Intent {
        Attack,     // 攻击
        Block,      // 防御
        Buff,       // 增益
        Debuff,     // 减益
        Special     // 特殊行动
    };

    Enemy(QString name = "未命名敌人", int maxHp = 30, Type type = Slime);

    // 基础属性
    QString getName() const { return name; }
    int getCurrentHp() const { return currentHp; }
    int getMaxHp() const { return maxHp; }
    int getBlock() const { return block; }
    Type getType() const { return type; }

    // 意图系统
    Intent getNextIntent() const { return nextIntent; }
    QString getIntentDescription() const;
    int getIntentValue() const { return intentValue; }
    void generateIntent();  // 生成下回合意图

    // 战斗操作
    void takeDamage(int amount);
    void gainBlock(int amount);
    bool isAlive() const { return currentHp > 0; }

    // 状态效果
    int getVulnerable() const { return vulnerable; }
    int getWeak() const { return weak; }
    int getFrail() const { return frail; }
    void addStatus(const QString& status, int value);
    void endTurn();  // 回合结束时减少状态层数

    // 属性操作
    void setAttackDamage(int damage) { baseAttackDamage = damage; }
    int getAttackDamage() const;

    // 文本描述
    QString getStatusText() const;

private:
    // 基础属性
    QString name;
    Type type;
    int maxHp;
    int currentHp;
    int block = 0;

    // 攻击属性
    int baseAttackDamage = 6;

    // 状态效果
    int vulnerable = 0;  // 易伤：受到的伤害+50%
    int weak = 0;        // 虚弱：造成的伤害-25%
    int frail = 0;       // 脆弱：获得的格挡-25%

    // 意图系统
    Intent nextIntent = Attack;
    int intentValue = 0;  // 意图数值（攻击伤害、格挡值等）

    // 计算实际属性（考虑状态影响）
    int calculateActualDamage(int baseDamage) const;
    int calculateActualBlock(int baseBlock) const;

    // 根据类型生成意图
    void generateSlimeIntent();
    void generateGoblinIntent();
    void generateCultistIntent();
    void generateSentinelIntent();
};

#endif // ENEMY_H