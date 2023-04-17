#ifndef OBNOTANODE_H
#define OBNOTANODE_H

#include "qftp.h"

#include <QDebug>
#include <QThread>
#include <QObject>

#include "obnotanodeftp.h"


class OBNOtaNode : public QObject
{
    Q_OBJECT
public:
    explicit OBNOtaNode(QObject *parent = nullptr);
    /// ====== 设置当前ftp服务器ip
    void setFtpServerIp(const int&, const QString&);
    /// ====== 设置工作目录
    void setCurrentWorkPath(QString _workPath);
    /// ====== 下载config文件
    void getConfigFile(QString, QString);
    /// ====== 上传升级文件
    void putOTAFileFunction(QString, QString);
signals:
    /// ====== 可链接状态改变信号
    void sig_changeConnectState(bool);
    /// ====== 设置工作路径
    void sig_changeWorkPath(QString);
    /// ====== 下载config文件
    void sig_getConfigFile(QString, QString);
    /// ====== 上传文件
    void sig_putFile(QString, QString);

    /// ======
    void node_signal_error(int, QString);
    void node_signal_get_config_file_success(int, const QString&);
    void node_signal_put_ota_file_success(int);
    void node_signal_curent_progress(int, int);

private:
    int     m_curentRowNo;
    QString m_curentFtpServerIp; ///< 当前节点IP
    OBNOtaNodeFtp*   m_ftp;
    QThread* m_threadFtp;
};

#endif // OBNOTANODE_H
