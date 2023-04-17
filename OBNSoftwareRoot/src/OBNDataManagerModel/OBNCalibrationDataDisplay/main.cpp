#include "obncalibrationdatadisplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString projectPath = "/home/datuo/ZHW/TestPath/ProjectName";
    QString projectName = "ProjectName";

    OBNCalibrationDataDisplay w;
    w.setProjectInfrom(projectPath, projectName);
    w.show();
    return a.exec();
}
