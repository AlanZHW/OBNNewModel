#include "obnlmgrarealistwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OBNLMGRAreaListWidget w;
    QString projPath = "/home/datuo/ZHW/TestPath/ProjectName";
    QString projName = "ProjectName";
    w.setProjectInform(projPath, projName);
    w.show();
    return a.exec();
}
