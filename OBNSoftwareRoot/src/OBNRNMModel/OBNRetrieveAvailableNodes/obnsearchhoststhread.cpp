#include "obnsearchhoststhread.h"

#ifdef Q_OS_WIN
#define PINGPARAMETER " -n 1 -i 1 -q";    //Windows 格式,NUL 屏幕输出
#else
#define PINGPARAMETER " -c 1 -t 1 -q";    //Linux 下格式
#endif

OBNSearchHostsThread::OBNSearchHostsThread(QObject *parent) : QThread(parent)
{

}

void OBNSearchHostsThread::run()
{
    if(0 == m_values.count())
    {
        return;
    }
    QString nPingIPStr, nPingCMD;
    int pingExitCode = 0;
    QHostAddress addr;

    int nTotalNum = m_values.count();
    for(int iNO = 0; iNO < nTotalNum; iNO ++)
    {
        float fPorcessNum = iNO+1;
        int   iPorcessNum = fPorcessNum/nTotalNum*100;
        addr.setAddress(m_values[iNO]);
        nPingIPStr   = addr.toString();
        nPingCMD     = "ping " + nPingIPStr + PINGPARAMETER;
        pingExitCode = QProcess::execute(nPingCMD);
        if(0 == pingExitCode)
        {
            emit signalSearchHostsLinkStatus(nPingIPStr, iPorcessNum, true);
        }
        else
        {
            emit signalSearchHostsLinkStatus(nPingIPStr, iPorcessNum, false);
        }
    }
}
