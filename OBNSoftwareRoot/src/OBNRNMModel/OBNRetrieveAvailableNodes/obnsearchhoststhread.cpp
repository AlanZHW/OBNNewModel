#include "obnsearchhoststhread.h"

#ifdef Q_OS_WIN
#define PINGPARAMETER " -n 1 -i 1";    //Windows 格式,NUL 屏幕输出
#else
#define PINGPARAMETER " -c 1 -t 1 -q";    //Linux 下格式
#endif

OBNSearchHostsThread::OBNSearchHostsThread(QObject *parent) : QThread(parent)
{

}

void OBNSearchHostsThread::setValue(uint _values, int _row)
{
    m_value = _values;
    m_row   = _row;
}

void OBNSearchHostsThread::run()
{
    QString nPingIPStr, nPingCMD;
    int pingExitCode = 0;
    QHostAddress addr;
    addr.setAddress(m_value);
    nPingIPStr   = addr.toString();
    nPingCMD     = "ping " + nPingIPStr + PINGPARAMETER;
    pingExitCode = QProcess::execute(nPingCMD);
    if(0 == pingExitCode)
    {
        emit signalSearchHostsLinkStatus(m_row, true);
    }
    else
    {
        emit signalSearchHostsLinkStatus(m_row, false);
    }
#if 0
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
#endif
}
