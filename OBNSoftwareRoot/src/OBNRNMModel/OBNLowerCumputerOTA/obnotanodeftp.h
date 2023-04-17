#ifndef OBNOTANODEFTP_H
#define OBNOTANODEFTP_H

#include "qftp.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QObject>

#include "macro.h"

#if 1
    #define FTP_USER_NAME     "root"
    #define FTP_USER_PASSWORD "root"
#else
    #define FTP_USER_NAME     "pi"
    #define FTP_USER_PASSWORD "raspberry"
#endif

class OBNOtaNodeFtp : public QObject
{
    Q_OBJECT
public:
    explicit OBNOtaNodeFtp(QObject *parent = nullptr);
    /// ====== 设置当前ftp服务器ip
    void setFtpServerIp(const QString&);

public slots:
    void slotCommandFinished(int cmd, bool error);
    /// ======
    void slotSetWorkPath(const QString& _workPath);
    /// ======
    void slotGetConfigFile(const QString&, const QString&);
    /// ======
    void slotPutFile(const QString, const QString);
    /// ======
    void slotDataTransferProgress(qint64, qint64);
    /// ======
    void slotListInform(const QUrlInfo&);
signals:
    void signal_error(QString);
    void signal_get_config_file_success(const QString&);
    void signal_put_ota_file_success();
    void signal_curent_progress(int);
private:
    QString m_curentFtpServerIp; ///< 当前节点IP
    QFtp*   m_ftp;
    QFile*  m_file;
    QString m_currentConfigfName;
    int     m_curentGet, m_curentPut, m_curentConnect, m_curentLogIn, m_curentCD, m_curentList;
};

#endif // OBNOTANODEFTP_H
