#include "nodeftp.h"
#include "rnitems.h"
#include "publicfunctions.h"

#include <QHostAddress>
#include <QDebug>

#if 0
    #define  FTP_User_Name      "root"
    #define  FTP_User_PassWord  "root"
#else
    #define  FTP_User_Name      "pi"
    #define  FTP_User_PassWord  "raspberry"
#endif

//设置最大配置文件大小，判断是配置文件还是数据文件
#define  Max_Config_File_Size   10E3

//=======================================================
NodeFtp::NodeFtp(QObject *parent)
    :QObject(parent)
    ,m_Ftp(NULL),m_file(NULL)
    ,m_workStep(NoneWork)
{
    qRegisterMetaType<QUrlInfo>("QUrlInfo");
    m_stoped = false;
}

void NodeFtp::setDevInfo(uint devNo,uint ip)
{
    node_ip = QHostAddress(ip).toString();
    node_no = QString("G%1").arg(devNo,3,10,QChar('0'));
}

void NodeFtp::startTimerInfo(const QString& SampletimeBegin,const QString& SampletimeEnd,const QString& SampleInterval)
{
    QString filename = m_workPath + Dir_Separator + Node_NODAL_FILE;
    //===先读一遍配置文件
    QString strAll;
    QStringList strList;
    QFile fileObsInfo(filename);
    if(!fileObsInfo.exists())
    {
        qDebug() << __FILE__ << "\t" << __FUNCTION__ << "\t" << __LINE__ << "\t filename = " << filename;
        return;
    }
    if(fileObsInfo.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        strAll=fileObsInfo.readAll();
        fileObsInfo.close();
    }
    else
    {
        qDebug() << __FILE__ << "\t" << __LINE__ << "\t" << __FUNCTION__ << "\t" << filename << "\t打开文件失败";
    }


#ifndef ZHW_DEBUG
    qDebug() << "zhw debug ...... " << __FILE__ << "\t" << __LINE__ << "\t" << __FUNCTION__ << "\t strAll is:" << strAll;
    qDebug() << "zhw debug ...... " << __FILE__ << "\t" << __LINE__ << "\t" << __FUNCTION__ << "\t filename is:" << filename;
#endif

    QFile writeFile(filename);
    if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream stream(&writeFile);
        strList=strAll.split("\n");
        for(int i=0;i<strList.count();i++)
        {
            if(i==strList.count()-1)
            {
                QString EndStr=strList.at(i);
                if(EndStr.contains("Sample Interval Per Hour"))
                {
                    int ipos=EndStr.indexOf(":");
                    EndStr.replace(ipos+1,EndStr.length()-ipos,SampleInterval);
                    stream<<EndStr;
                }
            }
            else
            {
                stream<<strList.at(i)<<'\n';
            }
            if(strList.at(i).contains("Sample Per Sec"))
            {
                QString tempStr=strList.at(i+1);
                if (tempStr.contains("Start Sampling Time"))
                {
                    int ipos=tempStr.indexOf(":");
                    tempStr.replace(ipos+1,tempStr.length()-ipos,SampletimeBegin);
                    stream<<tempStr<<'\n';
                }
                tempStr=strList.at(i+2);
                if (tempStr.contains("Stop  Sampling Time"))
                {
                    int ipos=tempStr.indexOf(":");
                    tempStr.replace(ipos+1,tempStr.length()-ipos,SampletimeEnd);
                    stream<<tempStr<<'\n';
                }
                i+=2;
            }
        }
    }
    writeFile.close();
}


