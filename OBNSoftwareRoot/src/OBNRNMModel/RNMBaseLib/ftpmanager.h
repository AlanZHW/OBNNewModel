#ifndef FTPMANAGER_H
#define FTPMANAGER_H

#include <QObject>
#include <QDebug>

#include "qftp.h"
#include "rnmpublic.h"
#include "qmetaobject.h"
#include "nodeftp.h"

class NodeItem;
class NodeFtp;
class FtpManager : public QObject
{
    Q_OBJECT
public:
    FtpManager(Node *owner);
    ~FtpManager();
    void startWork(const int &ftpWk,const QVariant &arg);
    void setTimerInfo(const QString &startTime,const QString &endTime, const QString &SampInterPer);
    void stopFtpWork();

signals:
    void signalStartWork(const int &ftpWk,const QVariant &arg);
    void signalTimerInfo(const QString&, const QString&, const QString&);
    void signalStopWork();

private slots:
    //子线程信号对应槽
    void slotMemoryChanged(float);           //存储容量改变
    void slotFrequencyChanged(int frequency);//采样率改变
    void slotDownloadPercentChanged(int percent);//下载进度改变
    //某个任务完成
    void slotFinishedFtpWork(int,bool error);

    void slotNoteChanged(const QString &note);

private:
    Node     *m_node;
    //线程
    QThread  *m_Thread;
    NodeFtp  *m_nodeFtp;
};
#endif // FTPMANAGER_H
