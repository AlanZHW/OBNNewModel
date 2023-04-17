#include "rnmpublic.h"

#include <QHostAddress>

#include "nodequery.h"
#include "nodeftp.h"
#include "rnitems.h"
#include "rnftpmanager.h"
#include "statusreport.h"

const QColor state_color[6] = {
    Node_Status_Disable_Color,
    Node_Status_Normal_Color,
    Node_Status_Warning_Color,
    Node_Status_Error_Color,
    Node_SelfTest_Warning_Color,
    Node_Downloaded_Color
};


//起始地址
static const uint startIp = QHostAddress("192.168.137.0").toIPv4Address();

bool isNodeIP(const uint &ipV4)
{
    uint val  = ipV4 - startIp;
    uint temp = val%256;
    return temp;    ///< 发送所有解析的节点ip地址

    // 每个网段的100-200为节点的IP地址
    // return (100 <= temp && temp<200);
}

uint ip2DeviceNo(const uint &ipV4)
{
    uint temp = ipV4 - startIp;
//    return (temp/256)*2 + ((temp%256)-2);
    return (temp/256)*2+(temp%256);
}

QString workName(const int &work)
{
    if(work == Updating)
        return "Updating";
    else if(work == DownLoadFiles)
        return "Downloading Files";
    else if(work == ClearMemory)
        return "Clearing Files";
    else if(work == SetSampleFrequecy)
        return "Setting Sample Frequency";
    else //None Work
        return "";
}

//Node----------------------------------------
Node::Node(QObject *parent)
    :QObject(parent),m_nodeQuery(0)
{
    //6种状态当前对应的颜色
    m_colors = new QColor[7];
    //根据节点链接状态判断是否创建查询
    m_nodeQuery = new NodeQuery(this);

    //参数状态
    for(int i = 0; i < 7; i ++)
    {
        m_state[i] = Normal;
    }
    m_state[7] =  Disable;

    m_ftpManager    = new FtpManager(this);
    m_downloadState = NoDownload;
    m_ftpError      = NoError;

    /// ====== 设定时间为10分钟保存一次当前设备信息
    mSaveDeviceInformTimer.setInterval(600000);
    connect(&mSaveDeviceInformTimer, &QTimer::timeout, this, [=](){
        functionSaveNodeDeviceInform();
    });
}

Node::~Node()
{
    if(m_nodeQuery)
        m_nodeQuery->stop();
    delete[] m_colors;
}

/// ======
void Node::startSaveNodeDeviceInform()
{
    mSaveDeviceInformTimer.start();
    /// ====== 启动定时器后先自动存储一次
    functionSaveNodeDeviceInform();
}
void Node::stopSaveNodeDeviceInform()
{
    mSaveDeviceInformTimer.stop();
    /// ====== 退出定时器时,保存一下最新的信息
    functionSaveNodeDeviceInform();
}
void Node::functionSaveNodeDeviceInform()
{
    /// ====== 判断路径是否存在,如果路径不存在则创建
    QString devicefDir  = m_projectInfoNode.ProjectPath + "/data/G" + QString::number(nodeData.no);
    QDir dir(devicefDir);
    if(!dir.exists())
    {
        dir.mkdir(devicefDir);
    }
    QString devicefName = devicefDir + "/node.info";
    qDebug() << __FILE__ << "\t" << __LINE__ << "\t devicefName = " << devicefName << "\t nodeData.no = " << nodeData.no;
    FILE *fpDevice = NULL;
    fpDevice = fopen(devicefName.toStdString().c_str(), "w");
    if(NULL != fpDevice)
    {
        fprintf(fpDevice, "设备编号:G%d\n", nodeData.no);
        fprintf(fpDevice, "ip:%d\n", nodeData.ip);
        fprintf(fpDevice, "链接状态:%d\n", nodeData.state);
        fprintf(fpDevice, "电压:%f\n", nodeData.sVoltage);
        fprintf(fpDevice, "温度:%f\n", nodeData.sTemper);
        fprintf(fpDevice, "舱压:%f\n", nodeData.sPress);
        fprintf(fpDevice, "工作电流:%f\n", nodeData.sEleCurr);
        fprintf(fpDevice, "充电电压:%f\n", nodeData.sChargeVolt);
        fprintf(fpDevice, "存储容量:%f\n", nodeData.sMemory);
        fprintf(fpDevice, "下载进度:%d\n", nodeData.downloadPercent);
        fprintf(fpDevice, "采样频率:%d\n", nodeData.sampleFrequency);
        fprintf(fpDevice, "是否下载完成:%d\n", nodeData.downloaded);
        fprintf(fpDevice, "驯服状态:%d\n", nodeData.tameState);
        fprintf(fpDevice, "俯仰角:%f\n", nodeData.pitchAngle);
        fprintf(fpDevice, "翻滚角:%f\n", nodeData.rollAngle);
        fprintf(fpDevice, "方位角:%f\n", nodeData.azimuthAngle);
        fclose(fpDevice);
    }
}

