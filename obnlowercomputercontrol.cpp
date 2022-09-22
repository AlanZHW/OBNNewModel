#include "obnlowercomputercontrol.h"
#include "ui_obnlowercomputercontrol.h"

OBNLowerComputerControl::OBNLowerComputerControl(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OBNLowerComputerControl)
{
    ui->setupUi(this);
    setWindowTitle(tr(""));
    setWindowState(Qt::WindowMaximized);

    /// ====== 初始化工具栏
    initToolBar();

    ui->splitter->setStretchFactor(0, 4);
    ui->splitter->setStretchFactor(1, 8);
    /// ======
    QString nQSSInform;
    QFile qssFile(":QSS/dialog.qss");
    if(qssFile.open(QIODevice::ReadOnly))
    {
        nQSSInform = qssFile.readAll();
        qssFile.close();
        this->setStyleSheet(nQSSInform);
    }
}

OBNLowerComputerControl::~OBNLowerComputerControl()
{
    delete ui;
}

/// ====== 初始化工具栏
void OBNLowerComputerControl::initToolBar()
{
    m_toolBar = new QToolBar;
    m_toolBar->addAction(QIcon(), tr("搜索"), this, &OBNLowerComputerControl::slotSearch);
    QCheckBox* n_selAllCheckBox = new QCheckBox(tr("全选"), this);
    connect(n_selAllCheckBox, &QCheckBox::stateChanged, this, &OBNLowerComputerControl::slotSelectall);
    m_toolBar->addWidget(n_selAllCheckBox);
    m_toolBar->addAction(QIcon(), tr("下载"), this, &OBNLowerComputerControl::slotdownload);
    m_toolBar->addAction(QIcon(), tr("上传"), this, &OBNLowerComputerControl::slotupload);
    m_toolBar->addAction(QIcon(), tr("升级"), this, &OBNLowerComputerControl::slotupgrade);
    this->addToolBar(Qt::TopToolBarArea, m_toolBar);
}


/// ====== 搜索按钮槽函数
void OBNLowerComputerControl::slotSearch()
{
    m_obnSeatchHosts = new OBNSearchHosts(this);
    connect(m_obnSeatchHosts, &OBNSearchHosts::signalCurrentHostsSend, this, &OBNLowerComputerControl::slotSearchHostsList);
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

}

/// ===== 下载
void OBNLowerComputerControl::slotdownload()
{

}

/// ===== 上传
void OBNLowerComputerControl::slotupload()
{

}

/// ===== 升级
void OBNLowerComputerControl::slotupgrade()
{

}
