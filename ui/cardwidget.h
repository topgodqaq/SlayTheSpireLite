#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include "src/core/card.h"

class CardWidget : public QFrame
{
    Q_OBJECT

public:
    explicit CardWidget(int index, const Card &card, QWidget *parent = nullptr);
    ~CardWidget();

    void updateCard(const Card &card);
    void setSelected(bool selected);

signals:
    void cardClicked(int cardIndex);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int cardIndex;
    QLabel *cardImageLabel = nullptr;
    QLabel *nameLabel = nullptr;
    QLabel *costLabel = nullptr;
    QLabel *descriptionLabel = nullptr;
    QVBoxLayout *layout = nullptr;
};

#endif // CARDWIDGET_H