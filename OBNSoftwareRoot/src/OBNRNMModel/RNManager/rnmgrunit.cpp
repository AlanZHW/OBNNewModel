#include "rnmgrunit.h"
#include "rnmanager.h"

#include <QStyledItemDelegate>
#include <QDesktopWidget>


//状态刷新时间
#define  Update_Interval_3    "3s"
#define  Update_Interval_5    "5s"
#define  Update_Interval_10   "10s"
#define  Update_Interval_20   "20s"
#define  Update_Interval_30   "30s"


#include <QLineEdit>
#include <QCheckBox>
#include <QProgressBar>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QHostInfo>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>
#include <QSpinBox>

#include "searchthread.h"
#include "publicwidgets.h"

RNMMenuManager::RNMMenuManager(QObject *parent)
    :QObject(parent)
{

}

void RNMMenuManager::createMenu(QMenuBar *menuBar, RNManager *rmnodemanager)
{
    menuFile = new QMenu(tr("文件"));
    menuFile->addAction(tr("设置搜索IP范围"),rmnodemanager,SLOT(slotSetSearchIpScope()));  ///< "&Set Search IP Scope..."
    menuFile->addSeparator();
    menuFile->addAction(tr("退出"),rmnodemanager,SLOT(slotQuit()),QKeySequence(tr("Ctrl+Q")));
    menuBar->addMenu(menuFile);

    //edit----
    menuEdit = new QMenu(tr("选项"));
    menuEdit->addAction(tr("限制选项"),rmnodemanager,SLOT(slotLimits()));    ///<
    menuEdit->addSeparator();

    QMenu *update_starus_interval = new QMenu(tr("更新状态间隔"));    ///<Update Status Interval
    menuEdit->addMenu(update_starus_interval);

    //update_starus_interval-------------------------------
    QVBoxLayout *btnLayout = new QVBoxLayout();
    QButtonGroup *m_btnGroup = new QButtonGroup(this);

    QRadioButton *timeBtn1 = new QRadioButton(Update_Interval_3);
    QRadioButton *timeBtn2 = new QRadioButton(Update_Interval_5);
    QRadioButton *timeBtn3 = new QRadioButton(Update_Interval_10);
    QRadioButton *timeBtn4 = new QRadioButton(Update_Interval_20);
    QRadioButton *timeBtn5 = new QRadioButton(Update_Interval_30);

    //垂直布局
    btnLayout->addWidget(timeBtn1);
    btnLayout->addWidget(timeBtn2);
    btnLayout->addWidget(timeBtn3);
    btnLayout->addWidget(timeBtn4);
    btnLayout->addWidget(timeBtn5);
    //按钮添加至按钮组
    m_btnGroup->addButton(timeBtn1);
    m_btnGroup->addButton(timeBtn2);
    m_btnGroup->addButton(timeBtn3);
    m_btnGroup->addButton(timeBtn4);
    m_btnGroup->addButton(timeBtn5);
    timeBtn1->setChecked(true);
    update_starus_interval->setLayout(btnLayout);
    m_btnGroup->setExclusive(true);
    connect(m_btnGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slotUpdateIntervalChanged(QAbstractButton*)));
    connect(this,SIGNAL(signalUpdateIntervalChanged(int)),rmnodemanager,SLOT(slotSetUpdateInterval(int)));
    //start/stop update------
    start_stop_update_act = new QAction(tr("&开始/停止更新"), menuEdit);
    start_stop_update_act->setCheckable(true);
    connect(start_stop_update_act,SIGNAL(triggered(bool)),rmnodemanager,SLOT(slotStartStopUpdate(bool)));
    menuEdit->addAction(start_stop_update_act);
    menuEdit->addSeparator();

    //采样率设置，下载管理
    menuEdit->addAction(tr("&Ftp节点管理"),rmnodemanager,SLOT(slotNodeFtpManager()));
    menuBar->addMenu(menuEdit);

    //view-------------------------
    menuView = new QMenu(tr("视图"));
    QAction *allConnectAct = new QAction(tr("显示全部/显示已链接"), menuView); ///< Show All/Connected
    allConnectAct->setCheckable(true);
    allConnectAct->setChecked(false);
    connect(allConnectAct,SIGNAL(triggered(bool)),rmnodemanager,SLOT(slotShowAllOrConnected(bool)));
    menuView->addAction(allConnectAct);
    menuView->addAction(tr("&显示状态报告"),rmnodemanager,SLOT(slotShowStatusReport()));   ///< Show Status Report
    menuView->addSeparator();


    QMenu  *displayFilterMenu = new QMenu(tr("&显示筛选器"),menuView); /// Display Filters
    menuView->addMenu(displayFilterMenu);
    QVBoxLayout *vFiltersLayout = new QVBoxLayout;

    //Filters
    filtersGroupBox = new QButtonGroup(this);

    QRadioButton *nodeStatusBtn = new QRadioButton(tr("节点状态"));         ///< Node Status
    nodeStatusBtn->setChecked(true);
    QRadioButton *voltageBtn = new QRadioButton(tr("电压"));            ///< Voltage
    QRadioButton *temperatureBtn = new QRadioButton(tr("温度"));        ///< Temperature
    QRadioButton *pressureBtn = new QRadioButton(tr("压力"));           ///< Pressure
    QRadioButton *storageBtn = new QRadioButton(tr("内存容量"));            ///< Memory Capacity
    QRadioButton *selfTestBtn = new QRadioButton(tr("自检"));           ///< Self Test
    QRadioButton *downLoadBtn = new QRadioButton(tr("下载"));           ///< Downloaded
    QRadioButton *tameButton  = new QRadioButton(tr("原子钟驯服"));

    vFiltersLayout->addWidget(nodeStatusBtn);
    filtersGroupBox->addButton(nodeStatusBtn,Status);
    vFiltersLayout->addWidget(voltageBtn);
    filtersGroupBox->addButton(voltageBtn,Voltage);
    vFiltersLayout->addWidget(temperatureBtn);
    filtersGroupBox->addButton(temperatureBtn,Temperature);
    vFiltersLayout->addWidget(pressureBtn);
    filtersGroupBox->addButton(pressureBtn,Pressure);
    vFiltersLayout->addWidget(storageBtn);
    filtersGroupBox->addButton(storageBtn,Memory_Capacity);
    vFiltersLayout->addWidget(selfTestBtn);
    filtersGroupBox->addButton(selfTestBtn,SelfTest);
    vFiltersLayout->addWidget(downLoadBtn);
    filtersGroupBox->addButton(downLoadBtn,DownLoad);
    vFiltersLayout->addWidget(tameButton);
    filtersGroupBox->addButton(tameButton, Tame);

    filtersGroupBox->setExclusive(true);

    connect(filtersGroupBox,SIGNAL(buttonClicked(int)),rmnodemanager,SLOT(slotDisplayFilters(int)));

    //设置间隔
    displayFilterMenu->setLayout(vFiltersLayout);

    //Print Warning Information

    QAction *printWarnInfoAct = new QAction(tr("打印/忽略警告消息"), menuView);   //< Print/Ignore Warning Message
    printWarnInfoAct->setCheckable(true);
    printWarnInfoAct->setChecked(true);
    connect(printWarnInfoAct,SIGNAL(toggled(bool)),rmnodemanager,SLOT(slotPrintWarningEnable(bool)));
    menuView->addAction(printWarnInfoAct);
    menuBar->addMenu(menuView);

    //Help---
    menuAbout = new QMenu(tr("帮助"));
    menuAbout->addAction(tr("&关于"),rmnodemanager,SLOT(slotAbout()));
    menuBar->addMenu(menuAbout);

    setDisplayedNode(false);
}


