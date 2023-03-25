#include "searchthread.h"

#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>


SearchThread::SearchThread(QObject *parent)
    : QThread(parent),m_stoped(false)
    ,m_IPScope(0,0),m_wTime(1000)
{

}

SearchThread::~SearchThread()
{
//    qDebug()<<"destory thread";
}

void SearchThread::stop()
{
    m_mutex.lock();
    m_stoped = true;
    m_mutex.unlock();
}

void SearchThread::setTotalHosts(QVector<uint> hosts)
{
    m_totalHosts = hosts;
}

void SearchThread::setIPScope(const int &start, const int &last)
{
    m_IPScope  = IPScope(start,last);
}

void SearchThread::setTaskCount(const TaskCount &taskCount)
{
    m_taskCount = taskCount;
}

void SearchThread::run()
{
    m_stoped = false;

    QHostAddress addr;

    QString cmdStr;
    int exitCode = 0;

    QString args;
#ifdef Q_OS_WIN
    args = " -n 1 -w 5 ";//Windows 格式,NUL 屏幕输出
#else
    args = " -c 1 -t 1 -q";//Linux 下格式
#endif

    //for(uint ip = m_IPScope.first;ip<=m_IPScope.second;ip++)
    for(uint ip = m_taskCount.start;ip <= m_taskCount.end;ip += m_taskCount.step)
    {
        m_mutex.lock();
        if(m_stoped)
        {
            m_mutex.unlock();
            break;
        }
        m_mutex.unlock();
        addr.setAddress(m_totalHosts[ip]);
        cmdStr = "ping "+addr.toString() +args;
        exitCode = QProcess::execute(cmdStr);
        if (0 == exitCode)
        {
            emit searchedHost(ip,true);
        }
        else
        {
            emit searchedHost(ip,false);
        }
    }
    emit searchFinished(m_id);
}


