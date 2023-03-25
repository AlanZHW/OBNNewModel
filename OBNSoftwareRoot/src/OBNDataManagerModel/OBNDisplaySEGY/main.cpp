#include "obndisplaysegy.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OBNDisplaySEGY w;
    w.show();
    return a.exec();
}
