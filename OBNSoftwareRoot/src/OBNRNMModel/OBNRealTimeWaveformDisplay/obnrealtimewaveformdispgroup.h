#ifndef OBNREALTIMEWAVEFORMDISPGROUP_H
#define OBNREALTIMEWAVEFORMDISPGROUP_H

#include "obnchart.h"
#include "obnwaveformtcpsocket.h"

#include <QList>
#include <QTimer>
#include <QThread>
#include <QWidget>
#include <QTcpSocket>
#include <QHBoxLayout>
#include <QHostAddress>


namespace Ui {
class OBNRealTimeWaveformDispGroup;
}

class OBNRealTimeWaveformDispGroup : public QWidget
{
    Q_OBJECT
public:
    /// ======
    explicit OBNRealTimeWaveformDispGroup(QWidget *parent = nullptr);
    /// ======
    ~OBNRealTimeWaveformDispGroup();
    /// ======
    void initCurrentWidget();
    /// ====== 设置当前显示数据的设备ID
    void setCurrentDeviceID(const QString&, const int&);
    /// ====== 获取当前X、Y、Z、H相关数据值
    void getCurrentWaveformInform();
    /// ====== 开始采集数据
    void startCollection();
    /// ====== 结束采集
    void exitCollection();
    /// ====== 打开实时波形
    void startDisplayWaveform();
    /// ====== 关闭实时波形
    void stopDisplayWaveform();

signals:
    void sig_startCollection();
    void sig_exitCollection();
    void sig_startDisplayWaveform();
    void sig_stopDisplayWaceform();

private:
    /// ====== 用于与底层通信的socket
    OBNWaveformTcpSocket* m_tcpSocket;
    QTimer* m_timer;
    QThread* m_thread;

    OBNChart *nChartX, *nChartY, *nChartZ, *nChartH;
    Ui::OBNRealTimeWaveformDispGroup *ui;
};

#endif // OBNREALTIMEWAVEFORMDISPGROUP_H
