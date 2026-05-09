#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "src/core/card.h"
#include "src/core/player.h"
#include "src/core/enemy.h"

void testPlayerStatus() {
    Player player(50, 3);

    // 测试虚弱效果
    player.addStatus("weak", 1);
    qDebug() << "攻击伤害测试（基础6点）：";
    int damage = player.calculateActualDamage(6);  // 应该是 4.5 -> 4

    // 测试脆弱效果
    player.addStatus("frail", 1);
    qDebug() << "格挡测试（基础5点）：";
    player.gainBlock(5);  // 应该是 3.75 -> 3

    // 测试易伤效果
    player.addStatus("vulnerable", 1);
    qDebug() << "受伤害测试（基础8点）：";
    player.takeDamage(8);  // 应该是 12点伤害

    qDebug() << "玩家状态:" << player.getStatusText();

    // 测试回合结束状态减少
    player.endTurnStatusUpdate();
    qDebug() << "回合结束后状态:" << player.getStatusText();
}

void testEnemyClass() {
    qDebug() << "=== 测试 Enemy 类 ===";

    // 创建不同敌人
    Enemy slime("史莱姆", 30, Enemy::Slime);
    Enemy goblin("哥布林", 25, Enemy::Goblin);

    qDebug() << "敌人1:" << slime.getName() << "生命:" << slime.getCurrentHp() << "/" << slime.getMaxHp();
    qDebug() << "敌人2:" << goblin.getName() << "生命:" << goblin.getCurrentHp() << "/" << goblin.getMaxHp();

    // 测试意图系统
    qDebug() << "\n=== 测试意图系统 ===";
    for (int i = 0; i < 3; i++) {
        slime.generateIntent();
        goblin.generateIntent();

        qDebug() << "第" << i+1 << "回合:";
        qDebug() << "  史莱姆意图:" << slime.getIntentDescription();
        qDebug() << "  哥布林意图:" << goblin.getIntentDescription();
    }

    // 测试战斗
    qDebug() << "\n=== 测试战斗 ===";

    // 史莱姆获得格挡
    slime.gainBlock(5);
    qDebug() << "史莱姆获得5点格挡";

    // 受到伤害
    slime.takeDamage(8);
    qDebug() << "史莱姆受到8点伤害后生命:" << slime.getCurrentHp();

    // 添加状态效果
    qDebug() << "\n=== 测试状态效果 ===";
    slime.addStatus("vulnerable", 2);
    slime.addStatus("weak", 1);

    qDebug() << "史莱姆状态:" << slime.getStatusText();

    // 状态影响下的伤害
    int baseDamage = 10;
    int actualDamage = baseDamage;  // 这里简化计算
    qDebug() << "基础伤害:" << baseDamage << "，对易伤敌人实际伤害大约:" << (baseDamage * 1.5);
    slime.takeDamage(actualDamage);

    // 测试是否存活
    qDebug() << "\n=== 测试存活状态 ===";
    slime.takeDamage(50);  // 造成大量伤害
    qDebug() << "史莱姆是否存活:" << (slime.isAlive() ? "是" : "否");

    qDebug() << "=== Enemy 类测试完成 ===";
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("杀戮尖塔Lite - 测试");
    window.resize(400, 300);

    // 创建中心部件
    QWidget* centralWidget = new QWidget(&window);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // 创建几张测试卡牌
    Card strike("strike", "打击", Card::Attack, 1, 6);
    Card defend("defend", "防御", Card::Skill, 1, 5);
    Card bash("bash", "重击", Card::Attack, 2, 8, "造成8点伤害，给予2点易伤");

    testPlayerStatus();

    testEnemyClass();

    // 显示卡牌信息
    QLabel* label1 = new QLabel(
        QString("卡牌1: %1 - %2 消耗: %3 效果: %4")
            .arg(strike.name)
            .arg(strike.getTypeString())
            .arg(strike.cost)
            .arg(strike.description)
        );

    QLabel* label2 = new QLabel(
        QString("卡牌2: %1 - %2 消耗: %3 效果: %4")
            .arg(defend.name)
            .arg(defend.getTypeString())
            .arg(defend.cost)
            .arg(defend.description)
        );

    QLabel* label3 = new QLabel(
        QString("卡牌3: %1 - %2 消耗: %3 效果: %4")
            .arg(bash.name)
            .arg(bash.getTypeString())
            .arg(bash.cost)
            .arg(bash.description)
        );

    // 升级测试按钮
    QPushButton* upgradeBtn = new QPushButton("升级打击卡牌");
    QLabel* upgradeResult = new QLabel("点击查看升级效果");

    QObject::connect(upgradeBtn, &QPushButton::clicked, [&]() {
        strike.upgrade();
        upgradeResult->setText(
            QString("升级后: 伤害 %1, 描述: %2")
                .arg(strike.value)
                .arg(strike.description)
            );
    });

    // 添加到布局
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);
    layout->addWidget(upgradeBtn);
    layout->addWidget(upgradeResult);
    layout->addStretch();

    window.setCentralWidget(centralWidget);
    window.show();

    return app.exec();
}