#include "nodequery.h"
#include <QHostAddress>
#include <QDebug>
#include <QDateTime>

#define Socket_WaitForConnect_Time 1
#define TCP_IP_PORT                5000

//最小查询延迟
#define Max_Query_Delay            30000

#include "rnitems.h"

// ====== 获取仓温
static const char tempCmd[3] = {0x3a,0x01,0x60};
// ====== 获取仓压
static const char pressCmd[3] = {0x3a,0x01,0x61};
// ====== 获取电压，工作电流，充电电压
static const char voltCmd[3] = {0x3a,0x01,0x62};
/// ======获取姿态
static const char angleCmd[3] = {0x3a,0x01,0x64};
static const char angleCmd2[3] = {0x3a,0x01,0x6A};
/// ======标定指令
static const char startCalibrationCmd[3] = {0x3a,0x01,0x6D};  ///<标定
static const char endCalibrationCmd[3]   = {0x3a,0x01,0x6E};  ///<取消标定
/// ======设置D
static const char setDCMD[5] = {0x3A, 0x02, (char)130, 0x32, 0x00};
/// ======获取D
static const char getDCMD[3] = {0x3A, 0X01, (char)128};
/// ======开始驯服
static const char startAtomicClockTame[3] = {0x3A, 0x01, 0x6E};
/// ======获取原子钟信息
static const char getAtomicClock[3] = {0x3A, 0x01, 0x6F};
/// ======退出驯服
static const char endAtomicClockTame[3] = {0x3A, 0x01, (char)129};

NodeQuery::NodeQuery(Node *owner)
    :QTcpSocket(owner),m_queryStep(NoQuery)
    ,m_running(false),m_count(0), m_stoped(true)
{
    connect(this, SIGNAL(readyRead()),    this, SLOT(slotReadData()));
    connect(this, SIGNAL(connected()),    this, SLOT(slotConnected()));
    connect(this, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));

    /// ====== 调整获取连接状态模式
    m_updateConnectTimer.setInterval(10000);
    connect(&m_updateConnectTimer, &QTimer::timeout, this, [=](){
        getCurrentConnectState();
    });
    m_updateConnectTimer.start();

    /// ====== 获取设备信息
    m_updateDeviceInfoTimer.setInterval(30000);
    connect(&m_updateDeviceInfoTimer, &QTimer::timeout, this, [=]{
        getCurrentDeviceInform();
    });
    m_updateDeviceInfoTimer.start();

    /// ====== 驯服定时器
    m_tameTimer.setInterval(600000);
    connect(&m_tameTimer, &QTimer::timeout, this, [=]{
        /// ====== 停止定时器
        m_tameTimer.stop();
        /// ====== 下发停止驯服指令
        endAtomicClockTameFunction();
        /// ====== 设置颜色为驯服失败
        m_node->setTameState(-1);
    });
    /// ======
    m_node = owner;

    QTimer::singleShot(1000, this, [=](){
        /// ====== 初始化获取一次连接状态
        getCurrentConnectState();
        /// ====== 初始化获取一次设备信息
        getCurrentDeviceInform();
    });
}

NodeQuery::~NodeQuery()
{
    if(this->state() == SocketState::ConnectedState)
    {
        this->disconnectFromHost();
        m_running = false;
    }
}

void NodeQuery::getCurrentConnectState()///<获取当前设备连接状态
{
    if(NULL != this->m_node)
    {
        #ifdef Q_OS_WIN
                    QString argsInform = " -n 1 -w 5 ";
        #else
                    QString argsInform = " -c 1 -t 1 -q";
        #endif
        QHostAddress addr;
        addr.setAddress(this->m_node->ip());

        QString cmdStr = "ping " + addr.toString() + argsInform;
        int exitCode = QProcess::execute(cmdStr);
        if(0 == exitCode)
        {
            m_node->setState(true);
        }
        else
        {
            m_node->setState(false);
        }
        m_node->updateNode();
    }
}

void NodeQuery::getCurrentDeviceInform()///<获取当前设备信息
{
    if(NULL != m_node && true == m_node->state())
    {
        startQuery();
    }
}

/// ====== 标定
void NodeQuery::startNodeQueryCalibrationFunction()
{
    if(this->state() == SocketState::ConnectedState)
    {
        write(startCalibrationCmd,sizeof(startCalibrationCmd));
        m_queryStep = StartCalibration;
        m_updateDeviceInfoTimer.stop();
    }
}
/// ====== 取消标定
void NodeQuery::endNodeQueryCalibrationFunction()
{
    if(this->state() == SocketState::ConnectedState)
    {
        write(endCalibrationCmd,sizeof(endCalibrationCmd));
        m_queryStep = EndCalibration;
        m_updateDeviceInfoTimer.start();
    }
}

