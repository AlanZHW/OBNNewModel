#include "obnrealtimewaveformdispgroup.h"
#include "ui_obnrealtimewaveformdispgroup.h"

OBNRealTimeWaveformDispGroup::OBNRealTimeWaveformDispGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNRealTimeWaveformDispGroup)
{
    ui->setupUi(this);
    /// ====== 初始化显示界面
    initCurrentWidget();
}

OBNRealTimeWaveformDispGroup::~OBNRealTimeWaveformDispGroup()
{
    delete ui;
}

//void OBNRealTimeWaveformDispGroup::closeEvent(QCloseEvent* event)
//{
//    /// ====== 关闭实时波形
//    emit sig_stopDisplayWaceform();
//    /// ====== 关闭采集
//    emit sig_exitCollection();
//}

/// ====== 初始化显示界面
void OBNRealTimeWaveformDispGroup::initCurrentWidget()
{

    nChartX = new OBNChart(this, "X channel");
    nChartX->setContentsMargins(0,0,0,0);
    nChartX->setAxis(tr(" "), 0, 1000, 6, tr(" "), 8000000, -8000000, 2);

    nChartY = new OBNChart(this, "Y channel");
    nChartY->setContentsMargins(0,0,0,0);
    nChartY->setAxis(tr(" "), 0, 1000, 6, tr(" "), 8000000, -8000000, 2);

    nChartZ = new OBNChart(this, "Z channel");
    nChartZ->setContentsMargins(0,0,0,0);
    nChartZ->setAxis(tr(" "), 0, 1000, 6, tr(" "), 8000000, -8000000, 2);

    nChartH = new OBNChart(this, "Fourth channel");
    nChartH->setContentsMargins(0,0,0,0);
    nChartH->setAxis(tr(" "), 0, 1000, 6, tr(" "), 8000000, -8000000, 2);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(nChartX);
    mainLayout->addWidget(nChartY);
    mainLayout->addWidget(nChartZ);
    mainLayout->addWidget(nChartH);
    this->setLayout(mainLayout);
}

/// ====== 设置当前显示数据的设备ID
void OBNRealTimeWaveformDispGroup::setCurrentDeviceID(const QString& pDeviceID, const int& _prot)
{
    m_tcpSocket = new OBNWaveformTcpSocket(pDeviceID, _prot);
    connect(m_tcpSocket, &OBNWaveformTcpSocket::sig_connect, m_tcpSocket, &OBNWaveformTcpSocket::slot_startConnect, Qt::BlockingQueuedConnection);
    m_timer = new QTimer;
    connect(m_timer, &QTimer::timeout,m_tcpSocket, &OBNWaveformTcpSocket::slot_startConnect);
    connect(m_tcpSocket,SIGNAL(sig_connect(int)),   m_timer,SLOT(start(int)));
    connect(m_tcpSocket, &OBNWaveformTcpSocket::connected,m_timer,&QTimer::stop);
    connect(this, &OBNRealTimeWaveformDispGroup::sig_startCollection,       m_tcpSocket, &OBNWaveformTcpSocket::startCollection);
    connect(this, &OBNRealTimeWaveformDispGroup::sig_exitCollection,        m_tcpSocket, &OBNWaveformTcpSocket::exitCollection);
    connect(this, &OBNRealTimeWaveformDispGroup::sig_startDisplayWaveform,  m_tcpSocket, &OBNWaveformTcpSocket::startDisplayWaveform);
    connect(this, &OBNRealTimeWaveformDispGroup::sig_stopDisplayWaceform,   m_tcpSocket, &OBNWaveformTcpSocket::exitDisplayWaveform);
    /// ======
    connect(m_tcpSocket, &OBNWaveformTcpSocket::sig_curent_data, this, [=](int _xNum, int _yNum, int _zNum, int _hNum)
    {
        nChartX->addData(_xNum);
        nChartY->addData(_yNum);
        nChartZ->addData(_zNum);
        nChartH->addData(_hNum);
    });
    m_thread = new QThread;
    m_tcpSocket->moveToThread(m_thread);
    m_timer->moveToThread(m_thread);
    m_thread->start();
}

/// ====== 开始采集
void OBNRealTimeWaveformDispGroup::startCollection()
{
    emit sig_startCollection();
}

/// ====== 结束采集
void OBNRealTimeWaveformDispGroup::exitCollection()
{
    emit sig_exitCollection();
}

/// ====== 打开实时波形
void OBNRealTimeWaveformDispGroup::startDisplayWaveform()
{
    emit sig_startDisplayWaveform();
}

/// ====== 关闭实时波形
void OBNRealTimeWaveformDispGroup::stopDisplayWaveform()
{
    emit sig_stopDisplayWaceform();
}

/// ====== 获取当前X、Y、Z、H相关数据值
void OBNRealTimeWaveformDispGroup::getCurrentWaveformInform()
{
}


