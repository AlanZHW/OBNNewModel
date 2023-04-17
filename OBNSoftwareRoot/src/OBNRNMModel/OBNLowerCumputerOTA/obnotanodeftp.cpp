#include "obnotanodeftp.h"

OBNOtaNodeFtp::OBNOtaNodeFtp(QObject *parent) : QObject(parent), m_file(NULL),m_curentGet(0),
    m_curentPut(0), m_curentConnect(0), m_curentLogIn(0), m_curentCD(0), m_curentList(0)
{
    m_ftp = new QFtp;
    connect(m_ftp, &QFtp::commandFinished, this, &OBNOtaNodeFtp::slotCommandFinished,Qt::DirectConnection);
    connect(m_ftp, &QFtp::dataTransferProgress, this, &OBNOtaNodeFtp::slotDataTransferProgress,Qt::DirectConnection);
    connect(m_ftp, &QFtp::listInfo, this, &OBNOtaNodeFtp::slotListInform,Qt::DirectConnection);
}

/// ====== 设置当前ftp服务器IP和所在表格行
void OBNOtaNodeFtp::setFtpServerIp(const QString& _ftpServerIP)
{
    m_curentFtpServerIp = _ftpServerIP;
    m_curentConnect = m_ftp->connectToHost(_ftpServerIP, 21);
}

void OBNOtaNodeFtp::slotListInform(const QUrlInfo& _urlInfo)
{
    if(_urlInfo.isFile())
    {
        QFileInfo fileInform(_urlInfo.name());
        qDebug() << _urlInfo.name();
        if("lst" == fileInform.suffix())
        {
            m_currentConfigfName = _urlInfo.name();
        }
    }
}

/// ====== 设置路径
void OBNOtaNodeFtp::slotSetWorkPath(const QString& _workPath)
{
    m_curentCD = m_ftp->cd(_workPath);
    if("/media/pi/OBN" == _workPath)
    {
        m_curentList = m_ftp->list();
    }
}

/// ======
void OBNOtaNodeFtp::slotGetConfigFile(const QString& _hostName, const QString& _mainWorkPath)
{
    qDebug() << __FUNCTION__ << "\t" << __FILE__ << "\t _hostName = " << _hostName << "\t _mainWorkPath = " << _mainWorkPath;
    QString confileDirName = _mainWorkPath + Dir_Separator + _hostName;
    qDebug() << __FUNCTION__ << "\t" << __FILE__ << "\t confileDirName = " << confileDirName;

    QDir    n_dir(confileDirName);
    if(!n_dir.exists())
    {
        n_dir.cd(_mainWorkPath);
        n_dir.mkdir(_hostName);
    }

    QString configName = confileDirName + Dir_Separator + m_currentConfigfName;
    qDebug() << "configName = " << configName;
    if(NULL == m_file)
    {
        m_file = new QFile(this);
    }
    m_file->setFileName(configName);
    m_file->open(QIODevice::WriteOnly);
    m_curentGet = m_ftp->get(m_currentConfigfName, m_file);
}

/// ====== 获取下载,上传进度
void OBNOtaNodeFtp::slotDataTransferProgress(qint64 readBytes, qint64 totalBytes)
{
    auto percent = (qreal)readBytes/totalBytes;
    int  nprogess= (int)(percent*100);
    emit signal_curent_progress(nprogess);
}

/// ======
void OBNOtaNodeFtp::slotPutFile(const QString _fileName, const QString _hostFileName)
{
    qDebug() << __FILE__ << "\t" << __LINE__ << "\t _fileName = " << _fileName;
    if(NULL == m_file)
    {
        m_file = new QFile(this);
    }
    else
    {
        m_file->close();
    }
    m_file->setFileName(_fileName);
    qDebug() << m_file->open(QIODevice::ReadOnly);

    m_ftp->setTransferMode(QFtp::Passive);
    m_curentPut = m_ftp->put(m_file, _hostFileName);
}

void OBNOtaNodeFtp::slotCommandFinished(int cmd, bool error)
{
    qDebug() << "cmd = " << cmd;
    qDebug() << "m_curentGet = " << m_curentGet << "\t m_curentPut = "     << m_curentPut << "\t m_curentConnect = " << m_curentConnect
             << "\t m_curentLogIn = " << m_curentLogIn << "\t m_curentCD = " << m_curentCD << "\t m_curentList = " << m_curentList;

    if(cmd == m_curentGet)
    {
        if(!error)  ///< Get成功
        {
            m_file->close();
            emit signal_get_config_file_success(m_currentConfigfName);
            emit signal_error("Get成功");
        }
        else
        {
            m_file->close();
            emit signal_error("Get失败");
        }
    }
    if(cmd == m_curentPut)
    {
        if(!error)  ///< Put成功
        {
            m_file->close();
            emit signal_put_ota_file_success();
            emit signal_error("Put成功");
        }
        else
        {
            m_file->close();
            emit signal_error("Put失败");
        }
    }
    if(cmd == m_curentConnect)
    {
        if(!error)  ///< 链接成功
        {
            m_curentLogIn = m_ftp->login(FTP_USER_NAME, FTP_USER_PASSWORD);
            emit signal_error("链接成功");
        }
        else
        {
            emit signal_error("链接失败");
        }
    }
    if(cmd == m_curentLogIn)
    {
        if(!error)  ///< 登录成功
        {
            m_curentCD = m_ftp->cd("/");
            emit signal_error("登录成功");
        }
        else
        {
            emit signal_error("登录失败");
        }
    }
    if(cmd == m_curentCD)
    {
        if(!error)
        {

        }
        else
        {

        }
    }
}
