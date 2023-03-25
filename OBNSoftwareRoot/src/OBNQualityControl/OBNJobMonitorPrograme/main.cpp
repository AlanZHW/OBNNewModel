#include "obnjobmonitorprograme.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OBNJobMonitorPrograme w;
    w.show();
    return a.exec();
}
