#include "card.h"
Card::Card(const QString& id,
           const QString& name,
           Type type,
           int cost,
           int value,
           const QString& description,
           Rarity rarity,
           bool isupgrade,
           const QString& imagePath)
    : id(id)
    , name(name)
    , type(type)
    , rarity(rarity)
    , cost(cost)
    , value(value)
    , isupgrade(isupgrade)
    , imagePath(imagePath)
{
    // 如果未提供描述，生成默认描述
    if (description.isEmpty()) {
        switch (type) {
        case Attack:
            this->description = QString("造成 %1 点伤害").arg(value);
            break;
        case Skill:
            this->description = QString("获得 %1 点格挡").arg(value);
            break;
        case Power:
            this->description = "获得特殊效果";
            break;
        }
    } else {
        this->description = description;
    }
}

bool Card::canPlay(int energy) const {
    return cost <= energy;
}

QString Card::getTypeString() const {
    static const char* typeNames[] = {"攻击", "技能", "能力"};
    return typeNames[type];
}

QColor Card::getTypeColor() const {
    // 根据卡牌类型返回不同颜色
    static QColor colors[] = {
        QColor(220, 50, 50),    // 攻击 - 红色
        QColor(50, 120, 220),   // 技能 - 蓝色
        QColor(180, 50, 220)    // 能力 - 紫色
    };
    return colors[type];
}

bool Card::upgrade() {
    if (!isupgrade) {
        // 基础升级逻辑
        switch (type) {
        case Attack:
            upgradedValue = value + 3;
            description = QString("造成 %1 点伤害").arg(upgradedValue);
            break;
        case Skill:
            upgradedValue = value + 3;
            description = QString("获得 %1 点格挡").arg(upgradedValue);
            break;
        case Power:
            // 能力卡不增加数值，只改进描述
            description += "（已升级）";
            break;
        }
        isupgrade = true;
        return true;
    }
    return false;
}