#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "src/core/card.h"
#include "src/core/player.h"

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

    Player player;
    player.prepareForBattle();
    qDebug() << "玩家血量:" << player.getCurrentHp() << "/" << player.getMaxHp();
    qDebug() << "手牌数量:" << player.getHand().size();
    qDebug() << "当前能量:" << player.getEnergy();

    // 测试抽牌
    player.drawCards(4);
    qDebug() << "抽牌后手牌:" << player.getHand().size();
    player.gainBlock(3);

    // 测试结束回合
    player.endTurn();
    qDebug() << "结束回合后手牌:" << player.getHand().size();
    qDebug() << "结束回合后格挡值:" << player.getBlock();

    player.takeDamage(3,2);
    qDebug() << "受伤后格挡值" << player.getBlock();
    qDebug() << "受伤后生命值:" << player.getCurrentHp();

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