void RNMMenuManager::setUpdateStatus(const bool &start)
{
    if(start_stop_update_act->isChecked() != start)
        start_stop_update_act->setChecked(start);
}

void RNMMenuManager::setDisplayedNode(const bool &displayed)
{
    //Edit
    QList<QAction *> edit_actionList = menuEdit->actions();
    edit_actionList[3]->setEnabled(displayed);//update status
    edit_actionList[5]->setEnabled(displayed);

    //View
    QList<QAction *> view_actionList = menuView->actions();
    view_actionList[0]->setEnabled(displayed);//显示全部或者已经链接节点项
    view_actionList[1]->setEnabled(displayed);//全部状态报告
}

void RNMMenuManager::setDisplayFilters(const int &status)
{
    filtersGroupBox->button(status)->setChecked(true);
}

/// ====== 设置查询状态信息时间
void RNMMenuManager::slotUpdateIntervalChanged(QAbstractButton *btn)
{
    QString text = btn->text();
    int interval = 1000;
    if(text == Update_Interval_3)
    {
        interval*=3;
    }
    else if(text == Update_Interval_5)
    {
        interval*=5;
    }
    else if(text == Update_Interval_10)
    {
        interval*=10;
    }
    else if(text == Update_Interval_20)
    {
        interval*=20;
    }
    else if(text == Update_Interval_30)
    {
        interval*=30;
    }
    emit signalUpdateIntervalChanged(interval);
}


//--------------------------
RNMToolManager::RNMToolManager(QObject *parent)
    :QObject(parent), m_curentCalibration(false), m_curentOpenStorage(false)
{
    m_Path = QCoreApplication::applicationDirPath();
}

