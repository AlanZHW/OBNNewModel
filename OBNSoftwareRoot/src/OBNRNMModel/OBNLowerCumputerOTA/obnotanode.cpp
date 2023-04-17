#include "obnotanode.h"

OBNOtaNode::OBNOtaNode(QObject *parent) : QObject(parent)
{
    m_threadFtp = new QThread;
    m_ftp = new OBNOtaNodeFtp;
    m_ftp->moveToThread(m_threadFtp);

    /// ====== 改变工作目录
    connect(this, &OBNOtaNode::sig_changeWorkPath, m_ftp, &OBNOtaNodeFtp::slotSetWorkPath);
    /// ======
    connect(this, &OBNOtaNode::sig_getConfigFile, m_ftp, &OBNOtaNodeFtp::slotGetConfigFile);
    /// ======
    connect(this, &OBNOtaNode::sig_putFile, m_ftp, &OBNOtaNodeFtp::slotPutFile);
    /// ==================
    connect(m_ftp, &OBNOtaNodeFtp::signal_error, this, [=](QString _errorInform){
        emit node_signal_error(m_curentRowNo, _errorInform);
    });
    connect(m_ftp, &OBNOtaNodeFtp::signal_get_config_file_success, this, [=](const QString& _cfgFileName){
        emit node_signal_get_config_file_success(m_curentRowNo, _cfgFileName);
    });
    connect(m_ftp, &OBNOtaNodeFtp::signal_put_ota_file_success, this, [=](){
        emit node_signal_put_ota_file_success(m_curentRowNo);
    });
    connect(m_ftp, &OBNOtaNodeFtp::signal_curent_progress, this, [=](int _progress){
        emit node_signal_curent_progress(m_curentRowNo, _progress);
    });
}



/// ====== 设置当前ftp服务器IP和所在表格行
void OBNOtaNode::setFtpServerIp(const int& _rowNo, const QString& _ftpServerIP)
{
    m_curentRowNo       = _rowNo;
    m_curentFtpServerIp = _ftpServerIP;
    /// ======
    m_ftp->setFtpServerIp(_ftpServerIP);
    /// ====== 启动线程
    m_threadFtp->start();
}

/// ====== 设置工作目录
void OBNOtaNode::setCurrentWorkPath(QString _workPath)
{
    emit sig_changeWorkPath(_workPath);
}

/// ====== 下载config文件
void OBNOtaNode::getConfigFile(QString _hostName, QString _mainWorkPath)
{
    qDebug() << __FUNCTION__ << "\t" << __FILE__ << "\t _hostName = " << _hostName << "\t _mainWorkPath = " << _mainWorkPath;
    emit sig_getConfigFile(_hostName, _mainWorkPath);
}

/// ====== 上传升级文件
void OBNOtaNode::putOTAFileFunction(QString _otaFile, QString _hostDir)
{
    emit sig_putFile(_otaFile, _hostDir);
}