void NodeFtp::startWork(const int &ftpWk,const QVariant &arg)
{
    qDebug()<<"main thread:"<<qApp->thread() <<"current thread:"<<QThread::currentThread();
    m_workStep = ftpWk;
    emit noteChanged(workName(m_workStep));
    if(NULL == m_Ftp)
    {
        m_Ftp = new QFtp(this);
        connect(m_Ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(slotCommandFinished(int,bool)),Qt::DirectConnection);
        connect(m_Ftp,SIGNAL(listInfo(const QUrlInfo&)),this,SLOT(slotListInfo(const QUrlInfo&)),Qt::DirectConnection);
    }
    qDebug() << __FILE__ << "\t" << __LINE__ << __FUNCTION__ << "\t"<< m_workStep;
    //1 更新节点信息
    if(m_workStep == Updating)
    {
        m_workPath = arg.toString();
        //文件目录
        m_workPath += Dir_Separator + node_no;
        qDebug() << "m_workPath = " << m_workPath;
        //查询本地文件目录，如果有配置文件读取采样率，没有在list之后需要下载
        m_FilesData.urlInfos.clear();
    }
    //2 下载文件
    else if(m_workStep == DownLoadFiles)
    {
        m_downloadType = arg.toInt();
    }
    //3 清除存储
    else if(m_workStep == ClearMemory)
    {
    }
    //4 设置采样率
    else if(m_workStep == SetSampleFrequecy)
    {
        if(m_sampleFrequency == arg.toInt())
        {
            emit finishedFtpWork(m_workStep,true);
            emit noteChanged("Finished");
            m_workStep = NoneWork;
            return;
        }
        m_sampleFrequency = arg.toInt();
        QString filename = m_workPath + Dir_Separator + Node_NODAL_FILE;
        if(!changeLocalFrequency(m_sampleFrequency,filename))
        {
            emit finishedFtpWork(m_workStep,true);
            emit noteChanged("Finished");
            m_workStep = NoneWork;
            return;
        }
    }
    m_stoped = false;
    if(m_Ftp->state() == QFtp::Unconnected)
    {
        qDebug() << __FILE__ << "\t" << __LINE__ << "\t" << __FUNCTION__ <<"\t connect:" << node_ip;
        m_ftpCmds.ConToHost = m_Ftp->connectToHost(node_ip, 21);
        qDebug() << "ConToHost = " << m_ftpCmds.ConToHost;
    }
}
void NodeFtp::stopWork()
{
    qDebug()<<"node stoped:"<<m_stoped;
    emit noteChanged("Stopping");
    m_stoped = true;
}

void NodeFtp::slotCommandFinished(int cmd, bool error)
{
    /// ====== 登录
    if(m_ftpCmds.ConToHost == cmd)
    {
        if(!error)
        {
            m_ftpCmds.LogIn = m_Ftp->login(FTP_User_Name,FTP_User_PassWord);
        }
        else
        {
            m_workStep = NoneWork;
        }
    }
    /// ======
    if(m_ftpCmds.LogIn == cmd)
    {
        if(!error)
        {
            switch(m_workStep)
            {
            case Updating:      ///< 查询
                /// ====== 开始查询时要将当前涉及到查询的内容进行初始化
                n_curentQurtyPath.clear();
                m_dataDirNameList.clear();
                m_nameAndDirMap.clear();

                n_curentQurtyPath = "/media/pi/OBN";
                /// ====== 开始查询
                m_ftpCmds.List = m_Ftp->list("/media/pi/OBN");
                break;
            case DownLoadFiles: ///< 下载文件
                startDownload();
                break;
            case SetSampleFrequecy: ///< 设置采样率
                uploadNodalFile();
                break;
            case ClearMemory:   ///< 清除容量
                if(1 <= m_FilesData.urlInfos.size())   /// 判断是否有文件
                    startClearMemory();
                break;
            default:
                break;
            }
        }
        else
        {
            //结束
            m_workStep = NoneWork;
            m_Ftp->close();
        }
    }

    /// ======
    if(m_ftpCmds.List == cmd)
    {
        if(!error)
        {
            /// ======
            if(0 != m_dataDirNameList.count())
            {
                /// ====== 查询子目录文件
                n_curentQurtyPath = m_dataDirNameList[m_dataDirNameList.length()-1];
                m_ftpCmds.List = m_Ftp->list("/media/pi/OBN/"+n_curentQurtyPath);
                /// ====== 删除路径列表已经查询过的路径
                m_dataDirNameList.removeAt(m_dataDirNameList.length()-1);
            }
            else
            {
                /// ====== 如果是查询
                if(m_workStep == Updating)
                {
                    updateInformation();
                }
            }
        }
        else
        {
            /// ====== 结束
            m_workStep = NoneWork;
            m_Ftp->close();
        }
    }
    else if(cmd == m_ftpCmds.get)
    {
        switch(m_workStep)
        {
        case Updating:  ///< 更新时候，下载完成配置文件，读取刷新采样率
            downloadedConfigureFile();
            break;
        case DownLoadFiles:
            finishDownload();
            break;
        default:
            break;
        }
    }
    else if(cmd == m_ftpCmds.put)
    {
        if(!error)
        {
            if(m_workStep == SetSampleFrequecy)
            {
                finishedSetFrequency();
            }
        }
    }
    //清除存储
    else if(cmd == m_ftpCmds.remove)
    {
        if(!error)
        {
            clearNextMemory();
        }
    }
    //close 结束任务
    else if(cmd == m_ftpCmds.close)
    {
        int temWork = m_workStep;
        m_workStep = NoneWork;
        emit finishedFtpWork(temWork);
        if(m_stoped)
        {
            emit noteChanged("Stopped");
        }
        else
        {
            emit noteChanged("Finished");
        }
    }
}