void Node::startRefresh(const int &interval)
{
    //参数更新开始
    m_nodeQuery->start(interval);
}

void Node::stopRefresh()
{
    m_nodeQuery->stop();
}

void Node::refreshState()
{
    m_nodeQuery->refresh();
}

/// ======启动原子钟驯服
void Node::nodeStartAtomicClockTameFunction()
{
    m_nodeQuery->startAtomicClockTameFunction();
}

void Node::nodeEndAtomicClockTameFunction()
{
    m_nodeQuery->endAtomicClockTameFunction();
}

void Node::nodeSetDFunction(const int& index)
{
    m_nodeQuery->setDValueFunction(index);
}

void Node::nodeGetDFunction()
{
    m_nodeQuery->getDValueFunction();
}

void Node::nodeCalibrationFunction(const bool _isCalibration)
{
    if(_isCalibration)
        m_nodeQuery->startNodeQueryCalibrationFunction();
    else
        m_nodeQuery->endNodeQueryCalibrationFunction();

}

bool Node::isRunning() const
{
    return m_nodeQuery&&m_nodeQuery->isRunning();
}

void Node::updateNode(const UpdateCmd &updateCmd)
{
    if(updateCmd & State_Update)
    {
        /// ====== 调用状态控制器计算每个参数状态
        m_stCtrler->calNodeState(this);

        int filter = state()?m_stCtrler->displayFilter():0;
        State st = m_state[filter];
        qDebug() << "filter = " << filter << "\t st = " << st;
        /// ====== 项显示更新----------------
        if(nullptr != nodeItem)
        {
            nodeItem->updateNode(state_color[st]);
        }
        /// ====== 向中介传递更新信息
        m_nodeMediator->nodeToStatusReport(updateCmd,this);
    }
    if(updateCmd & Ftp_Update)
    {
        //向中介传递更新信息
        m_nodeMediator->nodeToFtpManagerMsg(this,updateCmd);
    }
}

void Node::startFtpWork(const FtpWork &ftpWk,const QVariant &arg)
{
    qDebug() << __FILE__ << "\t" << __LINE__ << __FUNCTION__;
    m_ftpManager->startWork(ftpWk,arg);
}

void Node::setTimerInfo(const QString &startTime,const QString &endTime, const QString &SampInterPer)
{
    m_ftpManager->setTimerInfo(startTime, endTime, SampInterPer);
}

void Node::stopFtpWork()
{
    m_ftpManager->stopFtpWork();
}

void Node::finishedFtpWork(const int &ftpWk,const bool &err)
{
    m_nodeMediator->finishedFtpWork(this,ftpWk,err);
}


Node::NodeData::NodeData()
    :no(0),ip(0)
    ,state(false)
    ,sVoltage(0.0)
    ,sTemper(0.0)
    ,sPress(0.0)
    ,sEleCurr(0.0)
    ,sChargeVolt(0.0)
    ,sMemory(0.0)
    ,downloadPercent(0)
    ,sampleFrequency(1000)
    ,downloaded(false),
    tameState(0),
    pitchAngle(0),     // 俯仰角
    rollAngle(0),      // 翻滚角
    azimuthAngle(0)   // 方位角
{

}