/// ====== 设置D
void NodeQuery::setDValueFunction()
{
    qDebug() << "设置D";
    if(this->state() == SocketState::ConnectedState)
    {
        write(setDCMD,sizeof(setDCMD));
        m_queryStep = QuerySetD;
    }
}

/// ====== 获取D
void NodeQuery::getDValueFunction()
{
    qDebug() << "获取D";
    if(this->state() == SocketState::ConnectedState)
    {
        write(getDCMD,sizeof(getDCMD));
        m_queryStep = QueryGetD;
    }
}

/// ======启动原子钟驯服
void NodeQuery::startAtomicClockTameFunction()
{
    qDebug() << "启动原子钟驯服";
    if(this->state() == SocketState::ConnectedState)
    {
        write(startAtomicClockTame,sizeof(startAtomicClockTame));

        m_queryStep = QueryGetAtomic;
        /// ===== 打开获取设备信息定时器
        m_updateDeviceInfoTimer.stop();
        /// ======  设置状态为正在驯服
        m_node->setTameState(2);
        /// ====== 启动退出驯服定时器
        m_tameTimer.start();
    }
}

/// ====== 停止原子钟驯服
void NodeQuery::endAtomicClockTameFunction()
{
    qDebug() << "退出原子钟驯服";
    if(this->state() == SocketState::ConnectedState)
    {
        write(endAtomicClockTame,sizeof(endAtomicClockTame));
        m_queryStep = NoQuery;
        /// ======
        m_updateDeviceInfoTimer.start();
        /// ======
        m_tameTimer.stop();
        /// ====== 设置颜色为未驯服
        m_node->setTameState(0);
    }
}

void NodeQuery::reConnect()
{
#if 0
    QDateTime current_time = QDateTime::currentDateTime();
    QString StrCurrentTime = current_time.toString("hh:mm:ss");
    flush();
    abort();
    if(state() == QAbstractSocket::UnconnectedState)
    {
        this->disconnectFromHost();
        this->waitForDisconnected(1000);
        connectToHost(QHostAddress(m_node->ip()),TCP_IP_PORT);
        if(this->waitForConnected(1000))
        {
            qDebug("connected!");
        }
    }
#endif
}

void NodeQuery::disConnect()
{
    this->disconnectFromHost();
    m_running = false;
}

void NodeQuery::start(const int &interval)
{
    m_interval = interval;
    m_stoped   = false;
#if 1
    connectToHost(QHostAddress(m_node->ip()),TCP_IP_PORT);
    this->waitForConnected(1000);
#else
    QTcpSocket* nTcp = new QTcpSocket;
    nTcp->connectToHost(QHostAddress(m_node->ip()),TCP_IP_PORT);
    if(nTcp->waitForConnected(1000))
    {
        if(sizeof(voltCmd) != nTcp->write(voltCmd,sizeof(voltCmd)))
            qDebug() << __LINE__ << "\t send faile!";
        else
            qDebug() << __LINE__ << "\t send success!";
    }
#endif
}

void NodeQuery::stop()
{
    m_count = 0;
    flush();
    m_stoped = true;
    this->abort();
    m_running = false;
}

void NodeQuery::refresh()
{
    //两种节点状态处理
    //1)节点状态为 false
    if(NULL != m_node && !m_node->state())
    {
        m_count ++;
        /// ====== 当前状态为false的节点,几个周期查询链接一次，降低频率
        if(m_count*m_interval >= Max_Query_Delay)
        {
            reConnect();
            m_count = 0;
        }
        startQuery();
        return;
    }
//    else
//    {
//        //节点正在运行,可能是通讯中断，需要重新刷新链接启动
//        if(m_running)
//        {
//            m_running = false;
//            reConnect();
//            return;
//        }
//    }
}

void NodeQuery::startQuery()
{
    if(this->state() != QAbstractSocket::ConnectedState)
    {
        return;
    }
    m_running = true;
    t.start();
    /// ====== 启动查询,从电压-仓温-仓压顺序查询
    write(voltCmd, sizeof(voltCmd));
    m_queryStep = QueryVoltage;
}