void RNMToolManager::createToolBar(QToolBar *toolBar,RNManager *rmnodemanager)
{
    //文件目录-------------
    m_toolBar = toolBar;
    /// ====== 设置搜索IP范围
    toolBar->addAction(QIcon(m_Path+"/Image/search.png"),tr("设置搜索IP范围"),rmnodemanager,SLOT(slotSetSearchIpScope()));    /// Set Search IP Scope
    toolBar->addSeparator();

    /// ====== 启动更新
    updateAction = new QAction(QIcon(m_Path+"/Image/stop.png"), tr("启动更新"), toolBar);
    updateAction->setData(true);
    connect(updateAction,SIGNAL(triggered(bool)),this,SLOT(slotStartOrStopUpdate()));
    connect(this,SIGNAL(signalStartOrStopUpdate(bool)),rmnodemanager,SLOT(slotStartStopUpdate(bool)));
    toolBar->addAction(updateAction);
    toolBar->addSeparator();

    /// ====== 下载&存储管理器
    toolBar->addAction(QIcon(m_Path+"/Image/data_manager.png"), tr("下载&存储管理器"),rmnodemanager, SLOT(slotNodeFtpManager()));  /// DownLoad & Storage Manager
    /// ====== 状态报告
    toolBar->addAction(QIcon(m_Path+"/Image/list_item.png"), tr("状态报告"),rmnodemanager, SLOT(slotShowStatusReport()));   ///< Status Report
    toolBar->addSeparator();

    /// ====== 原子钟驯服
    toolBar->addAction(QIcon(m_Path+"/Image/search.png"),   tr("获取D"),        rmnodemanager, SLOT(slotGetD()));
    m_lineEditGetD = new QLineEdit;
    m_lineEditGetD->setMaximumHeight(25);
    m_lineEditGetD->setMinimumWidth(100);
    m_lineEditGetD->setMaximumWidth(100);
    m_lineEditGetD->setReadOnly(true);
    toolBar->addWidget(m_lineEditGetD);

    toolBar->addAction(QIcon(m_Path+"/Image/settings.png"), tr("设置D"),        rmnodemanager, SLOT(slotSetD()));
    m_setupDComboBox = new QComboBox;
    m_setupDComboBox->setMinimumWidth(100);
    m_setupDComboBox->addItem("50");
    m_setupDComboBox->addItem("80");
    toolBar->addWidget(m_setupDComboBox);
    toolBar->addAction(QIcon(m_Path+"/Image/start.png"),    tr("开始原子钟驯服"), rmnodemanager, SLOT(slotAtomicClockTame()));
    toolBar->addSeparator();

    /// ====== 标定
    calibrationAction = new QAction(QIcon(m_Path+"/Image/start.png"), tr("标定"), toolBar);
    connect(calibrationAction, &QAction::triggered, this, [=](const bool){
        if(!m_curentCalibration)
        {
            m_curentCalibration = true;
            calibrationAction->setIcon(QIcon(m_Path+ICON_STOP));
            emit signalStartCalibration();
        }
        else
        {
            m_curentCalibration = false;
            calibrationAction->setIcon(QIcon(m_Path+ICON_START));
            emit signalEndCalibration();
        }
    });
    toolBar->addAction(calibrationAction);
    toolBar->addSeparator();

    /// ====== 开启/关闭 自动存储设备状态信息
    saveDeviceStatus = new QAction(QIcon(m_Path+"/Image/start.png"), tr("开启/关闭 自动存储设备状态信息"), toolBar);
    connect(saveDeviceStatus, &QAction::triggered, this, [=](const bool){
        if(!m_curentOpenStorage)
        {
            m_curentOpenStorage = true;
            saveDeviceStatus->setIcon(QIcon(m_Path+ICON_STOP));
            emit signalStorageDeviceInformation(true);
        }
        else
        {
            m_curentOpenStorage = false;
            saveDeviceStatus->setIcon(QIcon(m_Path+ICON_START));
            emit signalStorageDeviceInformation(false);
        }
    });
    toolBar->addAction(saveDeviceStatus);
    toolBar->addSeparator();

    /// ======
    QLabel *devNoLbl = new QLabel("Serial.No:");
    m_searchEdit = new QLineEdit("G");
    m_searchEdit->setInputMask("G000; ");
    m_searchEdit->setCursorPosition(1);
    m_searchEdit->setMaximumWidth(80);
    toolBar->addWidget(devNoLbl);
    toolBar->addWidget(m_searchEdit);

    connect(m_searchEdit,SIGNAL(returnPressed()),this,SLOT(slotSearchNode()));

    setDisplayedNode(false);
}

void RNMToolManager::setUpdateStatus(const bool &start)
{
    if(updateAction->data().toBool()!=start)
    {
        if(!start)
        {
            updateAction->setIcon(QIcon(m_Path+"/Image/start.png"));
            updateAction->setToolTip("Start Update");
            updateAction->setData(false);
        }else
        {
            updateAction->setIcon(QIcon(m_Path+"/Image/stop.png"));
            updateAction->setToolTip("Stop Update");
            updateAction->setData(true);
        }
    }
}

void RNMToolManager::setDisplayedNode(const bool &displayed)
{
    QList<QAction *> actionList = m_toolBar->actions();
    actionList[2]->setEnabled(displayed);
    actionList[3]->setEnabled(displayed);
    actionList[4]->setEnabled(displayed);
}

void RNMToolManager::slotSetUpdateInterval(const QString &text)
{
    int interval = 1000;
    if(text == Update_Interval_3)
        interval *= 3;
    else if(text == Update_Interval_5)
        interval *= 5;
    else if(text == Update_Interval_10)
        interval *= 10;
    else if(text == Update_Interval_20)
        interval *= 20;
    else if(text == Update_Interval_30)
        interval *= 30;

    emit signalUpdateIntervalChanged(interval);
}

void RNMToolManager::slotSearchNode()
{
    uint dev_no = m_searchEdit->text().mid(1).toUInt();
    emit signalSearchNode(dev_no);
}

void RNMToolManager::slotStartOrStopUpdate()
{
    QAction *action = static_cast<QAction *>(sender());
    bool start = action->data().toBool();
    if(!start)
    {
        action->setIcon(QIcon(m_Path+ICON_STOP));
        action->setData(true);
        emit signalStartOrStopUpdate(true);
    }else
    {
        action->setIcon(QIcon(m_Path+ICON_START));
        action->setData(false);
        emit signalStartOrStopUpdate(false);
    }
}

//SearchIpDialog--------------------------------
SearchIpDialog::SearchIpDialog(QWidget *parent)
    :QDialog(parent)
{
    this->setWindowTitle(tr("搜索节点"));
    this->setWindowFlags(this->windowFlags() | Qt::WindowMinMaxButtonsHint);

    initDlg();
    this->resize(SearchIP_Dialog_Width,SearchIP_Dialog_height);

    QRect screenRt = QApplication::desktop()->screenGeometry();
    this->move((screenRt.width() - width())/2,(screenRt.height() - height())/2);
}

SearchIpDialog::~SearchIpDialog()
{
    if(m_Nodes.size()>0){
        qDeleteAll(m_Nodes);
        m_Nodes.clear();
    }
}