//状态控制--------------------------------------------
void StatusControler::setFilters(const int &status)
{
    m_filters = status;
    //更新---------------------------
    foreach (Node *node, m_nodes)
    {
        node->updateNode(State_Update);
    }
}

void StatusControler::setLimitData(const QVector<LimitData> &limitData)
{
    m_LimitData = limitData;
    //更新
    qDebug()<<"LimitData:"<<limitData.size();
    foreach (Node *node, m_nodes)
    {
        node->updateNode(State_Update);
    }
}

void StatusControler::setNodes(QVector<Node *> nodes)
{
    m_nodes = nodes;
}

void StatusControler::calNodeState(Node *node)
{
    //QString nodeName = QString("G%1").arg(node->no(),3,10,QChar('0'));
    //节点状态
    Node::State  *stateVale = node->stateValue();
    if(!node->state())
    {
        stateVale[0] = Node::Disable;
        return;
    }
    ///
    stateVale[0] = Node::Normal;
    /// 自检状态
    stateVale[5] = Node::SelfTest_Ok;
    /// voltage
    stateVale[1] = calState(node->voltage(),m_LimitData[0]);
    if(stateVale[1] != Node::Normal)
    {
        stateVale[5] = Node::SelfTest_Warning;
    }
    //temperature
    stateVale[2] = calState(node->temperature(),m_LimitData[1]);
    if(stateVale[2] != Node::Normal)
    {
        stateVale[5] = Node::SelfTest_Warning;
    }
    //pressure
    stateVale[3] = calState(node->pressure(),m_LimitData[2]);
    if(stateVale[3] != Node::Normal)
    {
        stateVale[5] = Node::SelfTest_Warning;
    }
    //memory
    stateVale[4] = calState(node->memory(),m_LimitData[3]);
    if(stateVale[4] != Node::Normal)
    {
        stateVale[5] = Node::SelfTest_Warning;
    }
    /// download
    stateVale[6] = node->isDownloaded()?Node::Downloaded:Node::Normal;

    /// ====== 原子钟相关
    switch (node->currentTameState())
    {
    case -1:
        stateVale[7] = Node::TameFailed;    ///< 驯服失败
        break;
    case 0:
        stateVale[7] = Node::TameNormal;    ///< 未开始驯服
        break;
    case 1:
        stateVale[7] = Node::TameSuccess;   ///< 驯服成功
        break;
    case 2:
        stateVale[7] = Node::TameRunning;   ///< 正在驯服
        break;
    default:
        break;
    }
}

Node::State StatusControler::calState(const float &value,const LimitData &limit)
{
    //计算颜色,红黄绿--------------------------
    if(limit.operate == Big)
    {
        if(value<=limit.first)
            return Node::Normal;
        else if (value>limit.second)
            return Node::State_Error;
        else
            return Node::State_Warning;
    }
    else
    {
        if(value<limit.second)
            return Node::State_Error;
        else if (value>=limit.first)
            return Node::Normal;
        else
            return Node::State_Warning;
    }
}




//NodeMediator 节点中介----
NodeMediator::NodeMediator(QObject *parent)
    :QObject(parent),m_ftpManager(0)
{

}

void NodeMediator::setRNFtpManager(RNFtpManager  *ftpManager)
{
    m_ftpManager = ftpManager;
}

void NodeMediator::setStatusReport(StatusReportDlg *statusReport)
{
    m_statusReport = statusReport;
}

void NodeMediator::setNodes(const QVector<Node*> &nodes)
{
    m_nodes = nodes;
}

void NodeMediator::nodeToStatusReport(const UpdateCmd &msg,Node *node)
{
    if(m_statusReport)
    {
        m_statusReport->getMessage(msg,node);
    }
}

void NodeMediator::nodeToFtpManagerMsg(Node *node,const UpdateCmd &msg)
{
    if(m_ftpManager)
    {
        m_ftpManager->getMessage(node,msg);
    }
}



void NodeMediator::finishedFtpWork(Node *node,const int &ftpWk,const bool &err)
{
    if(m_ftpManager)
        m_ftpManager->finishedFtpWork(node,ftpWk,err);
}

