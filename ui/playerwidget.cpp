#include "playerwidget.h"
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

PlayerWidget::PlayerWidget(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setFixedSize(180, 260);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    playerImageLabel = new QLabel;
    playerImageLabel->setAlignment(Qt::AlignCenter);
    playerImageLabel->setStyleSheet("border: 1px solid black; background: #fff;");
    playerImageLabel->setMinimumHeight(140);
    layout->addWidget(playerImageLabel);

    hpLabel = new QLabel("HP: 0/0");
    hpLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(hpLabel);

    statusLabel = new QLabel("Status: None");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setWordWrap(true);
    layout->addWidget(statusLabel);

    QString imagePath = resolveImagePath("images/player.png");
    QPixmap pix(imagePath);
    if (!pix.isNull())
    {
        playerImageLabel->setPixmap(pix.scaled(160, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        playerImageLabel->setText("Player Image");
    }
}

PlayerWidget::~PlayerWidget()
{
}

void PlayerWidget::updatePlayer(const Player &player)
{
    hpLabel->setText(QString("HP: %1/%2 | Energy: %3").arg(player.getCurrentHp()).arg(player.getMaxHp()).arg(player.getEnergy()));
    statusLabel->setText(QString("Status: %1").arg(player.getStatusText()));
}