void SearchIpDialog::closeEvent(QCloseEvent *e)
{
    //如果有扫描线程运行则阻止关闭
    if(m_threads.size()>0)
    {
        e->ignore();
        QMessageBox::warning(this,tr("警告"), tr("搜索正忙，请先停止."));    ///< Searching is busy,please stop first
    }
    else
    {
        QDialog::closeEvent(e);
    }
}


void SearchIpDialog::initDlg()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //loca host ip--------------
    QHBoxLayout *localHostLayout = new QHBoxLayout;
    QLabel *localHostIp = new QLabel(tr("本地主机IP:"));  ///< Local Host IP
    m_localHostIp = new QLabel(tr("127.0.0.1"));
    m_localHostIp->setAlignment(Qt::AlignCenter);
    QPushButton *checkLcHostIPBtn = new QPushButton(tr("检查"));
    checkLcHostIP();//初始化IP

    localHostLayout->addWidget(localHostIp);
    localHostLayout->addWidget(m_localHostIp );
    localHostLayout->addWidget(checkLcHostIPBtn,0,Qt::AlignTop);
    localHostLayout->addStretch(1);
    localHostLayout->setSpacing(24);
    mainLayout->addLayout(localHostLayout);

    GLine *line = new  GLine(this);
    line->setMaximumWidth(360);
    mainLayout->addWidget(line);

    //IP Address From -To----------------
    QHBoxLayout *searchFromLayout = new QHBoxLayout;
    QLabel *searchIpFromLbl = new QLabel(tr(":"));  ///< Search IP Scope
    m_ipFromEdit  = new IpAddrEdit(this);
    QLabel *toLbl = new QLabel("—");
    m_ipToEdit    = new IpAddrEdit(this);
    m_ipFromEdit->setMaximumWidth(180);
    m_ipToEdit->setMaximumWidth(180);
    m_ipFromEdit->setText("192.168.137.101");
    m_ipToEdit->setText("192.168.137.105");

    //
    QLabel   *wtimeLbl = new QLabel("| 最大等待时间(毫秒):"); ///< Max Wait Time(Msec)
    m_wtimeSpx = new QSpinBox(this);
    m_wtimeSpx->setRange(1,3000);
    m_wtimeSpx->setValue(2);

    //searchFromLayout->addStretch(1);
    searchFromLayout->addWidget(searchIpFromLbl);
    searchFromLayout->addWidget(m_ipFromEdit);
    searchFromLayout->addWidget(toLbl);
    searchFromLayout->addWidget(m_ipToEdit);
    searchFromLayout->addWidget(wtimeLbl);
    searchFromLayout->addWidget(m_wtimeSpx);
    searchFromLayout->addStretch(1);
    searchFromLayout->setSpacing(16);
    mainLayout->addLayout(searchFromLayout);

    //wait time

    //hLine-----
    mainLayout->addWidget(new GLine(this));

    //info----
    QHBoxLayout *infoLayout = new QHBoxLayout;
    QLabel *totalNdLbl = new QLabel(tr("节点总数:"));   ///< Total Nodes
    m_totalNodesLbl = new QLabel("0");
    m_totalNodesLbl->setMinimumWidth(60);
    QLabel *searchedNdLbl = new QLabel(tr("可用节点数:"));    ///<Connected Nodes
    m_SearchedNodesLbl = new QLabel("0");
    m_totalNodesLbl->setMinimumWidth(60);
    infoLayout->addWidget(totalNdLbl);
    infoLayout->addWidget(m_totalNodesLbl);
    infoLayout->addWidget(searchedNdLbl);
    infoLayout->addWidget(m_SearchedNodesLbl);
    infoLayout->addStretch(1);
    mainLayout->addLayout(infoLayout);

    //进度条-----------------------------
    QFrame      *progressFr = new QFrame(this);
    progressFr->setFrameShape(QFrame::Box);
    QVBoxLayout *progressVlayout = new QVBoxLayout;
    m_progressBar = new QProgressBar;
    progressVlayout->addWidget(m_progressBar);
    progressVlayout->setContentsMargins(2,2,2,2);

    progressFr->setLayout(progressVlayout);

    mainLayout->addWidget(progressFr);

    //搜索返回主机列表--------------------------
    m_hostsTab = new QTableWidget(this);
    m_hostsTab->setColumnCount(3);
    m_hostsTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList headerlbls;
    //headerlbls << "IP" << "Device.No" << "State(Connected)";
    headerlbls << "IP" << tr("设备编号") << tr("连接状态");
    m_hostsTab->setHorizontalHeaderLabels(headerlbls);
    m_hostsTab->setColumnWidth(0,240);
    m_hostsTab->horizontalHeader()->setStretchLastSection(true);
    m_hostsTab->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainLayout->addWidget(m_hostsTab);

    this->setLayout(mainLayout);

    //hLine-----
    mainLayout->addWidget(new GLine(this));

    //buttons---
    QHBoxLayout *btnLayout = new QHBoxLayout;
    m_searchBtn  = new QPushButton(tr(SearchIP_Button_Search));
    m_displayBtn = new QPushButton(tr("初始化")); /// "Init View(Close)");
    m_closeBtn   = new QPushButton(tr("关闭"));
    btnLayout->addStretch(1);
    btnLayout->addWidget(m_searchBtn);
    btnLayout->addStretch(1);
    btnLayout->addWidget(m_displayBtn);
    btnLayout->addStretch(1);
    btnLayout->addWidget(m_closeBtn);
    btnLayout->addStretch(1);
    mainLayout->addLayout(btnLayout);

    //signals-slots----------------------
    connect(checkLcHostIPBtn,SIGNAL(clicked(bool)),this,SLOT(checkLcHostIP()));
    connect(m_searchBtn, SIGNAL(clicked(bool)),this,SLOT(slotSearchBtnClicked()));
    connect(m_displayBtn,SIGNAL(clicked(bool)),this,SLOT(slotDisplayNodes()));
    connect(m_closeBtn,  SIGNAL(clicked(bool)),this,SLOT(close()));
}

