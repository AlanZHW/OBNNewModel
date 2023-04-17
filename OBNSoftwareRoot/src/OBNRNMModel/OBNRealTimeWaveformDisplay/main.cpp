#include "obnrealtimewaveroot.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
    QList<TCPInform> nHostInformList;
    TCPInform nTcp1;
    nTcp1.ip = "172.18.1.88";
    nTcp1.port=5000;
    nHostInformList.append(nTcp1);

    TCPInform nTcp2;
    nTcp2.ip = "172.18.1.89";
    nTcp2.port=5000;
    nHostInformList.append(nTcp2);

    TCPInform nTcp3;
    nTcp3.ip = "172.18.1.90";
    nTcp3.port=5000;
    nHostInformList.append(nTcp3);

    TCPInform nTcp4;
    nTcp4.ip = "172.18.1.91";
    nTcp4.port=5000;
    nHostInformList.append(nTcp4);

    OBNRealTimeWaveRoot w;
    w.setCurrentAvailableHostInformList(nHostInformList);
    w.show();
#else
    OBNRealTimeWaveRoot w;
    w.show();
#endif
    return a.exec();
}
