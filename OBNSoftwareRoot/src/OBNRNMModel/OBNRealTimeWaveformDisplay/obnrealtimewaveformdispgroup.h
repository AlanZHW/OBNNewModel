#ifndef OBNREALTIMEWAVEFORMDISPGROUP_H
#define OBNREALTIMEWAVEFORMDISPGROUP_H

#include "obnchart.h"
#include "obnrealtimewaveformpublic.h"

#include <QList>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHBoxLayout>

static const char realTimeWaveStartCmd[3] = {0x3a,0x01,0x5b};   ///< 打开实时波形
static const char realTimeWaveEndCmd[3]   = {0x3a,0x01,0x5c};   ///< 关闭实时波形
static const char realTimeWaveStartCollectionCmd[3] = {0x3a,0x01,0x52};   ///< 开始采集
static const char realTimeWaveEndCollectionCmd[3]   = {0x3a,0x01,0x53};   ///< 结束采集

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
private:
    QTcpSocket* m_tcpSocked;
    bool m_currentDispWaveform = false;
    OBNChart *nChartX, *nChartY, *nChartZ, *nChartH;
    Ui::OBNRealTimeWaveformDispGroup *ui;
};

#endif // OBNREALTIMEWAVEFORMDISPGROUP_H
