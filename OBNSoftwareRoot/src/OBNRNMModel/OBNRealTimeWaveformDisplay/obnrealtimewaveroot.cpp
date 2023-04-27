#include "obnrealtimewaveroot.h"
#include "ui_obnrealtimewaveroot.h"

OBNRealTimeWaveRoot::OBNRealTimeWaveRoot(QWidget *parent) :
    QMainWindow(parent),m_curentDispWaveform(false),m_obnSeatchHosts(NULL),
    ui(new Ui::OBNRealTimeWaveRoot)
{
    ui->setupUi(this);
    setWindowTitle(tr("实时波形显示"));
//    setWindowState(Qt::WindowMaximized);
    initWindow();

    ui->tableWidget->setMaximumWidth(248);
}

OBNRealTimeWaveRoot::~OBNRealTimeWaveRoot()
{
    /// ====== 关闭显示实时波形
    if(m_curentDispWaveform)
    {
        m_curentDispWaveform = false;
        for(int iList = 0; iList < m_waveDispGroup.count(); iList ++)
        {
            m_waveDispGroup[iList]->exitCollection();
        }
    }
    /// ====== 关闭采集
    if(m_curentCollecting)
    {
        m_curentCollecting = false;
        for(int iList = 0; iList < m_waveDispGroup.count(); iList ++)
        {
            m_waveDispGroup[iList]->stopDisplayWaveform();
        }
    }
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
                QList<TCPInform> n_tcpInformList;
                for(int iList = 0; iList < hostStateVecotr.count(); iList ++)
                {
                    TCPInform nTempTCPInform;
                    nTempTCPInform.ip       = hostStateVecotr[iList].ip;
                    nTempTCPInform.hostName = hostStateVecotr[iList].hostNum;
                    nTempTCPInform.port     = 5000;
                    n_tcpInformList.append(nTempTCPInform);
                }
                setCurrentAvailableHostInformList(n_tcpInformList);
            });
        }
        m_obnSeatchHosts->open();
    });
    ui->toolBar->addSeparator();

    m_actionStartCollection = new QAction(QIcon(m_Path+"/Image/start.png"), tr("开始/停止采集"));
    ui->toolBar->addAction(m_actionStartCollection);
    connect(m_actionStartCollection, &QAction::triggered, this, [=](const bool){
        /// ====== 描述当前是否已经点击了开始采集
        if(!m_curentCollecting)
        {
            m_curentCollecting = true;
            int currentIdx = ui->tabWidget->currentIndex();
            m_waveDispGroup[currentIdx]->startCollection();

            m_actionStartCollection->setIcon(QIcon(m_Path+"/Image/stop.png"));
            m_actionStartDispWaveform->setEnabled(true);
        }
        else
        {
            m_curentCollecting = false;
            int currentIdx = ui->tabWidget->currentIndex();
            m_waveDispGroup[currentIdx]->exitCollection();
            m_actionStartCollection->setIcon(QIcon(m_Path+"/Image/start.png"));
            m_actionStartDispWaveform->setEnabled(false);
        }
    });
    ui->toolBar->addSeparator();

    m_actionStartDispWaveform = new QAction(QIcon(m_Path+"/Image/start.png"), tr("开始/停止显示"));
    ui->toolBar->addAction(m_actionStartDispWaveform);
    m_actionStartDispWaveform->setEnabled(false);
    connect(m_actionStartDispWaveform, &QAction::triggered, this, [=](const bool){
        /// ====== 描述当前是否已经开始显示波形数据
        if(m_curentDispWaveform)
        {
            m_curentDispWaveform = false;
            int currentIdx = ui->tabWidget->currentIndex();
            m_waveDispGroup[currentIdx]->stopDisplayWaveform();
            m_actionStartDispWaveform->setIcon(QIcon(m_Path+"/Image/start.png"));
        }
        else
        {
            m_curentDispWaveform = true;
            int currentIdx = ui->tabWidget->currentIndex();
            m_waveDispGroup[currentIdx]->startDisplayWaveform();
            m_actionStartDispWaveform->setIcon(QIcon(m_Path+"/Image/stop.png"));
        }
    });
}

/// ====== 设置当前可用设备列表
void OBNRealTimeWaveRoot::setCurrentAvailableHostInformList(const QList<TCPInform> & pHostInformList)
{
    m_curentHostTCPInform = pHostInformList;

    /// ====== 设置界面左侧表格内容
    ui->tableWidget->setRowCount(m_curentHostTCPInform.count());
    ui->tableWidget->setColumnCount(3);
    QStringList nTableWidgetHeaders;
    nTableWidgetHeaders << tr("选中状态") << tr("节点编号") << tr("波形颜色");
    ui->tableWidget->setHorizontalHeaderLabels(nTableWidgetHeaders);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int iRow = 0; iRow < m_curentHostTCPInform.count(); iRow ++)
    {
        QCheckBox* nCheckBox = new QCheckBox;
        connect(nCheckBox, &QCheckBox::stateChanged, this, &OBNRealTimeWaveRoot::slotChangeCheckBoxState);
        ui->tableWidget->setCellWidget(iRow, 0, nCheckBox);

        ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(m_curentHostTCPInform[iRow].hostName));

        QColor lineColor = QColor::fromRgb(rand()%256,rand()%256,rand()%256);
        QLabel * nLabelColor = new QLabel;
        nLabelColor->setStyleSheet("QLabel{background-color:#" + QString::number(lineColor.rgba(), 16)+"}");
        ui->tableWidget->setCellWidget(iRow, 2, nLabelColor);
    }
}

/// ====== 改变当前表格节点选项选中状态
void OBNRealTimeWaveRoot::slotChangeCheckBoxState(const int& index)
{
    if(0 == index)
    {
        /// ====== 显示节点
        QString hostName;
        for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
        {
            if((QCheckBox*)ui->tableWidget->cellWidget(iRow, 0) == sender())
            {
                hostName = ui->tableWidget->item(iRow,1)->text();
                break;
            }
        }
        for(int iTab = 0; iTab < ui->tabWidget->count(); iTab ++)
        {
            if(hostName == ui->tabWidget->tabText(iTab))
            {
                ui->tabWidget->removeTab(iTab);
                m_waveDispGroup.removeAt(iTab);
            }
        }
    }
    else
    {
        /// ====== 显示节点
        for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
        {
            if((QCheckBox*)ui->tableWidget->cellWidget(iRow, 0) == sender())
            {
                OBNRealTimeWaveformDispGroup* nWaveformDisp = new OBNRealTimeWaveformDispGroup;
                nWaveformDisp->setCurrentDeviceID(m_curentHostTCPInform[iRow].ip, m_curentHostTCPInform[iRow].port);
                /// ====== 加载节点到图像显示区域
                ui->tabWidget->addTab(nWaveformDisp, m_curentHostTCPInform[iRow].hostName);
                m_waveDispGroup.append(nWaveformDisp);
            }
        }
    }
}












