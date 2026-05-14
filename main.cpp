#include <QApplication>
#include "ui/battleview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QMainWindow { background-image: url(:/images/battle_background.png); background-position: center; background-repeat: no-repeat; }");

    BattleView battleView;
    battleView.show();

    return a.exec();
}
