#include "battleships.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BattleShips w;
    w.show();
    return a.exec();
}
