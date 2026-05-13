#include <QApplication>
#include "ui/battleview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BattleView battleView;
    battleView.show();

    return a.exec();
}