void NodeFtp::slotListInfo(QUrlInfo url)
{
    if("System Volume Information" == url.name())
    {
        return;
    }
    /// ====== 若当前返回的信息是文件夹
    if(url.isDir())
    {
        QString m_curentDataDirName = url.name();

        /// ====== 当发现没有工作目录，则先创建工作目录
        QDir nDirWorkPath(m_workPath);
        if(!nDirWorkPath.exists())
        {
            nDirWorkPath.mkdir(m_workPath);
        }

        qDebug() << "m_workPath = " << m_workPath << "\t m_curentDataDirName = " << m_curentDataDirName;
        /// ====== 在工作目录下创建数据文件夹
        QDir dirDataPath;
        qDebug() << "cd ...... "    << dirDataPath.cd(m_workPath);
        qDebug() << "mkdir ...... " << dirDataPath.mkdir(m_curentDataDirName);

        /// ====== 将目录名放到目录列表里面
        m_dataDirNameList.append(m_curentDataDirName);
        return;
    }
    m_FilesData.urlInfos.append(url);
    /// ====== 保存当前文件属于哪个目录
    m_nameAndDirMap.insert(url.name(), n_curentQurtyPath);
}

void NodeFtp::startDownload()
{
    qDebug()<<"start download:"<<m_downloadType;
    m_FilesData.workingFiles.clear();
    /// ====== 初始化下载文件信息：1)全部下载
    if(m_downloadType == DownloadAll)
    {
        /// ====== 服务器所有文件列表，去掉已经下载的文件
        foreach (QUrlInfo url,  m_FilesData.urlInfos)
        {
            /// ====== 判断当前需要下载的文件是否在已经下载完成列表中
            if(!m_FilesData.localFiles.contains(url.name()))
            {
                m_FilesData.workingFiles.append(url.name());
            }
        }
    }
    else if(m_downloadType == DownloadInPeriod) ///< 下载时间段内数据文件
    {
        //判断是否在时间段内
        foreach (QUrlInfo url,  m_FilesData.urlInfos)
        {
            //本地包含就不下载
            if(m_FilesData.localFiles.contains(url.name()))
            {
                continue;
            }
            /// ====== 如果是数据文件则计算时间
            if(!(url.name().endsWith(".log")||url.name().endsWith(".lst")||url.name().endsWith(".CFG")))
            {
                //计算文件事件判断是否需要下载
                if(isFileInPeriod(url.name()))
                {
                    m_FilesData.workingFiles.append(url.name());
                }
                continue;
            }
            //其他文件
            m_FilesData.workingFiles.append(url.name());
        }
    }


    /// ====== 更新下载进度
    int progress = calDownloadProgress();
    emit downloadPercentChanged(progress);
    /// ====== 如果没有目录则创建目录
    QDir dir(m_workPath);
    if(!dir.exists())
    {
        dir.mkdir(m_workPath);
    }
    if(!m_file)
    {
        m_file = new QFile(this);
    }
    /// ====== 开始下载第一个文件
    downloadNext();
}

