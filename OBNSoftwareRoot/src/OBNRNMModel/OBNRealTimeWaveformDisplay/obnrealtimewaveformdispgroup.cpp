#include "obnrealtimewaveformdispgroup.h"
#include "ui_obnrealtimewaveformdispgroup.h"

OBNRealTimeWaveformDispGroup::OBNRealTimeWaveformDispGroup(QWidget *parent) :
    QWidget(parent), m_tcpSocked(NULL),
    ui(new Ui::OBNRealTimeWaveformDispGroup)
{
    ui->setupUi(this);
    /// ====== 初始化显示界面
    initCurrentWidget();
}

OBNRealTimeWaveformDispGroup::~OBNRealTimeWaveformDispGroup()
{
    /// ====== 退出界面时,断开链接
    if(NULL != m_tcpSocked && m_tcpSocked->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        /// ====== 下发退出更新实时波形
        if(m_currentDispWaveform)
        {
            m_tcpSocked->write(realTimeWaveEndCmd, sizeof(realTimeWaveEndCmd));
        }
        /// ====== 断开链接
        m_tcpSocked->disconnectFromHost();
        m_tcpSocked->waitForDisconnected(1000);
    }
    delete ui;
}

/// ====== 初始化显示界面
void OBNRealTimeWaveformDispGroup::initCurrentWidget()
{
    nChartX = new OBNChart(this, "X");
    nChartX->setAxis(tr("X"), 0, 1000, 6, tr("Y"), 0, 100, 3);

    nChartY = new OBNChart(this, "Y");
    nChartY->setAxis(tr("X"), 0, 1000, 6, tr("Y"), 0, 100, 3);

    nChartZ = new OBNChart(this, "Z");
    nChartZ->setAxis(tr("X"), 0, 1000, 6, tr("Y"), 0, 100, 3);

    nChartH = new OBNChart(this, "H");
    nChartH->setAxis(tr("X"), 0, 1000, 6, tr("Y"), 0, 100, 3);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QVBoxLayout::SetMinimumSize);
    mainLayout->setContentsMargins(1, 1, 1, 1);
    mainLayout->addWidget(nChartX);
    mainLayout->addWidget(nChartY);
    mainLayout->addWidget(nChartZ);
    mainLayout->addWidget(nChartH);

    ui->widget->setLayout(mainLayout);
}

/// ====== 设置当前显示数据的设备ID
void OBNRealTimeWaveformDispGroup::setCurrentDeviceID(const QString& pDeviceID, const int& _prot)
{
    /// ====== 显示当前链接的设备IP地址
    ui->groupBox->setTitle(pDeviceID + "  ");

    QHostAddress address;
    address.setAddress(pDeviceID);

    /// ====== 得到用于通信的套接字
    if(NULL != m_tcpSocked)
    {
        m_tcpSocked->disconnectFromHost();
        m_tcpSocked->waitForDisconnected(1000);
    }
    m_tcpSocked = new QTcpSocket;
    m_tcpSocked->connectToHost(address, _prot);
    m_tcpSocked->waitForConnected(1000);

    //客户端发来数据就会触发readyRead信号
    connect(m_tcpSocked, &QTcpSocket::readyRead,this,[=]()
    {
        QByteArray data = m_tcpSocked->readAll();
        qDebug() << "data = " << data;
    });
}

/// ====== 开始采集
void OBNRealTimeWaveformDispGroup::startCollection()
{
    qDebug() << "开始采集";
    if(NULL != m_tcpSocked && m_tcpSocked->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        m_tcpSocked->write(realTimeWaveStartCollectionCmd, sizeof(realTimeWaveStartCollectionCmd));
    }
}

/// ====== 结束采集
void OBNRealTimeWaveformDispGroup::exitCollection()
{
    qDebug() << "结束采集";
    if(NULL != m_tcpSocked && m_tcpSocked->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        m_tcpSocked->write(realTimeWaveEndCollectionCmd, sizeof(realTimeWaveEndCollectionCmd));
    }
}

/// ====== 打开实时波形
void OBNRealTimeWaveformDispGroup::startDisplayWaveform()
{
    qDebug() << "打开实时波形";
    if(m_tcpSocked->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        if(!m_currentDispWaveform)
        {
            m_currentDispWaveform = true;
            /// ====== 启动获取实时波形数据
            m_tcpSocked->write(realTimeWaveStartCmd, sizeof(realTimeWaveStartCmd));
        }
    }
}

/// ====== 关闭实时波形
void OBNRealTimeWaveformDispGroup::stopDisplayWaveform()
{
    qDebug() << "关闭实时波形";
    if(m_tcpSocked->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        if(!m_currentDispWaveform)
        {
            return;
        }
        m_currentDispWaveform = false;
        /// ====== 下发退出更新实时波形
        m_tcpSocked->write(realTimeWaveEndCmd, sizeof(realTimeWaveEndCmd));
    }
}

/// ====== 获取当前X、Y、Z、H相关数据值
void OBNRealTimeWaveformDispGroup::getCurrentWaveformInform()
{
}


