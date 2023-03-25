#include "jobmanager.h"

JobManager::JobManager(QObject *parent)
    :QObject(parent)
{
    m_fileTimer = 0;
    m_logTimer  = 0;
    m_interval  = 5000;
    menu = 0;
}

JobManager::~JobManager()
{
    if(menu)
    {
        delete menu;
    }
}

void JobManager::setProjInfo(const ProjectInfo &projInfo)
{
    m_projInfo = projInfo;
}

void JobManager::init(QListWidget *jobList,QTextBrowser *logBrowser)
{
    m_jobList    = jobList;
    m_logBrowser = logBrowser;
    connect(m_jobList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(slotJobItemClicked(QListWidgetItem*)));
    //右键：查看日志，重新提交作业功能
    m_jobList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_jobList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slotCustomContextMuenuReqested(QPoint)));
    //开始刷新日志
    refreshFiles();
    m_fileTimer = this->startTimer(5000);
}

void JobManager::timerEvent(QTimerEvent *e)
{
    /// ====== 刷新文件列表
    if(e->timerId() == m_fileTimer)
    {
        refreshFiles();
    }
    /// ====== 刷新日志
    if(e->timerId() == m_logTimer)
    {
        refreshLog();
    }
}

void JobManager::slotJobItemClicked(QListWidgetItem* item)
{
    m_currentFile = item->text();
    refreshLog();
}

void JobManager::slotCustomContextMuenuReqested(QPoint pt)
{
    if(!m_jobList->itemAt(pt))
    {
        return;
    }
    if(!menu)
    {
        menu = new QMenu();
        menu->addAction(tr("显示日志"), this, SLOT(slotShowLog()));
        menu->addAction(tr("重新开始"), this, SLOT(slotResubmit()));
    }
    menu->exec(QCursor::pos());
}

void JobManager::slotShowLog()
{
    m_currentFile = m_jobList->currentItem()->text();
    refreshLog();
}

void JobManager::slotResubmit()
{
    QString jobFile = m_jobList->currentItem()->text();
    jobFile         = m_projInfo.ProjectPath +"/work/"+ jobFile;
    qDebug()<<jobFile;
    QProcess    process;
    QStringList argList;
    argList.append(jobFile);

#ifdef Q_OS_LINUX
    process.startDetached("ExportSegyProgram",argList);
#else
    process.startDetached("ExportSegyProgram.exe",argList);
#endif

}

void JobManager::refreshFiles()
{
    QDir dir(m_projInfo.ProjectPath+"/work/");
    QFileInfoList logFiles = dir.entryInfoList(QStringList()<<"*.log", QDir::Files,QDir::Time);
    m_jobList->clear();
    foreach (QFileInfo fileInfo, logFiles)
    {
        m_jobList->addItem(fileInfo.baseName());
    }
}

void JobManager::refreshLog()
{
    if(m_currentFile.isEmpty())
        m_logBrowser->clear();

    m_logBrowser->verticalScrollBar()->value();
    QFile file(m_projInfo.ProjectPath+"/work/"+m_currentFile+".log");
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    m_logBrowser->setText(out.readAll());
    file.close();
    m_logBrowser->verticalScrollBar()->setValue(m_logBrowser->verticalScrollBar()->maximum());
}


void JobManager::setAutoRefreshEnable(bool enable)
{
    if(enable)
    {
        m_logTimer = this->startTimer(m_interval);
    }
    else
    {
        this->killTimer(m_logTimer);
        m_logTimer = 0;
    }
}

void JobManager::setLogRefreshInterval(int interval)
{
    m_interval = interval*1000;
    if(m_logTimer > 0)
    {
        this->killTimer(m_logTimer);
        m_logTimer = this->startTimer(m_interval);
    }
}
