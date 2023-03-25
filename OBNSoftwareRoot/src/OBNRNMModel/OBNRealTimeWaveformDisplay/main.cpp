#include "obnrealtimewaveroot.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QStringList nHostInformList;
    //nHostInformList << "172.18.1.88" << "172.18.1.89" << "172.18.1.90" << "172.18.1.91";

    OBNRealTimeWaveRoot w;
    // w.setCurrentAvailableHostInformList(nHostInformList);
    w.show();
    return a.exec();
}
