#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
class Player
{
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
    bool playCard(int cardIndex, int targetIndex = 0);
    void endTurn();
    void startTurn();
    void drawCards(int count);

    // 状态变化
    void takeDamage(int amount);
    void takeDamage(int times, int amount);
    void gainBlock(int amount);
    void heal(int amount);

    // 卡组操作
    void addCardToDeck(const Card& card);
    void removeCardFromDeck(int index);

    //准备战斗
    void prepareForBattle();

private:
    int currentHp;
    int maxHp;
    int block = 0;           //格挡值
    int currentEnergy;
    int maxEnergy;

    // 卡牌集合
    QVector<Card> deck;      // 完整卡组
    QVector<Card> hand;      // 当前手牌
    QVector<Card> discard;   // 弃牌堆
    QVector<Card> drawPile;  // 抽牌堆

    void shuffleDrawPile();
};

#endif // PLAYER_H
