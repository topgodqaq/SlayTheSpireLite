#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include "src/battle/battlecontroller.h"
#include <QTime>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建主窗口
    QMainWindow window;
    window.setWindowTitle("杀戮尖塔Lite - BattleController 测试");
    window.resize(800, 600);

    // 创建中心部件
    QWidget* centralWidget = new QWidget(&window);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // 状态显示区域
    QLabel* statusLabel = new QLabel("战斗状态: 未开始", centralWidget);
    statusLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #333;");
    mainLayout->addWidget(statusLabel);

    // 玩家信息显示
    QLabel* playerLabel = new QLabel("玩家: 等待开始...", centralWidget);
    playerLabel->setStyleSheet("font-size: 14px; color: #0066CC;");
    mainLayout->addWidget(playerLabel);

    // 敌人信息显示
    QTextEdit* enemiesText = new QTextEdit(centralWidget);
    enemiesText->setReadOnly(true);
    enemiesText->setMaximumHeight(150);
    enemiesText->setPlaceholderText("敌人信息将在这里显示...");
    mainLayout->addWidget(new QLabel("敌人信息:"));
    mainLayout->addWidget(enemiesText);

    // 手牌显示
    QTextEdit* handText = new QTextEdit(centralWidget);
    handText->setReadOnly(true);
    handText->setMaximumHeight(100);
    handText->setPlaceholderText("手牌信息将在这里显示...");
    mainLayout->addWidget(new QLabel("当前手牌:"));
    mainLayout->addWidget(handText);

    // 日志显示
    QTextEdit* logText = new QTextEdit(centralWidget);
    logText->setReadOnly(true);
    logText->setMaximumHeight(200);
    mainLayout->addWidget(new QLabel("战斗日志:"));
    mainLayout->addWidget(logText);

    // 控制按钮区域
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* btnStartBattle = new QPushButton("开始战斗", centralWidget);
    QPushButton* btnEndTurn = new QPushButton("结束回合", centralWidget);
    QPushButton* btnAttackEnemy1 = new QPushButton("攻击敌人1", centralWidget);
    QPushButton* btnAttackEnemy2 = new QPushButton("攻击敌人2", centralWidget);
    QPushButton* btnTestRitual = new QPushButton("测试邪教徒", centralWidget);

    btnEndTurn->setEnabled(false);
    btnAttackEnemy1->setEnabled(false);
    btnAttackEnemy2->setEnabled(false);
    btnTestRitual->setEnabled(false);

    buttonLayout->addWidget(btnStartBattle);
    buttonLayout->addWidget(btnEndTurn);
    buttonLayout->addWidget(btnAttackEnemy1);
    buttonLayout->addWidget(btnAttackEnemy2);
    buttonLayout->addWidget(btnTestRitual);
    mainLayout->addLayout(buttonLayout);

    window.setCentralWidget(centralWidget);

    // 创建 BattleController
    BattleController battleController;

    // 更新UI的函数
    auto updateUI = [&]() {
        // 更新战斗状态
        QString stateText;
        switch (battleController.getState()) {
        case BattleController::NotStarted: stateText = "未开始"; break;
        case BattleController::PlayerTurn: stateText = "玩家回合"; break;
        case BattleController::EnemyTurn: stateText = "敌人回合"; break;
        case BattleController::PlayerWon: stateText = "玩家胜利"; break;
        case BattleController::PlayerLost: stateText = "玩家失败"; break;
        case BattleController::BattleEnd: stateText = "战斗结束"; break;
        }
        statusLabel->setText("战斗状态: " + stateText);

        // 更新玩家信息
        Player& player = battleController.getPlayer();
        playerLabel->setText(
            QString("玩家: 生命 %1/%2 | 能量 %3/%4 | 格挡 %5 | 状态: %6")
                .arg(player.getCurrentHp()).arg(player.getMaxHp())
                .arg(player.getEnergy()).arg(player.getMaxEnergy())
                .arg(player.getBlock()).arg(player.getStatusText())
            );

        // 更新敌人信息
        const QVector<Enemy>& enemies = battleController.getEnemies();
        QString enemiesInfo;
        for (int i = 0; i < enemies.size(); i++) {
            const Enemy& enemy = enemies[i];
            enemiesInfo += QString("敌人%1: %2 生命 %3/%4 | 意图: %5 | 状态: %6\n")
                               .arg(i+1).arg(enemy.getName())
                               .arg(enemy.getCurrentHp()).arg(enemy.getMaxHp())
                               .arg(enemy.getIntentDescription()).arg(enemy.getStatusText());
        }
        enemiesText->setText(enemiesInfo);

        // 更新手牌信息
        const QVector<Card>& hand = player.getHand();
        QString handInfo = "手牌:\n";
        for (int i = 0; i < hand.size(); i++) {
            const Card& card = hand[i];
            QString costColor = (card.cost <= player.getEnergy()) ? "green" : "red";
            handInfo += QString("  [%1] %2 (消耗<span style='color:%3;'>%4</span>费) - %5\n")
                            .arg(i+1).arg(card.name).arg(costColor).arg(card.cost).arg(card.description);
        }
        handText->setHtml(handInfo);

        // 更新按钮状态
        bool isPlayerTurn = (battleController.getState() == BattleController::PlayerTurn);
        btnEndTurn->setEnabled(isPlayerTurn);
        btnAttackEnemy1->setEnabled(isPlayerTurn && enemies.size() > 0);
        btnAttackEnemy2->setEnabled(isPlayerTurn && enemies.size() > 1);

        qDebug() << "UI已更新，当前回合:" << stateText;
    };

    // 日志函数
    auto addLog = [&](const QString& message) {
        logText->append(QTime::currentTime().toString("[hh:mm:ss] ") + message);
    };

    // 连接信号
    QObject::connect(&battleController, &BattleController::battleLog, addLog);

    QObject::connect(&battleController, &BattleController::battleStateChanged,
                     [&](BattleController::BattleState state) {
                         updateUI();
                     });

    QObject::connect(&battleController, &BattleController::playerHealthChanged,
                     [&](int current, int max) {
                         addLog(QString("玩家血量变化: %1/%2").arg(current).arg(max));
                     });

    // 按钮点击事件
    QObject::connect(btnStartBattle, &QPushButton::clicked, [&]() {
        addLog("=== 开始新战斗 ===");

        // 创建敌人组合
        QVector<Enemy> enemies;
        enemies.append(Enemy("史莱姆A", 20, Enemy::Slime_A));
        enemies.append(Enemy("哨卫", 25, Enemy::Sentinel));
        enemies.append(Enemy("邪教徒", 30, Enemy::Cultist));

        battleController.startBattle(enemies);
        updateUI();
    });

    QObject::connect(btnEndTurn, &QPushButton::clicked, [&]() {
        addLog("玩家点击了【结束回合】");
        battleController.endTurn();
        updateUI();
    });

    QObject::connect(btnAttackEnemy1, &QPushButton::clicked, [&]() {
        addLog("玩家攻击敌人1");
        bool success = battleController.playCard(0, 0);  // 用第一张卡攻击第一个敌人
        if (success) {
            addLog("攻击成功！");
        } else {
            addLog("攻击失败！");
        }
        updateUI();
    });

    QObject::connect(btnAttackEnemy2, &QPushButton::clicked, [&]() {
        addLog("玩家攻击敌人2");
        bool success = battleController.playCard(0, 1);  // 用第一张卡攻击第二个敌人
        if (success) {
            addLog("攻击成功！");
        } else {
            addLog("攻击失败！");
        }
        updateUI();
    });

    QObject::connect(btnTestRitual, &QPushButton::clicked, [&]() {
        addLog("=== 测试邪教徒仪式 ===");

        // 创建只有一个邪教徒的战斗
        QVector<Enemy> testEnemies;
        testEnemies.append(Enemy("邪教徒", 30, Enemy::Cultist));

        BattleController testBattle;

        // 模拟3回合观察仪式
        addLog("第1回合: 邪教徒开始仪式");
        testBattle.startBattle(testEnemies);
        testBattle.endTurn();  // 结束玩家回合

        addLog("第2回合: 邪教徒继续仪式");
        testBattle.endTurn();  // 跳过玩家回合

        addLog("第3回合: 仪式应完成");
        testBattle.endTurn();  // 仪式完成

        addLog("=== 仪式测试完成 ===");
    });

    // 自动运行一些测试
    qDebug() << "\n=== 运行自动测试 ===";

    // 测试1: 基本战斗流程
    {
        addLog("测试1: 基本战斗流程");
        QVector<Enemy> testEnemies;
        testEnemies.append(Enemy("测试史莱姆", 10, Enemy::Slime_A));

        BattleController testBattle;
        testBattle.startBattle(testEnemies);

        // 模拟一次攻击
        testBattle.playCard(0, 0);
        testBattle.endTurn();

        addLog("基本战斗测试完成");
    }

    // 测试2: 多段攻击
    {
        addLog("\n测试2: 哨卫多段攻击");
        QVector<Enemy> testEnemies;
        testEnemies.append(Enemy("测试哨卫", 15, Enemy::Sentinel));

        BattleController testBattle;
        testBattle.startBattle(testEnemies);
        testBattle.endTurn();  // 让哨卫行动

        addLog("哨卫多段攻击测试完成");
    }

    // 测试3: 状态效果
    {
        addLog("\n测试3: 状态效果系统");

        Player player(50, 3);
        player.prepareForBattle();

        player.addStatus("weak", 2);
        player.addStatus("vulnerable", 1);
        player.addStatus("frail", 1);

        addLog(QString("玩家状态: %1").arg(player.getStatusText()));
        addLog("状态效果测试完成");
    }

    addLog("\n=== 所有自动测试完成 ===");
    addLog("请点击【开始战斗】按钮手动测试");

    window.show();

    return app.exec();
}