float NodeFtp::countFilesSize(const QList<QUrlInfo> &files)
{
    long long memSize = 0;
    foreach (QUrlInfo url, files)
    {
        memSize += url.size();
    }
    qDebug() << "zhw debug......memSize = " << memSize;
    //GB为单位保存
    float gMem = float((double)memSize/(double)(1024*1024*1024));
    return gMem;
}

/// ====== 初始化信息(下载配置文件)
void NodeFtp::updateInformation()
{
    if(0 >= m_FilesData.urlInfos.count())
    {
        return;
    }
    /// ====== 计算节点剩余存储,GB为单位保存
    float gMem = countFilesSize(m_FilesData.urlInfos);
    emit memoryChanged(32.0f - gMem);

    /// ====== 初始化本地文件目录，计算下载进度
    QDir dir(m_workPath);
    if(!dir.exists())
    {
        dir.mkdir(m_workPath);
    }
    m_FilesData.localFiles = dir.entryList(QDir::Files);

    /// ====== 服务器所有文件列表，去掉已经下载的文件
    int percent = 100*m_FilesData.localFiles.size()/m_FilesData.urlInfos.size();
    percent = percent>100?100:percent;
    emit downloadPercentChanged(percent);

    /// ====== 采样率查询
    QString filename = m_workPath + Dir_Separator + Node_NODAL_FILE;
    qDebug() << "filename = " << filename;
    QFile  file(filename);
    /// ====== 本地配置文件存在
    if(file.exists())
    {
        int frequency = getFrequencyFromFile(filename);
        if(frequency>0)
        {
            m_sampleFrequency = frequency;
            emit frequencyChanged(m_sampleFrequency);

            //关闭链接，结束任务
            m_ftpCmds.close = m_Ftp->close();
            return;
        }
    }
    /// ====== 配置文件不存在，下载配置文件
    if(!m_file)
    {
        m_file = new QFile(this);
    }
    m_FilesData.currentFile = Node_NODAL_FILE;
    filename = m_workPath + Dir_Separator + Node_NODAL_FILE;
    m_file->setFileName(filename);
    m_file->open(QIODevice::WriteOnly);
    m_ftpCmds.get = m_Ftp->get(Node_NODAL_FILE,m_file);
}

void NodeFtp::startClearMemory()
{
    /// ====== 清除当前正在下载的文件列表
    m_FilesData.workingFiles.clear();
    /// ====== 去掉Node_NODAL_FILE File
    foreach (QUrlInfo url, m_FilesData.urlInfos)
    {
        if(url.name() != Node_NODAL_FILE)
        {
            m_FilesData.workingFiles.append(url.name());
        }
    }
    //从第一个开始清除
    m_ftpCmds.remove = m_Ftp->remove(m_FilesData.workingFiles.takeFirst());
}

int NodeFtp::calDownloadProgress()
{
    int percent = 0;
    /// ====== 更新下载文件进度
    if(m_FilesData.urlInfos.size()<1)
    {
        percent = 0;
    }
    else
    {
        percent = (100.f*float(m_FilesData.localFiles.size())/float(m_FilesData.urlInfos.size()));
        percent = percent>100?100:percent;
    }
    return percent;
}

void NodeFtp::finishDownload()
{
    /// ====== 关闭文件
    m_file->close();
    /// ====== 更新本地文件进度
    m_FilesData.localFiles.append(m_FilesData.currentFile);
    /// ====== 获取当前下载进度
    int progress = calDownloadProgress();
    emit downloadPercentChanged(progress);
    /// ====== 已经停止，结束下载
    if(m_stoped)
    {
        qDebug()<<"download stoped";
        m_ftpCmds.close = m_Ftp->close();
    }
    else
    {
        /// ====== 继续下一个文件
        downloadNext();
    }
}

