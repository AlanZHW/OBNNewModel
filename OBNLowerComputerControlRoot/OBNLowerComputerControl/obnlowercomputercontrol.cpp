#include "obnlowercomputercontrol.h"
#include "ui_obnlowercomputercontrol.h"

OBNLowerComputerControl::OBNLowerComputerControl(QWidget *parent)
    : QMainWindow(parent), m_obnSeatchHosts(NULL),n_selAllCheckBox(NULL)
    , ui(new Ui::OBNLowerComputerControl)
{
    ui->setupUi(this);
    setWindowTitle(tr(""));
    setWindowState(Qt::WindowMaximized);

    /// ====== 初始化工具栏
    initToolBar();

    ui->splitter->setStretchFactor(0, 4);
    ui->splitter->setStretchFactor(1, 8);

    connect(ui->widgetNodeList, &OBNListNodeInform::signalOptionalHosts, this, &OBNLowerComputerControl::slotOptionalHosts);
    /// ======
    QString nQSSInform;
    QFile qssFile(":QSS/defaultStyle.qss");
    if(qssFile.open(QIODevice::ReadOnly))
    {
        nQSSInform = qssFile.readAll();
        qssFile.close();
        this->setStyleSheet(nQSSInform);
    }
    setWindowFlags(Qt::WindowCloseButtonHint);
}

OBNLowerComputerControl::~OBNLowerComputerControl()
{
    delete ui;
}

/// ====== 初始化工具栏
void OBNLowerComputerControl::initToolBar()
{
    m_toolBar = new QToolBar;
    m_toolBar->setStyleSheet("height:30");
    m_toolBar->addAction(QIcon(), tr("搜索"), this, &OBNLowerComputerControl::slotSearch);

    QLabel* nLabelItem = new QLabel("");
    nLabelItem->setFixedSize(20, 10);
    m_toolBar->addWidget(nLabelItem);

    n_selAllCheckBox = new QCheckBox(tr("全选"), this);
    connect(n_selAllCheckBox, &QCheckBox::stateChanged, this, &OBNLowerComputerControl::slotSelectall);
    n_selAllCheckBox->setChecked(false);
    m_toolBar->addWidget(n_selAllCheckBox);

    this->addToolBar(Qt::TopToolBarArea, m_toolBar);
}

/// ====== 语言设置和帮助文档
void OBNLowerComputerControl::slotSetupLanguage(const int& indexID)
{
    qDebug() << "indexID is:" << indexID;
}
void OBNLowerComputerControl::slotOpenHelpDocumentation(){}

/// ====== 搜索按钮槽函数
void OBNLowerComputerControl::slotSearch()
{
    if(NULL == m_obnSeatchHosts)
    {
        m_obnSeatchHosts = new OBNSearchHosts(this);
        connect(m_obnSeatchHosts, &OBNSearchHosts::signalCurrentHostsSend, this, &OBNLowerComputerControl::slotSearchHostsList);
    }
    m_obnSeatchHosts->open();
}
/// ====== 获取当前有效节点
void OBNLowerComputerControl::slotSearchHostsList(QVector<HostsState> pHostInforms)
{
    ui->widgetNodeList->setHostInforms(pHostInforms);
}

/// ======= 全选
void OBNLowerComputerControl::slotSelectall(int)
{
    if(NULL != n_selAllCheckBox)
    {
        bool flag = n_selAllCheckBox->checkState();
        n_selAllCheckBox->setChecked(flag);
        ui->widgetNodeList->selectAllFunction(flag);
    }
}

/// ======
void OBNLowerComputerControl::slotOptionalHosts(const QVector<HostsState>& pHostStateInforms)
{
    ui->widgetControl->setCurrentOptionalInform(pHostStateInforms);
}





























