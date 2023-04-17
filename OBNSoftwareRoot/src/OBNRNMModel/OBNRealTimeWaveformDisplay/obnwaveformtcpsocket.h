#ifndef OBNWAVEFORMTCPSOCKET_H
#define OBNWAVEFORMTCPSOCKET_H

#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QString>
#include <QByteArray>
#include <QTcpSocket>

static const char realTimeWaveStartCmd[3] = {0x3a,0x01,0x5b};   ///< 打开实时波形
static const char realTimeWaveEndCmd[3]   = {0x3a,0x01,0x5c};   ///< 关闭实时波形
static const char realTimeWaveStartCollectionCmd[3] = {0x3a,0x01,0x52};   ///< 开始采集
static const char realTimeWaveEndCollectionCmd[3]   = {0x3a,0x01,0x53};   ///< 结束采集

static const char returnWaveformTips[3] = {0x3b, 0x0d, 0x5b};

#define WAVEFORM_HEAD "3a0d5b"

class OBNWaveformTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    OBNWaveformTcpSocket(const QString&, const int&);
    /// ======
    void connectHost(const QString& ip, int port);

private:
    int calculateMeasureInform(QByteArray);

public slots:
    void slot_startConnect();   ///<

    /// ======
    void startCollection();
    void exitCollection();
    void startDisplayWaveform();
    void exitDisplayWaveform();
signals:
    void sig_connect(int);
    void sig_curent_data(int XNum, int YNum, int ZNum, int HNum);
private:
    QString m_ip;
    int     m_port;
    QByteArray m_dataInform;
    QTimer m_timer;
};

#endif // OBNWAVEFORMTCPSOCKET_H
