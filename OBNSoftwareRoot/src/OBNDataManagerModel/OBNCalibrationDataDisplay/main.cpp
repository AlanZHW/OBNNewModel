#include "obncalibrationdatadisplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OBNCalibrationDataDisplay w;
    w.show();
    return a.exec();
}
