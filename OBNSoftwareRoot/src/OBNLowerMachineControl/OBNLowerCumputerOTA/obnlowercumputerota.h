#ifndef OBNLOWERCUMPUTEROTA_H
#define OBNLOWERCUMPUTEROTA_H

#include <QWidget>
#include <QProgressBar>
#include <QFileDialog>

#include "publicHostInform.h"
#include "qftp.h"

#define FTP_USER_NAME     "pi"
#define FTP_USER_PASSWORD "raspberry1"

QT_BEGIN_NAMESPACE
namespace Ui { class OBNLowerCumputerOTA; }
QT_END_NAMESPACE

class OBNLowerCumputerOTA : public QWidget
{
    Q_OBJECT

public:
    OBNLowerCumputerOTA(QWidget *parent = nullptr);
    ~OBNLowerCumputerOTA();
    void setCurrentOptionalInform(const QVector<HostsState>&);
    void putCurrentOTAFile();
public slots:
    /// =======选择升级文件
    void slotBrowseFunction(const bool&);
    /// =======开始升级
    void slotStartFunction(const bool&);
    /// ======
    void slotDataTransferProgress(qint64 _t1, qint64 _t2);
private:
    QString m_fileName;
    QVector<HostsState> m_hostVertor;
    Ui::OBNLowerCumputerOTA *ui;
};
#endif // OBNLOWERCUMPUTEROTA_H
