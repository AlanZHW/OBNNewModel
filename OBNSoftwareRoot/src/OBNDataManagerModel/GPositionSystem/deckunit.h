#ifndef DECKUNIT_H
#define DECKUNIT_H

#include <QWidget>
#include <QTcpSocket>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPushButton>
#include <QScrollArea>
#include <QLatin1Char>
#include "gpspublic.h"

#ifdef Q_OS_WIN
#include "windows.h"
#endif

#include "datamanager.h"
#include <QMessageBox>
namespace Ui {
class DeckUnit;
}


class IpAddrEdit;
class QLineEdit;
class QCheckBox;
class QComboBox;

//负责与甲板机通信数据
class DeckUnit : public QWidget
{
    Q_OBJECT
public:
    DeckUnit(QWidget *parent = Q_NULLPTR);
//    void setShowTxtFunc(ShowTextFunc func);

    void startTx();
    void stopTx();
    void getPortNameList(QStringList& p_portNameList);
    void setReleaseCode();
    char convertCharToHex(char ch);
    void convertStringToHex(const QString &str, QByteArray &byteData);

    void slotSondaryFunction();
    void slotSoundcommFunction();
protected slots:
    void slotConnect(bool connect);
    void TxVisit(bool flag);

    void socketStateChanged(QAbstractSocket::SocketState state);
    void slotReadyRead();
    void slotRateCurrTextChange(QString);
    void slotCurrTextChange(QString);

    void slotClickedStart();

    void slotStop();
private:
    void creatWg();

signals:
    void signal_recv_Delaytime(const int&, const double&, const double&, const double&);
    void signal_Sondary_recv_range(const float&, const double&, const double&, const double&);
    void signal_send_OBS_info(const QString&, const QString&);
    void signal_send_loadinfo(QString);
    void signal_recv_sendsignal();
    void signal_recv_recvsignal();
    void signal_recv_clicked_start();
    void signal_recv_coordsystem(const double&, const double&, const double&);
    void signal_recv_coordAfterCalculator(const double&, const double&, const double&);
    void signal_stop_information();
private:
    Ui::DeckUnit   *ui;
    QTcpSocket    *m_socket;

    QComboBox *m_SerialPortComboBox, *m_BaudRateComboBox;
    QPushButton *checkBoxSetup,*checkBoxStartTX, *pushButtonStart, *checkBoxStop;
    QPushButton *SondaryButton, *SoundcommButton;
    QLineEdit *lineEditRangeWaterMin, *lineEditRangeWaterMax;
    QLineEdit *lineEditOBSMin, *lineEditOBSMax;
    QLineEdit* lineEditZValue, *lineEditZ0Value;
    QLineEdit* lineEditX0, *lineEditY0;
    //控件
    IpAddrEdit *m_ipAddrEdit;
    QLineEdit  *m_portEdit;
    QComboBox *m_epcCbx;

    QWidget* m_optWidget;

    QSerialPort* m_SerialPort;
    QStringList m_portNameList;
    int flag;
    int restflag;
    int sondaryflag;

    QString nextpagetime,sonardynestr,soundbuf;
    double oriposX,oriposY,oriposZ,fposX,fposY,fposZ;
//    QVector<GpsCoord> m_cpsCoord;
};

#endif // DECKUNIT_H
