#include "exportsegydlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExportSegyDlg w;
    w.show();
    return a.exec();
}
