#include <QApplication>
#include "obnwelcomemodel.h"
#include "obnlowercomputercontrol.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    OBNWelcomeModel w;
//    w.show();

    OBNLowerComputerControl cw;
    cw.show();

    return a.exec();
}
