#include "obnlogvisuailzationdisplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OBNLogVisuailzationDisplay w;
    w.show();
    return a.exec();
}
