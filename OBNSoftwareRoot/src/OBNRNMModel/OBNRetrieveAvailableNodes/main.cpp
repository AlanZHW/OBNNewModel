#include "obnretrieveavailablenodes.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ONBRetrieveAvailableNodes w;
    w.show();
    return a.exec();
}
