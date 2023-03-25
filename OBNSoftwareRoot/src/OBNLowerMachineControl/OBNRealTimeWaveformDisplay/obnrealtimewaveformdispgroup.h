#ifndef OBNREALTIMEWAVEFORMDISPGROUP_H
#define OBNREALTIMEWAVEFORMDISPGROUP_H

#include "obnchart.h"
#include "obnrealtimewaveformdisplaypublic.h"

#include <QList>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHBoxLayout>


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
    void setCurrentDeviceID(const QString& pDeviceID);
    /// ====== 获取当前X、Y、Z、H相关数据值
    void getCurrentWaveformInform();

private:
    QList<WaveformInformSuct> m_waveformInformList;
    OBNChart *nChartX, *nChartY, *nChartZ, *nChartH;
    Ui::OBNRealTimeWaveformDispGroup *ui;
};

#endif // OBNREALTIMEWAVEFORMDISPGROUP_H
