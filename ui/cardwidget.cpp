#include "cardwidget.h"
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

CardWidget::CardWidget(int index, const Card &card, QWidget *parent) : QFrame(parent), cardIndex(index)
{
    setFrameStyle(QFrame::Box);
    setFixedSize(120, 200);
    setStyleSheet("QFrame { border: 1px solid #aaa; border-radius: 6px; }");

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    cardImageLabel = new QLabel;
    cardImageLabel->setAlignment(Qt::AlignCenter);
    cardImageLabel->setMinimumSize(100, 80);
    cardImageLabel->setStyleSheet("background: #fff; border: 1px solid #ddd;");
    layout->addWidget(cardImageLabel);

    nameLabel = new QLabel(card.name);
    nameLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(nameLabel);

    costLabel = new QLabel(QString("Cost: %1").arg(card.cost));
    costLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(costLabel);

    descriptionLabel = new QLabel(card.description);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(descriptionLabel);

    setLayout(layout);
    updateCard(card);
}

CardWidget::~CardWidget()
{
}

void CardWidget::updateCard(const Card &card)
{
    nameLabel->setText(card.name);
    costLabel->setText(QString("Cost: %1").arg(card.cost));
    descriptionLabel->setText(card.description);

    QPixmap pix;
    const QString path = resolveImagePath(card.getImagePath());
    if (!path.isEmpty())
    {
        pix.load(path);
    }
    if (!pix.isNull())
    {
        cardImageLabel->setPixmap(pix.scaled(100, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        cardImageLabel->setText(card.name);
    }
}

void CardWidget::setSelected(bool selected)
{
    if (selected)
    {
        setStyleSheet("QFrame { border: 2px solid #0078d7; border-radius: 6px; }");
    }
    else
    {
        setStyleSheet("QFrame { border: 1px solid #aaa; border-radius: 6px; }");
    }
}

void CardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit cardClicked(cardIndex);
    }
    QFrame::mousePressEvent(event);
}