void NodeQuery::slotReadData()
{
    quint16 iData;
    quint32 bdata;
    QByteArray byteArray = this->readAll();
    QString temp;
qDebug() << "byteArray is:"   << byteArray << "m_queryStep is:" << m_queryStep;
    if(m_queryStep == QueryVoltage)
    {
        //电压
        iData = (((byteArray[4]&0xff)<<8)|(byteArray[3]&0xff));
        temp = QString::number(iData);
        qDebug() << "电压 = " << temp;
        m_node->setVoltage(temp.toFloat()/1000.f);

        //工作电流
        iData=(((byteArray[6]&0xff)<<8)|(byteArray[5]&0xff));
        temp = QString::number(iData);
        qDebug() << "工作电流 = " << temp;
        m_node->setCurrent(temp.toFloat()/1000.f);

        //充电电压
        iData=(((byteArray[8]&0xff)<<8)|(byteArray[7]&0xff));
        temp = QString::number(iData);
        qDebug() << "充电电压 = " << temp;
        m_node->setChargeVolt(temp.toFloat()/1000.f);

        //查询仓温
        write(tempCmd,sizeof(tempCmd));
        m_queryStep = QueryTemp;
        return;
    }
    if(m_queryStep == QueryTemp)
    {
        //仓温
        iData = (((byteArray[4]&0xff)<<8)|(byteArray[3]&0xff));
        temp = QString::number(iData);
        qDebug() << "仓温 = " << temp;
        m_node->setTemperature(temp.toFloat()/10.f);
        //查询仓压
        write(pressCmd,sizeof(pressCmd));
        m_queryStep = QueryPressure;
        return;
    }
    if( m_queryStep == QueryPressure)
    {
        //仓压
        bdata = ((byteArray[3]&0xff)|((byteArray[4]&0xff)<<8)|((byteArray[5]&0xff)<<16)|((byteArray[6]&0xff)<<24));
        temp = QString::number(bdata);
        qDebug() << "仓压 = " << temp;
        m_node->setPressure(temp.toFloat()/101325.0f);
        //结束--------------------------------
        m_queryStep = NoQuery;
        m_running = false;
        //更新显示状态
        m_node->updateNode(State_Update);

        //查询姿态(俯仰角和翻滚角数据)
        write(angleCmd,sizeof(angleCmd));
        m_queryStep = QueryAngle1;
        return;
    }
    if(QueryAngle1 == m_queryStep)   // ====== 查询姿态
    {
        /// ======解析俯仰角和翻滚角数据
        bdata = (byteArray[3]&0xff)|((byteArray[4]&0xff)<<8);
        temp = QString::number(bdata);
        qDebug() << "俯仰角 = " << temp;
        m_node->setPitchAngle(temp.toFloat());

        /// ======解析俯仰角和翻滚角数据
        bdata = (byteArray[5]&0xff)|((byteArray[6]&0xff)<<8);
        temp = QString::number(bdata);
        qDebug() << "翻滚角 = " << temp;
        m_node->setRollAngle(temp.toFloat());

        //查询姿态(方位角)
        write(angleCmd2,sizeof(angleCmd2));
        m_queryStep = QueryAngle2;
        return;
    }
    if(QueryAngle2 == m_queryStep)
    {
        /// ====== 解析方位角数据
        bdata = (byteArray[3]&0xff)|((byteArray[4]&0xff)<<8);
        temp = QString::number(bdata);
        qDebug() << "方位角 = " << temp;
        m_node->setAzimuthAngle(temp.toFloat());

        m_queryStep = NoQuery;
    }
    if(QueryGetAtomic == m_queryStep)
    {
        QString nCurrentData = byteArray.trimmed();
        QStringList nCurentDataList = nCurrentData.split(",");
        if(13 < nCurentDataList.count())
        {
            QString nState = nCurentDataList[13];
            qDebug() << "nState = " << nState;
            if(nState >= '0' && nState <= '9')
            {
                if(1 == nState.toInt())
                {
                    /// ====== 设置退出原子钟驯服
                    endAtomicClockTameFunction();
                    /// ======  设置状态为驯服成功
                    m_node->setTameState(1);
                    /// ======
                    m_queryStep = NoQuery;
                }
            }
        }
        QTimer::singleShot(2000, this, [=](){
            write(getAtomicClock,sizeof(getAtomicClock));
        });
    }
    if(StartCalibration == m_queryStep)
    {
    }
    if(EndCalibration == m_queryStep)
    {
    }
}

void NodeQuery::slotConnected(){
    QDateTime current_time = QDateTime::currentDateTime();
    QString StrCurrentTime = current_time.toString("hh:mm:ss");
}

void NodeQuery::slotDisconnected(){
    QDateTime current_time = QDateTime::currentDateTime();
    QString StrCurrentTime = current_time.toString("hh:mm:ss");
    qDebug() << "slotDisconnected ...... StrCurrentTime =" <<StrCurrentTime;
}

//void NodeQuery::slotStateChanged(QAbstractSocket::SocketState state)
//{
//    if(state == QAbstractSocket::UnconnectedState)
//    {
//        if(!m_stoped)
//        {
//            m_node->setState(false);
//            m_node->updateNode();
//        }
//    }
//    else if(state == QAbstractSocket::ConnectedState)
//    {
//        //开始查询
//        m_node->setState(true);
//        m_node->updateNode();
//        startQuery();
//    }
//}



