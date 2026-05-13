#include "battlecontroller.h"
#include <QDebug>
#include <QRandomGenerator>

BattleController::BattleController(QObject *parent)
    : QObject{parent}
{
}

void BattleController::startBattle(const QVector<Enemy> &initialEnemies)
{
    if (state != NotStarted && state != BattleEnd)
    {
        log("处于战斗中，无法开始新战斗");
        return;
    }

    state = PlayerTurn;
    currentTurn = 1;

    enemies = initialEnemies;

    player.prepareForBattle();

    emit battleStarted(enemies);
    emit playerTurnStarted();
    updateUI();
}

void BattleController::endBattle()
{
    if (state == BattleEnd)
    {
        log("战斗已经处于结束状态");
        return;
    }

    bool playerWon = (state == PlayerWon);
    state = BattleEnd;

    log(playerWon ? "战斗胜利！" : "战斗失败...");
    emit battleEnded(playerWon);
    emit battleStateChanged(state);
}

bool BattleController::playCard(int cardIndex, int targetIndex)
{
    if (state != PlayerTurn)
    {
        log("不是你的回合！");
        return false;
    }

    const QVector<Card> &hand = player.getHand();
    if (cardIndex < 0 || cardIndex >= hand.size())
    {
        log("请选择有效卡牌！");
        return false;
    }

    const Card &card = hand[cardIndex];
    if (card.type == Card::Attack)
    {
        if (targetIndex < 0 || targetIndex >= enemies.size())
        {
            log("请选择有效目标！");
            return false;
        }
        if (!enemies[targetIndex].isAlive())
        {
            log("目标已死亡！");
            return false;
        }
    }

    bool success = player.playCard(cardIndex, targetIndex, enemies);

    if (success)
    {
        if (card.type == Card::Attack && targetIndex >= 0 && targetIndex < enemies.size())
        {
            log(QString("成功打出卡牌，目标：%1").arg(enemies[targetIndex].getName()));
            emit cardPlayed(cardIndex, targetIndex);
        }
        else
        {
            log(QString("成功打出卡牌：%1").arg(card.name));
            emit cardPlayed(cardIndex, -1);
        }

        // 检测敌人是否死亡
        for (int i = enemies.size() - 1; i >= 0; i--)
        {
            if (!enemies[i].isAlive())
            {
                log(QString("%1 被击败了！").arg(enemies[i].getName()));
                enemies.removeAt(i);
                emit enemyHealthChanged(i, 0, 0);
            }
        }

        emit handChanged(player.getHand());

        checkBattleEnd();
    }
    else
    {
        log("无法打出卡牌（能量不足或无效卡牌）");
    }
    return success;
}

void BattleController::endTurn()
{
    if (state != PlayerTurn)
    {
        log("现在不是你的回合，无法结束回合");
        return;
    }

    log("玩家结束回合");

    player.endTurn();

    state = EnemyTurn;
    currentTurn++;

    emit turnEnded();
    emit enemyTurnStarted();
    emit battleStateChanged(state);

    processEnemyTurns();

    if (state == EnemyTurn)
    {
        state = PlayerTurn;

        player.startTurn();

        for (Enemy &enemy : enemies)
        {
            enemy.generateIntent();
        }

        log(QString("第%1回合开始").arg(currentTurn));
        emit playerTurnStarted();
        emit battleStateChanged(state);
    }

    updateUI();
    checkBattleEnd();
}

void BattleController::processEnemyTurns()
{
    if (state != EnemyTurn)
        return;
    log("敌人回合开始");

    for (int i = 0; i < enemies.size(); i++)
    {
        Enemy &enemy = enemies[i];

        if (!enemy.isAlive())
            continue;

        log(QString("%1 的回合").arg(enemy.getName()));
        processEnemyIntent(enemy);

        if (!isPlayerAlive())
        {
            state = PlayerLost;
            log("玩家被击败了！");
            emit battleEnded(false);
            endBattle();
            return;
        }
    }

    player.clearBlock();

    for (Enemy &enemy : enemies)
    {
        enemy.endTurn();
    }
}

void BattleController::processEnemyIntent(Enemy &enemy)
{
    switch (enemy.getNextIntent())
    {
    case Enemy::Attack:
    {
        int damage = enemy.getAttackDamage();
        log(QString("%1 攻击玩家，造成 %2 点伤害").arg(enemy.getName()).arg(damage));
        player.takeDamage(damage);
        emit playerHealthChanged(player.getCurrentHp(), player.getMaxHp());
        break;
    }

    case Enemy::MultiAttack:
    {
        int damage = enemy.getAttackDamage();
        int times = enemy.getIntentTimes();
        log(QString("%1 进行%2段攻击，每段%3点伤害").arg(enemy.getName()).arg(times).arg(damage));

        player.takeDamage(times, damage);
        emit playerHealthChanged(player.getCurrentHp(), player.getMaxHp());
        break;
    }

    case Enemy::Debuff_Weak:
    {
        int value = enemy.getIntentValue();
        log(QString("%1 给予玩家 %2 层虚弱").arg(enemy.getName()).arg(value));
        player.addStatus("weak", value);
        emit playerStatusChanged(player.getStatusText());
        break;
    }

    case Enemy::Debuff_Vulnerable:
    {
        int value = enemy.getIntentValue();
        log(QString("%1 给予玩家 %2 层易伤").arg(enemy.getName()).arg(value));
        player.addStatus("vulnerable", value);
        emit playerStatusChanged(player.getStatusText());
        break;
    }

    case Enemy::Buff_RITUAL:
    {
        enemy.processCultistRitual();
        break;
    }
    }
}

void BattleController::checkBattleEnd()
{
    if (state == PlayerWon || state == PlayerLost)
    {
        return; // 已经结束
    }

    // 检查玩家是否死亡
    if (!isPlayerAlive())
    {
        state = PlayerLost;
        log("玩家生命值归零，战斗失败");
        emit battleStateChanged(state);
        endBattle();
        return;
    }

    // 检查所有敌人是否死亡
    if (!areEnemiesAlive())
    {
        state = PlayerWon;
        log("所有敌人都被击败了，战斗胜利！");
        emit battleStateChanged(state);
        endBattle();
        return;
    }
}

bool BattleController::areEnemiesAlive() const
{
    for (const Enemy &enemy : enemies)
    {
        if (enemy.isAlive())
        {
            return true;
        }
    }
    return false;
}

int BattleController::getAliveEnemyCount() const
{
    int count = 0;
    for (const Enemy &enemy : enemies)
    {
        if (enemy.isAlive())
        {
            count++;
        }
    }
    return count;
}

void BattleController::updateUI()
{
    // 更新玩家信息
    emit playerHealthChanged(player.getCurrentHp(), player.getMaxHp());
    emit playerEnergyChanged(player.getEnergy(), player.getMaxEnergy());
    emit playerBlockChanged(player.getBlock());
    emit playerStatusChanged(player.getStatusText());

    // 更新敌人信息
    for (int i = 0; i < enemies.size(); i++)
    {
        const Enemy &enemy = enemies[i];
        emit enemyHealthChanged(i, enemy.getCurrentHp(), enemy.getMaxHp());
        emit enemyIntentChanged(i, enemy.getIntentDescription(), enemy.getIntentValue());
    }

    // 更新卡牌信息
    emit handChanged(player.getHand());

    // 更新牌堆信息（需要扩展Player类来获取这些信息）
    // emit deckInfoChanged(...);
}

void BattleController::log(const QString &message)
{
    qDebug() << "[战斗]" << message;
    emit battleLog(message);
}
