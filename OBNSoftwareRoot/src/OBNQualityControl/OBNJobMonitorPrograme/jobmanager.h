#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <QDir>
#include <QMenu>
#include <QFile>
#include <QDebug>
#include <QObject>
#include <QProcess>
#include <QScrollBar>
#include <QTextBrowser>
#include <QTextStream>
#include <QTimerEvent>
#include <QListWidget>
#include <QTextBrowser>

#include "publicHostInform.h"

class JobManager : public QObject
{
    Q_OBJECT
public:
    JobManager(QObject *parent = 0);
    ~JobManager();
    void setProjInfo(const ProjectInfo &projInfo);
    void init(QListWidget *jobList,QTextBrowser *logBrowser);
    void timerEvent(QTimerEvent *e);
    void refreshFiles();
    void refreshLog();
    void setAutoRefreshEnable(bool enable);
    void setLogRefreshInterval(int interval);
protected slots:
    void slotJobItemClicked(QListWidgetItem*);
    void slotCustomContextMuenuReqested(QPoint);
    void slotShowLog();
    void slotResubmit();

private:
    QListWidget  *m_jobList;
    QTextBrowser *m_logBrowser;
    ProjectInfo   m_projInfo;
    QString       m_currentFile;
    //刷新日志文件和刷新日志信息 时钟
    int          m_fileTimer,m_logTimer;
    int          m_interval;
    QMenu        *menu;
};

#endif // JOBMANAGER_H
