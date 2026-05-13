#ifndef BATTLEVIEW_H
#define BATTLEVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include "src/battle/battlecontroller.h"
#include "ui/cardwidget.h"
#include "ui/enemywidget.h"
#include "ui/playerwidget.h"

class BattleView : public QMainWindow
{
    Q_OBJECT

public:
    explicit BattleView(QWidget *parent = nullptr);
    ~BattleView();

private slots:
    void onCardClicked(int cardIndex);
    void onEnemyClicked(int enemyIndex);
    void onEndTurnClicked();
    void onBattleEnded(bool playerWon);

private:
    void setupUI();
    void setupBattle();
    void updateUI();
    bool eventFilter(QObject *obj, QEvent *event) override;
    bool canPlaySelectedCardOnEmpty() const;
    void updateStatusLabel();

    BattleController *battleController = nullptr;

    QWidget *centralWidget = nullptr;
    QVBoxLayout *mainLayout = nullptr;

    PlayerWidget *playerWidget = nullptr;
    QWidget *battleArea = nullptr;
    QLabel *battleAreaLabel = nullptr;

    QWidget *enemiesContainer = nullptr;
    QVBoxLayout *enemiesLayout = nullptr;
    QVector<EnemyWidget *> enemyWidgets;

    QWidget *handContainer = nullptr;
    QHBoxLayout *handLayout = nullptr;
    QVector<CardWidget *> cardWidgets;

    QLabel *statusLabel = nullptr;
    QPushButton *endTurnButton = nullptr;
    int selectedCardIndex = -1;
    QTextEdit *logText = nullptr;
};

#endif // BATTLEVIEW_H