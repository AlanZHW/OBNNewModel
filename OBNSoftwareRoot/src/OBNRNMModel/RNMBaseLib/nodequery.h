#ifndef NODEQUERY_H
#define NODEQUERY_H

#include <QTimer>
#include <QTcpSocket>
#include "projectarea.h"

#include "rnmpublic.h"

class NodeItem;
class NodeQuery : public QTcpSocket
{
    Q_OBJECT
public:
    enum QueryStep
    {
        NoQuery        = 0,     ///<无
        QueryVoltage   = 1,     ///<查询电流电压相关信息
        QueryTemp      = 2,     ///<查询仓温信息
        QueryPressure  = 3,     ///<查询仓压信息
        QueryAngle1    = 4,     ///<查询俯仰角,翻滚角
        QueryAngle2    = 5,     ///<查询方位角
        QuerySetD      = 6,     ///<设置D
        QueryGetD      = 7,     ///<查询D
        QueryGetAtomic = 8,     ///<原子钟驯服相关
        StartCalibration = 9,   ///<开始标定
        EndCalibration = 10,    ///<结束标定
        QueryMemoryInform = 11  ///<查询内存信息
    };
    NodeQuery(Node *owner);
    ~NodeQuery();
    void start(const int &interval);
    void stop();
    void refresh();
    //重连/断开-------
    void disConnect();

    const bool &isRunning(){return m_running;}

    /// ====== 原子钟驯服相关函数
    void setDValueFunction(const int& index);
    void getDValueFunction();
    void startAtomicClockTameFunction();
    void endAtomicClockTameFunction();
    /// ====== 标定相关
    void endNodeQueryCalibrationFunction();
    void startNodeQueryCalibrationFunction();
private:
    void getCurrentConnectState();///<获取当前设备连接状态
    void getCurrentDeviceInform();///<获取当前设备信息
private slots:
    void slotReadData();
    void slotConnected();
    void slotDisconnected();
private:
    void       startQuery();
    QTimer     m_updateConnectTimer;
    QTimer     m_updateDeviceInfoTimer;
    QTimer     m_tameTimer;
    QueryStep  m_queryStep;
    bool       m_running;
    Node       *m_node;
    int        m_count;
    int        m_interval; //刷新间隔
    QTime      t;
    bool       m_stoped;
};

#endif // NODEQUERY_H
