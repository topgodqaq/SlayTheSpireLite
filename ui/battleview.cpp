#include "battleview.h"
#include <QApplication>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

BattleView::BattleView(QWidget *parent) : QMainWindow(parent)
{
    battleController = new BattleController(this);

    QVector<Enemy> enemies;
    enemies.append(Enemy("史莱姆A", 20, Enemy::Slime_A));
    enemies.append(Enemy("哨卫", 25, Enemy::Sentinel));
    enemies.append(Enemy("邪教徒", 30, Enemy::Cultist));
    battleController->startBattle(enemies);

    setupUI();
    setupBattle();
    updateUI();
}

BattleView::~BattleView()
{
}

void BattleView::setupUI()
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *topLayout = new QHBoxLayout;
    mainLayout->addLayout(topLayout);

    playerWidget = new PlayerWidget;
    topLayout->addWidget(playerWidget);

    battleArea = new QWidget;
    battleArea->setStyleSheet("background: #f7f7f7; border: 1px dashed #ccc;");
    battleArea->setMinimumSize(240, 260);
    battleArea->installEventFilter(this);
    QVBoxLayout *battleLayout = new QVBoxLayout(battleArea);
    battleLayout->setAlignment(Qt::AlignCenter);
    battleAreaLabel = new QLabel("Click here to play non-attack cards");
    battleAreaLabel->setAlignment(Qt::AlignCenter);
    battleAreaLabel->setWordWrap(true);
    battleLayout->addWidget(battleAreaLabel);
    topLayout->addWidget(battleArea, 1);

    enemiesContainer = new QWidget;
    enemiesLayout = new QVBoxLayout(enemiesContainer);
    topLayout->addWidget(enemiesContainer);

    handContainer = new QWidget;
    handLayout = new QHBoxLayout(handContainer);
    handLayout->setSpacing(10);
    handLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(handContainer);

    statusLabel = new QLabel("Select a card to play");
    statusLabel->setWordWrap(true);
    mainLayout->addWidget(statusLabel);

    endTurnButton = new QPushButton("End Turn");
    connect(endTurnButton, &QPushButton::clicked, this, &BattleView::onEndTurnClicked);
    mainLayout->addWidget(endTurnButton);

    logText = new QTextEdit;
    logText->setReadOnly(true);
    logText->setMaximumHeight(120);
    mainLayout->addWidget(logText);

    setWindowTitle("Slay the Spire Lite");
    resize(1000, 700);
}

void BattleView::setupBattle()
{
    // Connect battle controller signals
    connect(battleController, &BattleController::handChanged, this, &BattleView::updateUI);
    connect(battleController, &BattleController::turnEnded, this, &BattleView::updateUI);
    connect(battleController, &BattleController::playerHealthChanged, this, &BattleView::updateUI);
    connect(battleController, &BattleController::playerEnergyChanged, this, &BattleView::updateUI);
    connect(battleController, &BattleController::playerStatusChanged, this, &BattleView::updateUI);
    connect(battleController, &BattleController::enemyHealthChanged, this, &BattleView::updateUI);
    connect(battleController, &BattleController::enemyIntentChanged, this, &BattleView::updateUI);
    connect(battleController, &BattleController::battleEnded, this, &BattleView::onBattleEnded);

    // Create enemy widgets
    const QVector<Enemy> &enemies = battleController->getEnemies();
    for (int i = 0; i < enemies.size(); ++i)
    {
        EnemyWidget *enemyWidget = new EnemyWidget(i);
        enemyWidgets.append(enemyWidget);
        enemiesLayout->addWidget(enemyWidget);
        connect(enemyWidget, &EnemyWidget::enemyClicked, this, &BattleView::onEnemyClicked);
    }

    // Create card widgets
    const QVector<Card> &hand = battleController->getPlayer().getHand();
    for (int i = 0; i < hand.size(); ++i)
    {
        CardWidget *cardWidget = new CardWidget(i, hand[i]);
        cardWidgets.append(cardWidget);
        handLayout->addWidget(cardWidget);
        connect(cardWidget, &CardWidget::cardClicked, this, &BattleView::onCardClicked);
    }
}

void BattleView::onBattleEnded(bool playerWon)
{
    QString msg = playerWon ? "你胜利了！" : "你失败了！";
    QMessageBox::information(this, "战斗结束", msg);
}

void BattleView::updateUI()
{
    const Player &player = battleController->getPlayer();
    playerWidget->updatePlayer(player);

    // Update enemies
    const QVector<Enemy> &enemies = battleController->getEnemies();
    for (int i = 0; i < enemyWidgets.size(); ++i)
    {
        if (i < enemies.size())
        {
            enemyWidgets[i]->updateEnemy(enemies[i]);
            enemyWidgets[i]->show();
        }
        else
        {
            enemyWidgets[i]->hide();
        }
    }

    // Update hand
    const QVector<Card> &hand = battleController->getPlayer().getHand();
    for (int i = 0; i < cardWidgets.size(); ++i)
    {
        if (i < hand.size())
        {
            cardWidgets[i]->updateCard(hand[i]);
            cardWidgets[i]->show();
            cardWidgets[i]->setSelected(i == selectedCardIndex);
        }
        else
        {
            cardWidgets[i]->hide();
        }
    }

    updateStatusLabel();
}

void BattleView::onCardClicked(int cardIndex)
{
    if (selectedCardIndex == cardIndex)
    {
        selectedCardIndex = -1;
    }
    else
    {
        selectedCardIndex = cardIndex;
    }
    updateUI();
}

void BattleView::onEnemyClicked(int enemyIndex)
{
    const QVector<Card> &hand = battleController->getPlayer().getHand();
    if (selectedCardIndex < 0 || selectedCardIndex >= hand.size())
    {
        return;
    }

    const Card &card = hand[selectedCardIndex];
    if (card.type != Card::Attack)
    {
        statusLabel->setText("This card does not target enemies. Click the empty battle area instead.");
        return;
    }

    if (battleController->playCard(selectedCardIndex, enemyIndex))
    {
        selectedCardIndex = -1;
    }
    updateUI();
}

void BattleView::onEndTurnClicked()
{
    battleController->endTurn();
    selectedCardIndex = -1;
    updateUI();
}

bool BattleView::canPlaySelectedCardOnEmpty() const
{
    const QVector<Card> &hand = battleController->getPlayer().getHand();
    if (selectedCardIndex < 0 || selectedCardIndex >= hand.size())
    {
        return false;
    }
    const Card &card = hand[selectedCardIndex];
    return card.type != Card::Attack;
}

void BattleView::updateStatusLabel()
{
    const QVector<Card> &hand = battleController->getPlayer().getHand();
    if (selectedCardIndex >= 0 && selectedCardIndex < hand.size())
    {
        const Card &card = hand[selectedCardIndex];
        if (card.type == Card::Attack)
        {
            statusLabel->setText("Attack card selected: click an enemy on the right to play.");
            battleAreaLabel->setText("Attack cards must target an enemy.");
        }
        else
        {
            statusLabel->setText("Non-attack card selected: click the empty battle area to play.");
            battleAreaLabel->setText("Click here to play this card.");
        }
    }
    else
    {
        statusLabel->setText("Select a card to play.");
        battleAreaLabel->setText("Click here to play non-attack cards.");
    }
}

bool BattleView::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == battleArea && event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton && canPlaySelectedCardOnEmpty())
        {
            if (battleController->playCard(selectedCardIndex, -1))
            {
                selectedCardIndex = -1;
            }
            updateUI();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}