void SearchIpDialog::checkLcHostIP()
{
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> address = info.addresses();
    if(address.size()<1)
    {
        return;
    }
    foreach (QHostAddress addr, address)
    {
        if(addr.protocol() == QAbstractSocket::IPv4Protocol)
        {
            m_localHostIp->setText(addr.toString());
        }
    }
}

//#define DEBUG
void SearchIpDialog::slotSearchBtnClicked()
{
#ifdef DEBUG
    FILE *fptx = fopen("./slotSearchBtnClicked", "wb");
#endif

    if(m_searchBtn->text() == SearchIP_Button_Stop)
    {
        //停止搜索
        stopSearch();
        return;
    }
    //检查输入IP范围是否合理
    QString fromIP = m_ipFromEdit->text();
    if(fromIP.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"), tr("起始IP错误,请检查"), tr("确定"));   /// "Start IP is wrong."
        return;
    }
    QString toIP =   m_ipToEdit->text();
    if(toIP.isEmpty())
    {
        QMessageBox::warning(this,tr("警告"), tr("终了IP错误,请检查"), tr("确定")); /// Last IP is wrong.
        return;
    }
#ifdef DEBUG
    fprintf(fptx, "fromIP is:%s\n, toIP is:%s\n",
            fromIP.toStdString().c_str(), toIP.toStdString().c_str());
    fflush(fptx);
#endif

    QStringList nfromIPList = fromIP.split(".");
    QString firstIP;
    for(int iList = 0; iList < nfromIPList.count()-1; iList ++)
    {
        firstIP = firstIP + nfromIPList[iList] + ".";
    }
    firstIP = firstIP + "0";

    QHostAddress addr1(fromIP);
    QHostAddress addr2(toIP);
    QHostAddress addrFirst(firstIP);

    //满足 起始< 结束-----
    if(addr1.toIPv4Address()>addr2.toIPv4Address())
    {
        QMessageBox::warning(this,tr("警告"), tr("IP范围错误,请检查"), tr("确定")); ///< IP Scope is wrong.
        return;
    }

    //初始化
    m_progressBar->setValue(0);
    m_searchBtn->setText(SearchIP_Button_Stop);
    m_displayBtn->setEnabled(false);
    m_closeBtn->setEnabled(false);
    m_searchedNodes = 0;

    //表格初始化
    m_hostsTab->clear();
    m_hostsTab->setHorizontalHeaderLabels(QStringList() << "IP" << tr("设备编号") << tr("连接状态"));   ///< State(Connected)

    m_startIP = addr1.toIPv4Address();
    m_lastIP  = addr2.toIPv4Address();
    m_firstIP = addrFirst.toIPv4Address();
#ifdef DEBUG
    fprintf(fptx, "m_startIP:%d\n", m_startIP);
    fprintf(fptx, "m_lastIP: %d\n", m_lastIP);
    fflush(fptx);
#endif

    m_totalIp = findNodesFromScope(m_startIP, m_lastIP);

    int addrNum = m_totalIp.size();
#ifdef DEBUG
    fprintf(fptx, "addrNum:%d\n", addrNum);
    fflush(fptx);
#endif
    m_hostsTab->setRowCount(addrNum);

    for(int i=0;i<addrNum;i++)
    {
        m_hostsTab->setItem(i,0,new QTableWidgetItem(QHostAddress(m_totalIp[i]).toString()));
        m_hostsTab->setItem(i,1,new QTableWidgetItem(QString("G%1").arg(ip2DeviceNo(m_totalIp[i], m_firstIP),3,10,QChar('0'))));
    }

    m_totalNodesLbl->setText(QString::number(addrNum));
    m_SearchedNodesLbl->setText("0");
    m_progressBar->setRange(0,addrNum);
    searchIpScope(m_totalIp);

#ifdef DEBUG
    fclose(fptx);
#endif
}

void SearchIpDialog::slotDisplayNodes()
{
    qDeleteAll(m_Nodes);
    m_Nodes.clear();

    //读取节点下载记录文件，初始化下载状态
    QStringList downloadedGOBS = Project::finishedDownloadGOBS(m_projectInfo);
    //初始化显示节点列表
    int node_size = m_hostsTab->rowCount();
    bool status;
    int count = 0;
    uint devNo = 0;
    for(int i=0;i<node_size;i++)
    {
        QTableWidgetItem *item = m_hostsTab->item(i,2);
        status = item->data(Node_Role_State).toBool();

        if(!status)
        {
            continue;
        }

        //创建节点信息结构体
        Node *node = new Node(this);
        if(downloadedGOBS.contains(m_hostsTab->item(i,1)->text()))
        {
            node->setDownloaded(true);
        }
        node->setIP(item->data(Node_Role_IP).toUInt());
        node->setState(status);

        devNo = m_hostsTab->item(i,1)->text().mid(1).toUInt();
        node->setDevNo(devNo);
        m_Nodes.append(node);

        count ++;
    }
    this->close();

    emit displayNodes(m_Nodes);
}

