#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QColor>

class Card
{
public:
    //卡牌类型
    enum Type {
        Attack,   //攻击
        Skill,    //技能
        Power     //能力
    };

    //稀有度
    enum Rarity {
        Basic,    //基础
        Common,   //普通
        Uncommon, //罕见
        Rare      //稀有
    };

    Card(const QString& id = "",
         const QString& name = "",
         Type type = Attack,
         int cost = 1,
         int value = 0,
         const QString& description = "",
         Rarity rarity = Common,
         bool isupgrade = false);

    QString id;          // 唯一标识
    QString name;        // 卡牌名称
    QString description; // 描述文本
    Type type;           // 卡牌类型
    Rarity rarity;       // 稀有度
    int cost;            // 能量消耗
    int value;           // 基础数值（伤害/格挡等）
    bool isupgrade;      //是否升级

    bool canPlay(int energy) const;
    QString getTypeString() const;
    QColor getTypeColor() const;

    // 卡牌升级
    bool upgrade();
private:
    int upgradedValue = 0;
};

#endif // CARD_H
