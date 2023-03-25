#include "gobsdtmagerdifftime.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GobsDtMagerDiffTime w;
    w.show();

    return a.exec();
}
