#include "enemywidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QPixmap>

static QString resolveImagePath(const QString &relativePath)
{
    if (relativePath.isEmpty())
        return QString();
    if (QFile::exists(relativePath))
        return relativePath;

    QDir appDir(QCoreApplication::applicationDirPath());
    for (int i = 0; i < 6; ++i)
    {
        QString candidate = appDir.filePath(relativePath);
        if (QFile::exists(candidate))
            return candidate;
        appDir.cdUp();
    }

    return relativePath;
}

EnemyWidget::EnemyWidget(int index, QWidget *parent) : QFrame(parent), enemyIndex(index)
{
    setFrameStyle(QFrame::Box);
    setFixedSize(150, 220);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    intentLabel = new QLabel("Intent: Attack");
    intentLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(intentLabel);

    enemyImageLabel = new QLabel;
    enemyImageLabel->setAlignment(Qt::AlignCenter);
    enemyImageLabel->setStyleSheet("border: 1px solid black; background: #fff;");
    enemyImageLabel->setMinimumSize(120, 100);
    layout->addWidget(enemyImageLabel);

    hpLabel = new QLabel("HP: 50/50");
    hpLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(hpLabel);

    statusLabel = new QLabel("Status: Normal");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setWordWrap(true);
    layout->addWidget(statusLabel);

    setLayout(layout);
}

EnemyWidget::~EnemyWidget()
{
}

void EnemyWidget::updateEnemy(const Enemy &enemy)
{
    intentLabel->setText("Intent: " + enemy.getIntentDescription());
    hpLabel->setText(QString("HP: %1/%2").arg(enemy.getCurrentHp()).arg(enemy.getMaxHp()));
    statusLabel->setText("Status: " + enemy.getStatusText());

    QString imagePath = resolveImagePath(enemy.getImagePath());
    QPixmap pix(imagePath);
    if (!pix.isNull())
    {
        enemyImageLabel->setPixmap(pix.scaled(120, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        enemyImageLabel->setText("");
    }
    else
    {
        enemyImageLabel->setText(enemy.getName());
    }
}

void EnemyWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit enemyClicked(enemyIndex);
    }
    QFrame::mousePressEvent(event);
}