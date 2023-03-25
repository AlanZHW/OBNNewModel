#include "linemanager.h"
#include <QApplication>

#include "deploysystem.h"
#include "assignnodedlg.h"
#include "rndeployments.h"

#include <QTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LineManager w;
    w.show();
    return a.exec();
}
