#include "opensegydlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenSegyDlg w;
    w.show();
    return a.exec();
}
