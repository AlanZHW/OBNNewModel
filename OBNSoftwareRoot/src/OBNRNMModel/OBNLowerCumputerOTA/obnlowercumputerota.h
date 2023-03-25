#ifndef OBNLOWERCUMPUTEROTA_H
#define OBNLOWERCUMPUTEROTA_H

#include <QDebug>
#include <QWidget>
#include <QProgressBar>
#include <QFileDialog>

#include "publicHostInform.h"
#include "qftp.h"
#include "obnretrieveavailablenodes.h"
#include "obnlowercumputerota_global.h"

#define FTP_USER_NAME     "pi"
#define FTP_USER_PASSWORD "raspberry1"

QT_BEGIN_NAMESPACE
namespace Ui { class OBNLowerCumputerOTA; }
QT_END_NAMESPACE

class OBNOTA_EXPORT OBNLowerCumputerOTA : public QDialog
{
    Q_OBJECT
public:
    OBNLowerCumputerOTA(QWidget *parent = nullptr);
    ~OBNLowerCumputerOTA();
    void setCurrentOptionalInform(const QVector<HostsState>&);
    void putCurrentOTAFile();

    /// ======升级选项修改
    void otaOptionIndexChange(const int&);

private slots:
    void slotOTAOptionComboBoxIndexChange(const int&);

private:
    QString m_fileName;
    QVector<HostsState> m_hostVertor;
    ONBRetrieveAvailableNodes* m_obnSeatchHosts;
    Ui::OBNLowerCumputerOTA *ui;
};
#endif // OBNLOWERCUMPUTEROTA_H
