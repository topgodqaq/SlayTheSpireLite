#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include "card.h"
#include "enemy.h"

class Player {
public:
    // 构造
    Player(int maxHp = 80, int maxEnergy = 3);

    // 基础属性
    int getCurrentHp() const { return currentHp; }
    int getMaxHp() const { return maxHp; }
    int getBlock() const { return block; }
    int getEnergy() const { return currentEnergy; }
    int getMaxEnergy() const { return maxEnergy; }

    // 卡牌管理
    const QVector<Card>& getDeck() const { return deck; }
    const QVector<Card>& getHand() const { return hand; }

    // 战斗操作
    bool playCard(int cardIndex, int targetIndex, QVector<Enemy>& enemies);
    void endTurn();
    void startTurn();
    void drawCards(int count);

    // 状态变化
    void takeDamage(int amount);
    void takeDamage(int times, int amount);
    void gainBlock(int amount);
    void heal(int amount);
    void clearBlock();

    // 卡组操作
    void addCardToDeck(const Card& card);
    void removeCardFromDeck(int index);

    // 状态效果管理
    int getWeak() const { return weak; }          // 虚弱层数
    int getVulnerable() const { return vulnerable; } // 易伤层数
    int getFrail() const { return frail; }        // 脆弱层数
    void addStatus(const QString& status, int value);
    void endTurnStatusUpdate();  // 回合结束时更新状态层数

    // 计算实际效果
    int calculateActualDamage(int baseDamage) const;
    int calculateActualBlock(int baseBlock) const;
    int calculateDamageTaken(int baseDamage) const;

    //战斗前卡组准备
    void prepareForBattle();
    // 状态描述
    QString getStatusText() const;

    // 卡牌效果
    void applyCardEffect(const Card& card, int targetIndex, QVector<Enemy>& enemies);

private:
    // 基础属性
    int currentHp;
    int maxHp;
    int block = 0;
    int currentEnergy;
    int maxEnergy;

    // 状态效果
    int weak = 0;        // 虚弱：攻击伤害-25%
    int vulnerable = 0;  // 易伤：受到的伤害+50%
    int frail = 0;       // 脆弱：获得的格挡-25%

    // 卡牌集合
    QVector<Card> deck;      // 完整卡组
    QVector<Card> hand;      // 当前手牌
    QVector<Card> discard;   // 弃牌堆
    QVector<Card> drawPile;  // 抽牌堆

    void shuffleDrawPile();
};

#endif // PLAYER_H