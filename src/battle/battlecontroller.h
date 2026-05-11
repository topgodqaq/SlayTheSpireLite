#ifndef BATTLECONTROLLER_H
#define BATTLECONTROLLER_H

#include <QObject>
#include <QVector>
#include "src/core/player.h"
#include "src/core/enemy.h"

class BattleController : public QObject
{
    Q_OBJECT
public:
    // 战斗状态
    enum BattleState {
        NotStarted,     // 未开始
        PlayerTurn,     // 玩家回合
        EnemyTurn,      // 敌人回合
        PlayerWon,      // 玩家胜利
        PlayerLost,     // 玩家失败
        BattleEnd       // 战斗结束
    };

    explicit BattleController(QObject *parent = nullptr);

    //战斗管理
    void startBattle(const QVector<Enemy>& initialEnemies);
    void endBattle();

    //获取状态
    BattleState getState() const {return state;}
    Player& getPlayer() {return player;}
    QVector<Enemy> getEnemies() {return enemies;}

    //玩家接口
    bool playCard(int cardIndex, int targetIndex);
    void endTurn();

    //辅助函数
    bool isPlayerAlive() const {return player.getCurrentHp() > 0;}
    bool areEnemiesAlive() const;
    int getAliveEnemiesAlive() const;
    int getAliveEnemyCount() const;

signals:
    // 状态变化信号
    void battleStateChanged(BattleState newState);
    void battleStarted(const QVector<Enemy>& enemies);
    void battleEnded(bool playerWon);

    // 玩家状态信号
    void playerHealthChanged(int current, int max);
    void playerEnergyChanged(int current, int max);
    void playerBlockChanged(int block);
    void playerStatusChanged(const QString& status);

    // 敌人状态信号
    void enemyHealthChanged(int index, int current, int max);
    void enemyIntentChanged(int index, const QString& intent, int value);

    // 卡牌相关信号
    void cardPlayed(int cardIndex, int targetIndex);
    void handChanged(const QVector<Card>& hand);
    void deckInfoChanged(int deckSize, int discardSize, int drawPileSize);

    // 回合信号
    void playerTurnStarted();
    void enemyTurnStarted();
    void turnEnded();

    // 战斗信息信号
    void battleLog(const QString& message);
private:
    BattleState state = NotStarted;
    Player player;
    QVector<Enemy> enemies;

    // 私有方法
    void processEnemyTurns();
    void processEnemyIntent(Enemy& enemy);
    void checkBattleEnd();
    void updateUI();
    void log(const QString& message);

    // 战斗计数器
    int currentTurn = 0;
};

#endif // BATTLECONTROLLER_H
