#ifndef NODEFTP_H
#define NODEFTP_H

#include "qftp.h"
#include "rnmpublic.h"
#include "qmetaobject.h"
#include "ftpmanager.h"
struct FtpCmd
{
    int ConToHost;
    int LogIn;
    int List;
    int get;
    int remove;
    int put;
    int close;
};

struct FilesData
{
    QList<QUrlInfo>   urlInfos;     //节点所有文件信息
    QStringList       localFiles;   //本地文件
    QStringList       workingFiles; //待下载文件
    QString           currentFile;  //当前正在下载文件
};

//Ftp 功能类
class NodeFtp : public QObject
{
    Q_OBJECT
public:
    NodeFtp(QObject *parent = 0);
    void setDevInfo(uint devNo,uint ip);
public slots:
    //开始执行命令
    void startWork(const int &ftpWk,const QVariant &arg);
    void stopWork();
    void startTimerInfo(const QString&,const QString&,const QString&);
signals:
    void memoryChanged(float memory);
    void frequencyChanged(int frequency);
    void downloadPercentChanged(int percent);
    //完成当前任务
    void finishedFtpWork(int ftpWork,bool error = false);
    void noteChanged(const QString &note);

private slots:
    void slotCommandFinished(int,bool);
    void slotListInfo(QUrlInfo);

private:
    void startDownload();
    void updateInformation();
    void startClearMemory();

    //功能函数-------------
    float countFilesSize(const QList<QUrlInfo> &files);
    int   calDownloadProgress();

    //当前文件下载完成
    void  finishDownload();
    int   getFrequencyFromFile(const QString &fileName);
    //下载配置文件
    void  downloadedConfigureFile();
    void  downloadNext();
    bool  changeLocalFrequency(const int &frequency,const QString &fileName);
    void  uploadNodalFile();
    void  finishedSetFrequency();
    void  clearNextMemory();

private:
    QFtp             *m_Ftp;
    QFile            *m_file;
    FilesData         m_FilesData;

    int               m_workStep;
    FtpCmd            m_ftpCmds;
    QString           m_workPath;
    int               m_sampleFrequency;

    QString           node_ip;
    QString           node_no;
    bool              m_stoped;

    int               m_downloadType;
};


#endif // NODEFTP_H
