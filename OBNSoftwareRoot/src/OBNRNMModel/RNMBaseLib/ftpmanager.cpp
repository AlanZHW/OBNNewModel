#include "ftpmanager.h"

FtpManager::FtpManager(Node *owner)
    :QObject(owner)
    ,m_node(owner)
{
    m_Thread = new QThread(this);
    m_nodeFtp = new NodeFtp;
    m_nodeFtp->moveToThread(m_Thread);
    connect(this,SIGNAL(signalStartWork(const int&,const QVariant&)),m_nodeFtp,SLOT(startWork(const int&,const QVariant&)),Qt::QueuedConnection);
    connect(this,SIGNAL(signalTimerInfo(const QString&,const QString&,const QString&)),m_nodeFtp,SLOT(startTimerInfo(const QString&,const QString&,const QString&)),Qt::QueuedConnection);
    connect(this,SIGNAL(signalStopWork()),m_nodeFtp,SLOT(stopWork()),Qt::QueuedConnection);

    connect(m_nodeFtp,SIGNAL(memoryChanged(float)),SLOT(slotMemoryChanged(float)),Qt::QueuedConnection);
    connect(m_nodeFtp,SIGNAL(frequencyChanged(int)),SLOT(slotFrequencyChanged(int)),Qt::QueuedConnection);
    connect(m_nodeFtp,SIGNAL(downloadPercentChanged(int)),SLOT(slotDownloadPercentChanged(int)),Qt::QueuedConnection);
    connect(m_nodeFtp,SIGNAL(finishedFtpWork(int,bool)),SLOT(slotFinishedFtpWork(int,bool)),Qt::QueuedConnection);
    //Note
    connect(m_nodeFtp,SIGNAL(noteChanged(const QString&)),SLOT(slotNoteChanged(const QString&)),Qt::QueuedConnection);

}

FtpManager::~FtpManager()
{
    if(m_Thread && m_Thread->isRunning())
    {
        m_Thread->quit();
        m_Thread->wait();
    }
    delete m_nodeFtp;
}

void FtpManager::setTimerInfo(const QString &startTime,const QString &endTime, const QString &SampInterPer)
{
    emit signalTimerInfo(startTime, endTime, SampInterPer);
}

void FtpManager::startWork(const int &ftpWk,const QVariant &arg)
{
    if(m_Thread->isRunning())
    {
        return;
    }
    m_nodeFtp->setDevInfo(m_node->no(),m_node->ip());
    /// ====== 启动子线程工作
    m_Thread->start();
    qDebug() << __FILE__ << "\t" << __LINE__ << __FUNCTION__;
    emit signalStartWork(ftpWk,arg);
}

void FtpManager::stopFtpWork()
{
    emit signalStopWork();
}

void FtpManager::slotMemoryChanged(float memory)
{
    qDebug()<<"slot memory changed:"<<QThread::currentThread();
    qDebug()<<"meory changed:"<<memory;
    m_node->setMemory(memory);
    m_node->updateNode(Ftp_Update_Memory);
}

void FtpManager::slotFrequencyChanged(int frequency)
{
    m_node->setSampleFrequency(frequency);
    m_node->updateNode(Ftp_Update_SampleFrequency);
}

void FtpManager::slotDownloadPercentChanged(int percent)
{
    m_node->setDownloadPercent(percent);
    m_node->updateNode(Ftp_Update_Progress);
}

void FtpManager::slotNoteChanged(const QString &note)
{
    qDebug() << "slotNoteChanged ...... note is:" << note;
    m_node->setInfoString(note);
    m_node->updateNode(Ftp_Update_Note);
}

void FtpManager::slotFinishedFtpWork(int ftpWork,bool error)
{
    //结束线程
    if(m_Thread->isRunning())
    {
        m_Thread->quit();
        m_Thread->wait();
    }
    //完成工作
    m_node->finishedFtpWork(ftpWork,error);
}
