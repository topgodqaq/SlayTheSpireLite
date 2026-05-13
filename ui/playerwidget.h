#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include "src/core/player.h"

class PlayerWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();

    void updatePlayer(const Player &player);

private:
    QLabel *playerImageLabel = nullptr;
    QLabel *hpLabel = nullptr;
    QLabel *statusLabel = nullptr;
    QVBoxLayout *layout = nullptr;
};

#endif // PLAYERWIDGET_H