void NodeFtp::downloadNext()
{
    if(!m_FilesData.workingFiles.isEmpty())
    {
        QString n_curentFileName = m_FilesData.workingFiles.takeFirst();;
        QString m_currentGetFilePath = m_nameAndDirMap.value(n_curentFileName);
        QString fileName;
        if(m_currentGetFilePath == "/media/pi/OBN")
        {
            fileName                = m_workPath + Dir_Separator + n_curentFileName;
            m_FilesData.currentFile = m_currentGetFilePath + Dir_Separator + n_curentFileName;
        }
        else
        {
            fileName                = m_workPath + Dir_Separator + m_currentGetFilePath + Dir_Separator + n_curentFileName;
            m_FilesData.currentFile = "/media/pi/OBN/" + m_currentGetFilePath + Dir_Separator + n_curentFileName;
        }
        qDebug() << "m_currentGetFilePath = " << m_currentGetFilePath << "\t ftp服务文件：" << m_FilesData.currentFile << "\t 本地目录名称:" << fileName;
        m_file->setFileName(fileName);
        if(!m_file->open(QIODevice::WriteOnly))
        {
            return;
        }
        m_ftpCmds.get = m_Ftp->get(m_FilesData.currentFile, m_file);
    }
    else
    {
        //下载完成，结束
        m_ftpCmds.close = m_Ftp->close();
    }
}


int NodeFtp::getFrequencyFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << __FILE__ << "\t" << __FUNCTION__ << "\t" << __LINE__;
        return -1;
    }
    QTextStream in(&file);
    QString context = in.readAll();
    QString sampleLine = context.split("\n",QString::SkipEmptyParts).at(1);
    QString sampleStr = sampleLine.mid(sampleLine.indexOf(":")+1,4);
    file.close();
    return sampleStr.toInt();
}

void NodeFtp::downloadedConfigureFile()
{
    m_file->close();
    //下载完成，更新采样率
    {
        //配置文件下载完成，更新采样频率
        QString filename = m_workPath + Dir_Separator + Node_NODAL_FILE;
        int frequency = getFrequencyFromFile(filename);
        m_sampleFrequency = frequency;

        emit frequencyChanged(m_sampleFrequency);
        //下载完成，结束
        m_ftpCmds.close = m_Ftp->close();
    }
}

bool NodeFtp::changeLocalFrequency(const int &frequency,const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << __FILE__ << "\t" << __LINE__ << "\t" << __FUNCTION__ << "\t" << fileName << "\t打开文件失败";
        return false;
    }
    QTextStream in(&file);
    QString context = in.readAll();
    file.close();
    //====更新采样率
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QStringList list = context.split("\n",QString::SkipEmptyParts);

    int index = list.at(1).indexOf(":");
    QString prex = list.at(1).mid(0,index+1);
    QString last;
    if(frequency == 1000)
    {
        last = "1000 //500,250";
    }
    else if(frequency == 500)
    {
        last = "500 //1000,250";
    }
    else if(frequency == 250)
    {
        last = "250 //1000,500";
    }
    list[1] = prex+last;
    QTextStream out(&file);
    for(int i=0;i<list.size();i++)
    {
        out<<list[i]<<endl;
    }
    file.close();
    return true;
}

void NodeFtp::uploadNodalFile()
{
    //上传配置文件
    if(!m_file)
    {
        m_file = new QFile(this);
    }
    QString filename = m_workPath +Dir_Separator+Node_NODAL_FILE;
    m_file->setFileName(filename);
    qDebug()<<"upload:"<<filename;
    qDebug()<<"open:"<< m_file->open(QIODevice::ReadOnly);
    m_ftpCmds.put = m_Ftp->put(m_file,Node_NODAL_FILE);
}

void NodeFtp::finishedSetFrequency()
{
    m_file->close();
    qDebug()<<"finished put";
    emit frequencyChanged(m_sampleFrequency);
    //关闭链接，结束任务
    m_ftpCmds.close = m_Ftp->close();
}

void NodeFtp::clearNextMemory()
{
    //判断清除完成
    if(m_FilesData.workingFiles.isEmpty())
    {
        emit memoryChanged(32.0f);
        m_ftpCmds.close = m_Ftp->close();
    }
    else
    {
        //从第一个开始清除
        m_ftpCmds.remove = m_Ftp->remove(m_FilesData.workingFiles.takeFirst());
    }
}

