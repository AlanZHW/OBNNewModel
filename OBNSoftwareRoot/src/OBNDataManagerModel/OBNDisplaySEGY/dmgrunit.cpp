#include "dmgrunit.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QListWidget>

#include "obndisplaysegy.h"
#include "segy.h"

/// ========================================= QMenuManager
MenuManager::MenuManager(QObject *parent)
    :QObject(parent)
{
}

void MenuManager::createMenu(OBNDisplaySEGY *dataMgrControl,QMenuBar *menuBar)
{
    //菜单
    fileMenu = new QMenu("File",menuBar);
    fileMenu->addAction(tr("&Exit"), dataMgrControl,SLOT(slotExit()), QKeySequence(tr("Ctrl+Q")));
    menuBar->addMenu(fileMenu);
    //tools
    toolsMenu = new QMenu(tr("Tools"),menuBar);
    toolsMenu->addAction(tr("Display Option"), dataMgrControl,SLOT(slotDisplayOption()));
    menuBar->addMenu(toolsMenu);
    //其他菜单扩展
    helpMenu = new QMenu(tr("Help"));
    helpMenu->addAction(tr("Help"),dataMgrControl,SLOT(slotAbout()));
    menuBar->addMenu(helpMenu);
}



/// ============================================ QToolManager
ToolManager::ToolManager(QObject *parent)
    :QObject(parent)
{
}

void ToolManager::createTools(OBNDisplaySEGY *dataMgrControl,QToolBar *toolBar)
{
    QString n_Path = QCoreApplication::applicationDirPath();

    toolBar->setIconSize(QSize(24,24));

    /// ====== 前后播放，跳转到某一道集
    toolBar->addAction(QIcon(n_Path + "/Image/previous.png"),"Previous Gather",dataMgrControl, SLOT(slotPreviousGather()));
    toolBar->addAction(QIcon(n_Path + "/Image/next.png"),    "Next Gather",    dataMgrControl, SLOT(slotNextGather()));
    toolBar->addAction(QIcon(n_Path + "/Image/move.png"),    "Move To Gather", dataMgrControl, SLOT(slotMoveToGather()));
    toolBar->addSeparator();

    /// ====== zoom In 缩放
    m_zoomInBtn = new DownToolButton(toolBar);
    m_zoomInBtn->setText("Zoom In");
    m_zoomInBtn->setToolTip("Zoom In");
    m_zoomInBtn->setIcon(QIcon(n_Path + "/Image/zoom_in.png"));

    connect(m_zoomInBtn,SIGNAL(btnTriggerDowned(bool)), this,SLOT(slotZoomIn(bool)));
    connect(this,SIGNAL(signalZoomInEnable(bool)),dataMgrControl,SLOT(slotZoomIn(bool)));
    toolBar->addWidget(m_zoomInBtn);

    /// ====== zoom Out
    QToolButton *zoomOutBtn = new QToolButton(toolBar);
    zoomOutBtn->setText("Zoom Out");
    zoomOutBtn->setToolTip("Zoom Out");
    zoomOutBtn->setIcon(QIcon(n_Path + "/Image/zoom_out.png"));
    connect(zoomOutBtn,SIGNAL(clicked()),dataMgrControl,SLOT(slotZoomOut()));
    toolBar->addWidget(zoomOutBtn);

    toolBar->addSeparator();

    /// ====== trace header
    m_traceInfBtn = new DownToolButton(toolBar);
    m_traceInfBtn->setText("Trace Information");
    m_traceInfBtn->setIcon(QIcon(n_Path + "/Image/information.png"));
    toolBar->addWidget(m_traceInfBtn);
    m_traceInfBtn->setToolTip("Trace Header Information");
    connect(m_traceInfBtn,SIGNAL(btnTriggerDowned(bool)),this,SLOT(slotTraceInformation(bool)));
    connect(this,SIGNAL(signalTraceInformEnable(bool)),dataMgrControl,SLOT(slotTraceInform(const bool&)));

    /// ====== display option
    toolBar->addAction(QIcon(n_Path + "/Image/settings.png"),"Display Option",dataMgrControl,SLOT(slotDisplayOption()));
}

void ToolManager::slotZoomIn(bool enable)
{
    bool zoomEnable = enable;
    if(zoomEnable)
    {
        m_traceInfBtn->setBtnDown(false);
    }
    emit signalZoomInEnable(zoomEnable);
}

void ToolManager::slotTraceInformation(bool enable)
{
    bool traceInforEnable = enable;
    if(traceInforEnable)
        m_zoomInBtn->setBtnDown(false);
    emit signalTraceInformEnable(traceInforEnable);
}






