#include "obnrealtimewaveroot.h"
#include "ui_obnrealtimewaveroot.h"

OBNRealTimeWaveRoot::OBNRealTimeWaveRoot(QWidget *parent) :
    QMainWindow(parent),m_obnSeatchHosts(NULL),m_obsHostInformSetup(NULL),
    ui(new Ui::OBNRealTimeWaveRoot)
{
    ui->setupUi(this);
    setWindowTitle(tr("实时波形显示"));
    setWindowState(Qt::WindowMaximized);

    initWindow();
}

OBNRealTimeWaveRoot::~OBNRealTimeWaveRoot()
{
    delete ui;
}

void OBNRealTimeWaveRoot::initWindow()
{
    QString m_Path = QCoreApplication::applicationDirPath();

    ui->toolBar->addAction(QIcon(m_Path+"/Image/search.png"), tr("筛选可用节点"), this, [=](){
        if(NULL == m_obnSeatchHosts)
        {
            m_obnSeatchHosts = new ONBRetrieveAvailableNodes(this);
            connect(m_obnSeatchHosts, &ONBRetrieveAvailableNodes::signalCurrentHostsSend, this, [=](QVector<HostsState> hostStateVecotr){
                QStringList nCurrentHostIDList;
                for(int iList = 0; iList < hostStateVecotr.count(); iList ++)
                {
                    QString nHostID = hostStateVecotr[iList].ip;
                    nCurrentHostIDList.append(nHostID);
                }
                if(NULL != m_obsHostInformSetup)
                {
                    delete m_obsHostInformSetup;
                    m_obsHostInformSetup = NULL;
                }
                m_obsHostInformSetup = new OBNRealTimeWaveformSetup(this);
                connect(m_obsHostInformSetup, &OBNRealTimeWaveformSetup::signalCurrentTcpInformList, this, [=](const QList<TCPInform>& _tcpInformList){
                    setCurrentAvailableHostInformList(_tcpInformList);
                    m_obsHostInformSetup->close();
                });
                m_obsHostInformSetup->setCurrentHostInform(nCurrentHostIDList);
                m_obsHostInformSetup->open();
            });
        }
        m_obnSeatchHosts->open();
    });

    ui->toolBar->addSeparator();

    m_actionStartCollection = new QAction(QIcon(m_Path+"/Image/start.png"), tr("开始/停止采集"));
    ui->toolBar->addAction(m_actionStartCollection);
    connect(m_actionStartCollection, &QAction::triggered, this, [=](const bool){
        if(!m_curentCollecting)
        {
            m_curentCollecting = true;
            for(int iList = 0; iList < m_waveDispGroup.count(); iList ++)
            {
                m_waveDispGroup[iList]->startCollection();
            }
            m_actionStartCollection->setIcon(QIcon(m_Path+"/Image/stop.png"));
            m_actionStartDispWaveform->setEnabled(true);
        }
        else
        {
            m_curentCollecting = false;
            for(int iList = 0; iList < m_waveDispGroup.count(); iList ++)
            {
                m_waveDispGroup[iList]->exitCollection();
            }
            m_actionStartCollection->setIcon(QIcon(m_Path+"/Image/start.png"));
            m_actionStartDispWaveform->setEnabled(false);
        }
    });

    ui->toolBar->addSeparator();

    m_actionStartDispWaveform = new QAction(QIcon(m_Path+"/Image/start.png"), tr("开始/停止显示"));
    ui->toolBar->addAction(m_actionStartDispWaveform);
    m_actionStartDispWaveform->setEnabled(false);
    connect(m_actionStartDispWaveform, &QAction::triggered, this, [=](const bool){
        if(m_curentDispWaveform)
        {
            m_curentDispWaveform = false;
            for(int iList = 0; iList < m_waveDispGroup.count(); iList ++)
            {
                m_waveDispGroup[iList]->stopDisplayWaveform();
            }
            m_actionStartDispWaveform->setIcon(QIcon(m_Path+"/Image/start.png"));
        }
        else
        {
            m_curentDispWaveform = true;
            for(int iList = 0; iList < m_waveDispGroup.count(); iList ++)
            {
                m_waveDispGroup[iList]->startDisplayWaveform();
            }
            m_actionStartDispWaveform->setIcon(QIcon(m_Path+"/Image/stop.png"));
        }
    });
}

/// ====== 设置当前可用设备列表
void OBNRealTimeWaveRoot::setCurrentAvailableHostInformList(const QList<TCPInform> & pHostInformList)
{
    if(0 != m_waveDispGroup.count())
    {
        m_waveDispGroup.clear();
    }

    QScrollArea* mScrollArea = new QScrollArea;
    mScrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    mScrollArea->setWidgetResizable(true);

    QVBoxLayout* nVBoxLayout = new QVBoxLayout;
    nVBoxLayout->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);
    for(int iList = 0; iList < pHostInformList.count(); iList ++)
    {
        OBNRealTimeWaveformDispGroup* nWaveformDisp = new OBNRealTimeWaveformDispGroup();
        nWaveformDisp->setFixedHeight(800);
        nWaveformDisp->setCurrentDeviceID(pHostInformList[iList].ip, pHostInformList[iList].port);
        nVBoxLayout->addWidget(nWaveformDisp);

        m_waveDispGroup.append(nWaveformDisp);
    }
    /// ======
    QWidget* widget = new QWidget(this);
    widget->setLayout(nVBoxLayout);
    /// ======
    mScrollArea->setWidget(widget);
    /// ======
    QVBoxLayout* mainHBoxLayout = new QVBoxLayout;
    mainHBoxLayout->addWidget(mScrollArea);

    ui->widgetRealTimeExhibition->setLayout(mainHBoxLayout);
}
