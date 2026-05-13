#ifndef ENEMYWIDGET_H
#define ENEMYWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "src/core/enemy.h"

class EnemyWidget : public QFrame
{
    Q_OBJECT

public:
    explicit EnemyWidget(int index, QWidget *parent = nullptr);
    ~EnemyWidget();

    void updateEnemy(const Enemy &enemy);

signals:
    void enemyClicked(int enemyIndex);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int enemyIndex;
    QLabel *intentLabel = nullptr;
    QLabel *enemyImageLabel = nullptr;
    QLabel *hpLabel = nullptr;
    QLabel *statusLabel = nullptr;
    QVBoxLayout *layout = nullptr;
};

#endif // ENEMYWIDGET_H