void SearchIpDialog::searchIpScope(QVector<uint> &hosts)
{
    int thread_num = QThread::idealThreadCount();
    thread_num = thread_num>hosts.size()?hosts.size():thread_num;

    int wtime = m_wtimeSpx->value();
    uint threadnum = uint(thread_num);

    for(quint32 i =0 ;i<threadnum;i++)
    {
        SearchThread *thread = new SearchThread(this);

        thread->setTotalHosts(m_totalIp);
        TaskCount taskCount;
        taskCount.start = i;
        taskCount.end   = m_totalIp.size()-1;

        taskCount.step = thread_num;

        thread->setTaskCount(taskCount);
        thread->setId(i);
        thread->setWaitTime(wtime);
        connect(thread,SIGNAL(searchedHost(quint32,bool)),this,SLOT(slotSearchedHost(quint32,bool)));
        connect(thread,SIGNAL(searchFinished(int)),this,SLOT(slotThreadFinished(int)));
        connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
        m_threads.insert(i,thread);
        thread->start();
    }
}

void SearchIpDialog::stopSearch()
{
    qApp->setOverrideCursor(Qt::WaitCursor);

    foreach(SearchThread *thread,m_threads.values())
    {
        thread->stop();
    }
    while(m_threads.size()>0)
    {
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    //搜索结束---------
    m_searchBtn->setText(SearchIP_Button_Search);
    qApp->restoreOverrideCursor();

    m_displayBtn->setEnabled(true);
    m_closeBtn->setEnabled(true);
}

QVector<uint> SearchIpDialog::findNodesFromScope(const quint32 &start,const quint32 &last)
{
    QVector<uint> rst;
    rst.resize(last-start +1);

    int num = 0;
    for(uint i=start;i<=last;i++)
    {
        if(isNodeIP(i, m_firstIP))
        {
            rst[num] = i;
            num++;
        }
    }
    rst.resize(num);
    return rst;
}

/// 获取当前搜索的节点
//#define DEBUG_SLOT_SEARCHED_HOST
void SearchIpDialog::slotSearchedHost(const quint32 &index,const bool &available)
{
#ifdef DEBUG_SLOT_SEARCHED_HOST
    FILE* fpIdx = fopen("./slotSearchedHost", "ab+");
    fprintf(fpIdx, "index is:%d, available:%d\n", index, available?1:0);
    fclose(fpIdx);
#endif

    m_progressBar->setValue(m_progressBar->value()+1);
    //行号------
    if(available)
    {
        QTableWidgetItem *item = new QTableWidgetItem(Node_Connected);
        item->setData(Node_Role_IP,m_totalIp[index]);
        item->setData(Node_Role_State,true);
        m_hostsTab->setItem(index,2,item);
    }
    else
    {
        QTableWidgetItem *item = new QTableWidgetItem(Node_Not_Avaliable);
        item->setData(Node_Role_IP,m_totalIp[index]);
        item->setData(Node_Role_State,false);
        m_hostsTab->setItem(index,2,item);
        return;
    }
    m_searchedNodes ++;
    m_SearchedNodesLbl->setText(QString::number(m_searchedNodes));
}

/// 显示当前节点到view上
void SearchIpDialog::slotThreadFinished(const int &id)
{
    //    qDebug()<<"thread:"<<id<<" finished";
    delete m_threads.value(id);
    m_threads.remove(id);

    //搜索结束
    if(m_threads.size() == 0)
    {
        m_searchBtn->setText(SearchIP_Button_Search);
        m_displayBtn->setEnabled(true);
        m_closeBtn->setEnabled(true);
    }
}

//LimitWg---------------------------
LimitWg::LimitWg(const Limit &limit,QWidget *parent)
    :QWidget(parent),m_limit(limit),m_buddyWg(0)
{
    m_defultVal = m_limit.value;
    initWg();
}
void LimitWg::setLimit(const Limit &limit)
{
    m_limit = limit;
    m_defultVal = m_limit.value;
    m_colorFrame->setColor(m_limit.color);
    m_logicLbl->setText(logicText(m_limit.operation));
    m_valEdit->setText(QString::number(m_limit.value));
    m_suffixLbl->setText(m_limit.suffix);
}

void LimitWg::reset()
{
    m_valEdit->setText(QString::number(m_limit.value));
}

Limit LimitWg::limit(bool *ok )
{
    bool ret= false;
    if(ok)
        *ok = true;
    //判断格式
    m_valEdit->text().toFloat(&ret);
    if(!ret) {
        if(ok)
            *ok = ret;
        return m_limit;
    }

    //判断值的范围
    if(m_valEdit->validator())
    {
        const QDoubleValidator *validator = static_cast<const QDoubleValidator*>(m_valEdit->validator());
        if(validator)
        {
            QString text = m_valEdit->text();
            int pos = 0;
            if(validator->validate(text,pos) != QValidator::Acceptable)
            {
                ret = false;
                if(ok)
                    *ok = false;
                return m_limit;
            }
        }
    }

    Limit limit = m_limit;
    limit.value = m_valEdit->text().toFloat();

    return limit;
}

void LimitWg::initWg()
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    m_colorFrame = new ColorFrame(this);
    m_colorFrame->setColor(m_limit.color);
    m_logicLbl   = new QLabel(logicText(m_limit.operation));
    m_valEdit    = new QLineEdit(QString::number(m_limit.value));
    m_suffixLbl  = new QLabel(m_limit.suffix);

    mainLayout->addWidget(m_colorFrame);
    mainLayout->addWidget(m_logicLbl);
    mainLayout->addWidget(m_valEdit);
    mainLayout->addWidget(m_suffixLbl);

    this->setLayout(mainLayout);
}

