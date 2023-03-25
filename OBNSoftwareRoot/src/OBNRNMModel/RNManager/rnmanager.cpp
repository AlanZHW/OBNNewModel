#include "rnmanager.h"
#include "ui_rnmanager.h"

#define  TextBrwser_Min_Height   50
#define  SideBar_Min_Width       80

#include <QBoxLayout>
#include <QFrame>
#include <QDesktopWidget>
#include <QLabel>
#include <QSplitter>
#include <QMessageBox>
#include <QDebug>

#include "assistant.h"

QTextBrowser    *txtBrwser = 0;
bool             warning_enable = true;
RNManager::RNManager(QWidget *parent):QMainWindow(parent)
    ,ui(new Ui::RNManager)
    ,m_updating(false)
{
    ui->setupUi(this);

    switch(AppGlobal::getInstance()->getCurrentLanguageMode())
    {
    case 0:
        m_translator.load("rnmanager_cn.qm", ".");
        break;
    case 1:
        m_translator.load("rnmanager_en.qm", ".");
        break;
    default:
        break;
    }
    QCoreApplication::installTranslator(&m_translator);
    ui->retranslateUi(this);

    this->setWindowTitle(tr("远程节点管理器"));   ///<RNM(Remote Node Manager)

    /// ====== 创建菜单栏
    m_menuManager = new RNMMenuManager(this);
    /// ====== 创建工具栏
    m_toolManager = new RNMToolManager(this);

    /// ====== 参数状态显示限制编辑对话框
    m_limitsDlg   = new LimitsDialog(this);
    /// ====== 初始limit值
    m_limitData   = m_limitsDlg->limitData();
    /// ======
    m_stCtrler = new StatusControler;

    m_searIPDlg    = 0;
    m_statusReport = 0;

    initWindow();

    m_txtBrowser->document()->setMaximumBlockCount(50);

    txtBrwser = m_txtBrowser;

    m_stCtrler->setFilters(0);
    m_stCtrler->setLimitData(m_limitData);

    m_statisticsData.updateInterval =  5;
    m_RNView->setStatisticsData(&m_statisticsData);

    m_sideBar->setStatisticsData(m_statisticsData);

    /// ======
    connect(m_sideBar, &RNMSideBar::reportNodeStatus,      this, &RNManager::slotShowStatusReport);
    connect(m_sideBar, &RNMSideBar::displayFiltersChanged, this, &RNManager::slotDisplayFilters);

    connect(m_limitsDlg, &LimitsDialog::limitsChanged,this, [=](const QVector<LimitData> & limitData){
        /// ======
        m_limitData = limitData;
        /// ====== 状态控制器
        m_stCtrler->setLimitData(limitData);
        /// ====== 状态报告
        if(m_statusReport)
        {
            m_statusReport->setLimitData(limitData);
        }
    });

    connect(m_toolManager, &RNMToolManager::signalSearchNode, this, [=](const uint & node){
        m_RNView->searchNode(node);
    });
    connect(m_toolManager, &RNMToolManager::signalStartCalibration, this, [=](){
        slotStartCalibrationFunction();
    });
    connect(m_toolManager, &RNMToolManager::signalEndCalibration, this, [=](){
        slotEndCalibrationFunction();
    });

    connect(m_RNView, &RNMGraphView::updateNodes, this, [=](){
        /// ====== 每次更新统计所有节点的状态报告信息
        int avalid_num = 0;
        for(int i = 0; i<m_Nodes.size();i++)
        {
            if(m_Nodes[i]->state())
            {
                avalid_num ++;
            }
        }
        m_statisticsData.avaliableNodes = avalid_num;
        m_sideBar->setStatisticsData(m_statisticsData);
    });

    QRect rect = QApplication::desktop()->screenGeometry();
    this->resize(rect.width()*2/3,rect.height()*3/4);
    this->move((rect.width()-width())/2,(rect.height()-height())/2);
    m_sideBar->resize(100,m_sideBar->height());
}

RNManager::~RNManager()
{
    delete ui;
    //先停止刷新
    if(m_RNView->isUpdating())
    {
        m_RNView-> startOrStopUpdateNode(false);
    }
    if(NULL != m_stCtrler)
    {
        delete m_stCtrler;
    }
}

void RNManager::slotShowStatusReport()
{
    m_statusReport->setCurrentNodeInfo(m_Nodes);
    m_statusReport->show();
}

void RNManager::slotDisplayFilters(const int &status)
{
    /// ====== 菜单
    m_menuManager->setDisplayFilters(status);
    /// ====== 侧边栏
    m_sideBar->setDisplayFilters(status);
    /// ====== 节点状态控制器
    m_stCtrler->setFilters(status);
}

/// ====== 原子钟相关
void RNManager::slotAtomicClockTame()
{
    m_RNView->startAtomicClockTameFunction();
}

/// ====== 设置D
void RNManager::slotSetD()
{
    m_RNView->setDFunction();
}

/// ====== 获取D
void RNManager::slotGetD()
{
    m_RNView->getDFunction();
}

/// ====== 标定
void RNManager::slotStartCalibrationFunction()
{
    m_RNView->calibrationFunction(true);
}

void RNManager::slotEndCalibrationFunction()
{
    m_RNView->calibrationFunction(false);
}

bool RNManager::init()
{
    m_nodeMediator = new NodeMediator(this);
    m_FtpManager   = new RNFtpManager(this);
    m_FtpManager->setProjectInfo(m_projInfo);
    /// ====== 设置中介
    m_FtpManager->setNodeMediator(m_nodeMediator);
    m_statusReport = new StatusReportDlg(this);
    m_statusReport ->setLimitData(m_limitData);
    m_statusReport->setCurrentNodeInfo(m_Nodes);
    m_FtpManager->setNodesInfo(m_Nodes);
    /// ====== 中介设置显示面板
    m_nodeMediator->setStatusReport(m_statusReport);
    m_nodeMediator->setRNFtpManager(m_FtpManager);
    return true;
}


