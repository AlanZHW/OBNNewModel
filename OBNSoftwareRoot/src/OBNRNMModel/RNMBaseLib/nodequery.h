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
        NoQuery        = 0,
        QueryVoltage   = 1,
        QueryTemp      = 2,
        QueryPressure  = 3,
        QueryAngle1    = 4, ///<姿态
        QueryAngle2    = 5, ///<姿态2
        QuerySetD      = 5,
        QueryGetD      = 6,
        QueryGetAtomic = 7,
        StartCalibration = 8,
        EndCalibration = 9
    };
    NodeQuery(Node *owner);
    ~NodeQuery();
    void start(const int &interval);
    void stop();
    void refresh();
    //重连/断开-------
    void reConnect();
    void disConnect();

    const bool &isRunning(){return m_running;}

    /// ====== 原子钟驯服相关函数
    void setDValueFunction();
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