LimitGroupBox::LimitGroupBox(QWidget* parent)
    :QGroupBox(parent)
{
    initLayout();
}

LimitGroupBox::LimitGroupBox(const QString &title, QWidget* parent)
    :QGroupBox(title,parent)
{
    initLayout();
}

void LimitGroupBox::addLimit(const Limit &limit)
{
    LimitWg *limitWg = new LimitWg(limit,this);
    limitWg->setId(m_childWidgets.size());

    m_childWidgets.append(limitWg);
    mainLayout->addWidget(limitWg);
}

QList<Limit> LimitGroupBox::limits(bool *ok)
{
    QList<Limit> lis;
    if(ok)
        *ok  = true;
    bool ret = false;
    foreach(LimitWg *widget, m_childWidgets)
    {
        lis.append(widget->limit(&ret));
        if(!ret)
        {
            if(ok)
            {
                *ok = ret;
            }
            m_errString = "limit value is out of range"+QString("(%1,%2)").arg(m_validator->bottom()).arg(m_validator->top());
        }
    }

    //    qDebug()<<lis.at(0).operation;
    //大小顺序是否正确
    if(lis.at(0).operation == Big)
    {
        if(lis.first().value>lis.last().value)
        {
            if(ok)
                *ok = false;
            //数值不对，重置
            lis.clear();
            foreach(LimitWg *widget, m_childWidgets)
            {
                widget->reset();
                lis.append(widget->defultLimit());
            }
            m_errString = "limit value is error,first is bigger than second value.";
        }
    }
    else
    {
        if(lis.first().value<lis.last().value){
            if(ok)
                *ok = false;
            //数值不对，重置
            lis.clear();
            foreach(LimitWg *widget, m_childWidgets) {
                widget->reset();
                lis.append(widget->defultLimit());
            }
            m_errString = "limit value is error,first is less than second value.";
        }
    }

    return lis;
}

LimitData LimitGroupBox::limitData(bool *ok)
{
    LimitData liData;
    if(ok)
        *ok = true;
    //先获取判断当前 Limit 设置
    bool ret = false;
    QList<Limit> lis = limits(&ret);
    if(!ret)
    {
        if(ok)
            *ok = ret;
    }

    //第一级
    liData.operate = lis.first().operation;
    liData.first = lis.first().value;
    //第二级
    liData.second = lis.last().value;

    return liData;
}

void LimitGroupBox::setValidator(QValidator *validator)
{
    foreach (LimitWg *limitWg, m_childWidgets) {
        limitWg->setValidator(validator);
    }
    m_validator = static_cast<QDoubleValidator*>(validator);
}

void LimitGroupBox::initLayout()
{
    mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(2,2,2,2);
    this->setLayout(mainLayout);
}



//参数状态显示限制编辑对话框-------------------
LimitsDialog::LimitsDialog(QWidget *parent)
    :QDialog(parent)
{
    this->setWindowTitle(tr("设置限制选项"));   /// Define Limits
    initDlg();
    this->resize(600,300);
}

LimitInfo LimitsDialog::getLimitInfo(const int &status)
{
    LimitInfo    limitInfo;
    QList<Limit> limits;
    //显示节点链接状态
    if(status == 0)
    {
        limitInfo.operate = Equal;

        Limit limit;
        limit.color = QColor(Qt::green);
        limit.suffix = "Connected";
        limits.append(limit);

        limit.color = QColor(Qt::gray);
        limit.suffix = "Not Avaliable";
        limits.append(limit);
    }
    else if(status == 5)//自检状态
    {
        limitInfo.operate = Equal;

        Limit limit;
        limit.color = QColor(Qt::green);
        limit.suffix = "Normal";
        limits.append(limit);

        limit.color = QColor(Qt::red);
        limit.suffix = "Warning";
        limits.append(limit);
    }
    else if(status == 6)//下载
    {
        limitInfo.operate = Equal;

        Limit limit;
        limit.color = QColor(Qt::green);//未下载
        limit.suffix = "UnDownload";
        limits.append(limit);

        limit.color = QColor(Qt::blue);//已经下载完成
        limit.suffix = "Downloaded";
        limits.append(limit);
    }
    else if(7 == status)
    {
        limitInfo.operate = Equal;

        Limit limit;
        limit.color = QColor(Qt::green);
        limit.suffix = tr("成功");
        limits.append(limit);

        limit.color = QColor(Qt::yellow);
        limit.suffix = tr("正在驯服");
        limits.append(limit);

        limit.color = QColor(Qt::gray);
        limit.suffix = tr("未驯服");
        limits.append(limit);

        limit.color = QColor(Qt::red);
        limit.suffix = tr("失败");
        limits.append(limit);
    }
    else
    {
        bool ok = false;
        limits = m_groupBoxs.at(status-1)->limits(&ok);
        if(!ok)
        {
            QMessageBox::warning(NULL,tr("警告"),m_groupBoxs.at(status-1)->title()+ " limit value is wrong,error:"+m_groupBoxs.at(status-1)->errString());
        }
        limitInfo.operate = limits.at(0).operation;
    }
    limitInfo.limits = limits;
    return limitInfo;
}