void RNManager::initWindow()
{
    //创建菜单栏---
    m_menuManager->createMenu(ui->menuBar,this);

    //创建工具栏------------------
    m_toolManager->createToolBar(ui->mainToolBar,this);

    QSplitter    *mainSplitter = new QSplitter(Qt::Vertical,this);
    /// ====== 侧边栏
    QSplitter   *horiSplitter = new QSplitter(Qt::Horizontal,this);
    m_sideBar = new RNMSideBar(m_limitsDlg,this);
    m_sideBar->setMinimumWidth(SideBar_Min_Width);
    horiSplitter->addWidget(m_sideBar);

    /// ====== 图像显示区
    m_RNView = new  RNMGraphView(this);
    horiSplitter->addWidget(m_RNView);
    horiSplitter->setStretchFactor(1,1);

    mainSplitter->addWidget(horiSplitter);

    /// ====== 提示文本框
    m_txtBrowser = new QTextBrowser(this);
    m_txtBrowser->setMinimumHeight(TextBrwser_Min_Height);
    mainSplitter->addWidget(m_txtBrowser);

    mainSplitter->setStretchFactor(0,1);

    this->setCentralWidget(mainSplitter);
}

void RNManager::setProjectInform(const QString& _projectPath, const QString& _projectName)
{
    m_projInfo.ProjectPath = _projectPath;
    m_projInfo.ProjectName = _projectName;
qDebug() << "ProjectPath = " << m_projInfo.ProjectPath << "\t ProjectName = " << m_projInfo.ProjectName;
    this->init();
}

/// ====== 菜单file选项
void RNManager::slotSetSearchIpScope()
{
    if(NULL == m_searIPDlg)
    {
        m_searIPDlg = new SearchIpDialog(this);
        m_searIPDlg->setProjectInfo(m_projInfo);

        /// ====== 信号
        connect(m_searIPDlg, &SearchIpDialog::displayNodes, this, [=](const QVector<Node*> &_displayNodes){

            m_Nodes = _displayNodes;
            /// ====== 开始显示
            m_txtBrowser->append(QString(tr("总节点数:%1")).arg(_displayNodes.size())); ///< Total Node

            int avalid_num = 0;
            for(int i = 0; i < m_Nodes.size(); i ++)
            {
                /// ====== 每个节点设置中介
                m_Nodes[i]->setNodeMediator(m_nodeMediator);
                /// ====== 设置状态控制器
                m_Nodes[i]->setStateCtrler(m_stCtrler);
                if(m_Nodes[i]->state())
                {
                    avalid_num ++;
                }
            }
            m_statisticsData.totalNodes     = m_Nodes.size();
            m_statisticsData.avaliableNodes = avalid_num;
            /// ======
            m_nodeMediator->setNodes(m_Nodes);
            /// ======
            m_stCtrler->setNodes(m_Nodes);
            /// ======
            m_FtpManager->setNodesInfo(m_Nodes);

            /// ====== 布局显示，参数刷新---------------
            m_RNView->setNodes(_displayNodes);

            m_statisticsData.nodeBoxes = m_RNView->nodeBoxes();
            m_sideBar->setStatisticsData(m_statisticsData);
            //更新菜单工具栏选项状态
            if(_displayNodes.size() > 0)
            {
                m_menuManager->setDisplayedNode(true);
                m_toolManager->setDisplayedNode(true);
                m_sideBar->setDisplayedNode(true);
                //初始启动刷新
                slotStartStopUpdate(true);
            }
        });
    }

    //如果正在刷新状态,因为都是用TCP/IP ,需要先停止刷新
    if(m_RNView->isUpdating())
    {
        //提示停止刷新
        QMessageBox box(QMessageBox::Warning,"warning","need to stop Refreshing node first,do you want to continue?",QMessageBox::Yes|QMessageBox::Cancel,this);
        switch (box.exec())
        {
        case QMessageBox::Yes:
            //停止刷新
            slotStartStopUpdate(false);
            break;
        case QMessageBox::Cancel:
            return;
        default:
            break;
        }
    }
    m_searIPDlg->exec();
}


void RNManager::slotQuit()
{
    this->close();
}

//set选项
void RNManager::slotLimits()
{
    m_limitsDlg->exec();
}

void RNManager::slotSetUpdateInterval(const int &interval)
{
    m_RNView->setUpdateInterval(interval);
}

void RNManager::slotStartStopUpdate(const bool &start)
{
    m_toolManager->setUpdateStatus(start);
    m_menuManager->setUpdateStatus(start);
    /// ====== 显示图像区域启动或停止刷新显示
    m_RNView->startOrStopUpdateNode(start);
}

void RNManager::slotNodeFtpManager()
{
    m_FtpManager->show();
}

//view选项
void RNManager::slotShowAllOrConnected(const bool &show)
{
    m_RNView->setShowAllOrConnected(show);
}

//about选项
void RNManager::slotAbout()
{
    Assistant::showAssistant("RNM");
}

void RNManager::slotPrintWarningEnable(const bool &enable)
{
    warning_enable = enable;
}

void outputMessage(QtMsgType type,const QMessageLogContext &/*context*/,const QString &msg)
{
    if(!warning_enable)
    {
        return;
    }
    switch (type)
    {
    case QtWarningMsg://警告信息
        if(txtBrwser)
            txtBrwser->append("warning:"+msg);
        break;
    case QtCriticalMsg://严重警告信息
        if(txtBrwser)
            txtBrwser->append("error:"+msg);
        break;
    default:
        break;
    }
}