//3*3 布局显示
void LimitsDialog::initDlg()
{
    QVBoxLayout *vlayout = new QVBoxLayout;
    QGridLayout  *mainLayout = new QGridLayout;
    Limit limit;
    m_limitData.resize(5);

    //Voltage
    LimitGroupBox *valtageBox = new LimitGroupBox(tr("电压"),this);
    limit.color     = QColor(Qt::yellow);
    limit.operation = Less;
    limit.value     = 3.7;
    limit.suffix    = "V";
    valtageBox->addLimit(limit);
    limit.color     = QColor(Qt::red);
    limit.operation = Less;
    limit.value     = 3.5;
    limit.suffix    = "V";
    valtageBox->addLimit(limit);
    m_groupBoxs.append(valtageBox);
    mainLayout->addWidget(valtageBox,0,0);
    m_limitData[0].operate = Less;
    m_limitData[0].first   = 3.7;
    m_limitData[0].second  = 3.5;
    QDoubleValidator  *validator = new QDoubleValidator(valtageBox);
    //0～5V
    validator->setRange(0,5,6);
    valtageBox->setValidator(validator);

    //Temperature
    LimitGroupBox *temperBox = new LimitGroupBox(tr("温度"),this);
    limit.color     = QColor(Qt::yellow);
    limit.operation = Big;
    limit.value     = 30;
    limit.suffix    = QStringLiteral("℃");
    temperBox->addLimit(limit);
    limit.color     = QColor(Qt::red);
    limit.operation = Big;
    limit.value     = 50;
    limit.suffix    = QStringLiteral("℃");
    temperBox->addLimit(limit);
    m_groupBoxs.append(temperBox);
    mainLayout->addWidget(temperBox,0,1);
    m_limitData[1].operate= Big;
    m_limitData[1].first  = 30;
    m_limitData[1].second = 50;
    validator = new QDoubleValidator(temperBox);
    //0～50 ℃
    validator->setRange(0,50,6);
    temperBox->setValidator(validator);

    //Pressure
    LimitGroupBox *PressureBox = new LimitGroupBox(tr("舱压"),this);  ///< Pressure
    limit.color     = QColor(Qt::yellow);
    limit.operation = Big;
    limit.value     = 0.90;
    limit.suffix    = "atm";
    PressureBox->addLimit(limit);
    limit.color     = QColor(Qt::red);
    limit.operation = Big;
    limit.value     = 1.0;
    limit.suffix    = "atm";
    PressureBox->addLimit(limit);
    m_groupBoxs.append(PressureBox);
    mainLayout->addWidget(PressureBox,0,2);
    m_limitData[2].operate=Big;
    m_limitData[2].first  = 0.90;
    m_limitData[2].second = 1.0;
    validator = new QDoubleValidator(PressureBox);
    //0～1.0
    validator->setRange(0,1.0,6);
    PressureBox->setValidator(validator);

    //Memory Capacity
    LimitGroupBox *memoryBox = new LimitGroupBox(("内存容量"),this);    ///< Memory Capacity
    limit.color     = QColor(Qt::yellow);
    limit.operation = Less;
    limit.value     = 5;
    limit.suffix    = "GB";
    memoryBox->addLimit(limit);
    limit.color     = QColor(Qt::red);
    limit.operation = Less;
    limit.value     = 1;
    limit.suffix    = "GB";
    memoryBox->addLimit(limit);
    m_groupBoxs.append(memoryBox);
    m_limitData[3].operate=Less;
    m_limitData[3].first  = 5;
    m_limitData[3].second = 1;
    validator = new QDoubleValidator(memoryBox);
    //0～32.0 G
    validator->setRange(0.0,32.0,6);
    memoryBox->setValidator(validator);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(memoryBox, 1, 0);

    //标定
    LimitGroupBox *calibrationBox = new LimitGroupBox(tr("标定过零点设置"),this);
    limit.color     = QColor(Qt::yellow);
    limit.operation = Big;
    limit.value     = 5;
    limit.suffix    = QStringLiteral("");
    calibrationBox->addLimit(limit);
    limit.color     = QColor(Qt::red);
    limit.operation = Big;
    limit.value     = 10;
    limit.suffix    = QStringLiteral("");
    calibrationBox->addLimit(limit);
    m_groupBoxs.append(calibrationBox);
    mainLayout->addWidget(calibrationBox,1,1);
    m_limitData[4].operate= Big;
    m_limitData[4].first  = 5;
    m_limitData[4].second = 10;
    validator = new QDoubleValidator(calibrationBox);
    validator->setRange(0, 50, 6);
    calibrationBox->setValidator(validator);

    vlayout->addLayout(mainLayout);
    vlayout->addWidget(new GLine(this));

    /// ======
    QHBoxLayout   *btnLayout  = new QHBoxLayout;
    QPushButton   *cancelBtn = new QPushButton(tr("&取消"));
    QPushButton   *okBtn     = new QPushButton(tr("&确定"));
    btnLayout->addStretch(1);
    okBtn->setDefault(true);
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(okBtn);

    vlayout->addLayout(btnLayout);
    this->setLayout(vlayout);

    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelBtnClicked()));
    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(okBtnClicked()));
}

void LimitsDialog::cancelBtnClicked()
{
    this->close();
}

void LimitsDialog::okBtnClicked()
{
    bool ok = false;
    //更新阀值数组
    for(int i = 0;i<m_groupBoxs.size();i++)
    {
        m_limitData[i] = m_groupBoxs[i]->limitData(&ok);
        if(!ok){
            QMessageBox::warning(this,tr("警告"),m_groupBoxs[i]->title()+" limit data is wrong,error:"+m_groupBoxs[i]->errString());
            return;
        }
    }

    //发送更新
    emit limitsChanged(m_limitData);
    this->close();
}




