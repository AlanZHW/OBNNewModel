#include "obnmainwindow.h"
#include "ui_obnmainwindow.h"

OBNMainWindow::OBNMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_createArea(NULL),
    m_updateArea(NULL),
    m_openSEGYDialog(NULL),
    m_exportSEGYDialog(NULL),
    m_openLmgrListWdget(NULL),
    m_dataItems(NULL),
    m_itemRoot(NULL),
    m_itemArea(NULL),
    n_processLoadData(NULL),
    m_processDisplay(NULL),
    n_processBaseMap(NULL),
    ui(new Ui::OBNMainWindow)
{
    ui->setupUi(this);

    m_translator = new QTranslator;

    switch(AppGlobal::getInstance()->getCurrentLanguageMode())
    {
    case 0:
        m_translator->load("mainwindow_cn.qm", ".");
        break;
    case 1:
        m_translator->load("mainwindow_en.qm", ".");
        break;
    default:
        break;
    }
    QCoreApplication::installTranslator(m_translator);
    ui->retranslateUi(this);

    /// ====== 设置软件标题
    setWindowTitle(tr("海底节点-控制软件"));    ///< Ocean bottom node
    /// ====== 设置软件默认最大化显示
    setWindowState(Qt::WindowMaximized);

    QDir bin_dir(QCoreApplication::applicationDirPath());
    bin_dir.cdUp();
    m_iconPath = bin_dir.absolutePath();
    m_iconPath += "/icon/";
    /// ====== 设置软件图标
    setWindowIcon(QIcon(m_iconPath+"module_lmgr.png"));

    /// 界面按钮信号槽和函数
    connect(ui->toolButtonNewArea,      SIGNAL(clicked(bool)), this, SLOT(slotNewArea(bool)));     ///< 新建观测系统
    connect(ui->toolButtonOpenArea,     SIGNAL(clicked(bool)), this, SLOT(slotOpenArea(bool)));    ///< 打开观测系统
    connect(ui->toolButtonUpdateArea,   SIGNAL(clicked(bool)), this, SLOT(slotUpdateArea(bool)));    ///< 修改观测系统
    connect(ui->toolButtonDeleteArea,   SIGNAL(clicked(bool)),  this, SLOT(slotDeleteArea(bool))); ///< 删除观测系统
    /// ====== 节点管理相关
    connect(ui->toolButtonRNM,                  SIGNAL(clicked(bool)), this, SLOT(slotRNMFunction(bool)));      ///< 节点管理
    connect(ui->toolButtonRealTimWaveform,      SIGNAL(clicked(bool)),  this, SLOT(slotRealTimWaveform(bool))); ///< 实时波形显示
    connect(ui->toolButtonOTA,                  SIGNAL(clicked(bool)), this, SLOT(slotOTA(bool)));              ///< 软件升级
    connect(ui->toolButtonPositionSystem,       SIGNAL(clicked(bool)), this, SLOT(slotPositionSystem(bool)));   ///< 定位系统
    /// ====== 数据管理相关
    connect(ui->toolButtonOpenSEGY,             SIGNAL(clicked(bool)), this, SLOT(slotOpenSEGY(bool)));         ///< 显示SEG-Y
    connect(ui->toolButtonExportSEGY,           SIGNAL(clicked(bool)), this, SLOT(slotExportSEGY(bool)));       ///< 导出SEG-Y
    connect(ui->toolButtonHTimeAnilysis,        SIGNAL(clicked(bool)),  this, SLOT(slotHTimeAnilysis(bool)));   ///< 水深信号分析
    connect(ui->toolButtonLogDisplay,           SIGNAL(clicked(bool)),  this, SLOT(slotLogDisplay(bool)));      ///< Log信息显示
    connect(ui->toolButtonCalibration,          SIGNAL(clicked(bool)), this, SLOT(slotCalibration(bool)));      ///< 标定
    /// ====== 质量控制相关
    connect(ui->toolButtonJobAnalysis,          SIGNAL(clicked(bool)), this, SLOT(slotJobAnalysis(bool)));     ///< 作业状态分析
    /// ====== 帮助文档
    connect(ui->toolButtonHelp, SIGNAL(clicked(bool)), this, SLOT(slotOpenHelpPrograme(bool)));

    /// ======
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /// ======
    m_labelStatubar = new QLabel;
    ui->statusbar->addPermanentWidget(m_labelStatubar);

    /// ====== 初始化界面
    initWindow();
    ui->treeView_DataList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView_DataList->setEditTriggers(QTreeView::NoEditTriggers);
    ui->treeView_DataList->setContextMenuPolicy(Qt::CustomContextMenu);
    /// ====== 数据列表槽函数链接
    connect(ui->treeView_DataList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotClickedDataList(const QModelIndex&)));
    connect(ui->treeView_DataList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomContextDataMenuFunc(QPoint)));
    /// ======
    ui->treeView_DataList->header()->hide();
    displayDataList();

    /// ======
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(38, 78, 119, 127));
    shadow_effect->setBlurRadius(22);
    ui->tabWidget->setGraphicsEffect(shadow_effect);
    /// ======
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=](int){
        displayDataList();
    });
    /// ====== 设置软件风格
    QString nQSSInform;
    QFile qssFile(":qss/defaultStyle.qss");
    if(qssFile.open(QIODevice::ReadOnly))
    {
        nQSSInform = qssFile.readAll();
        qssFile.close();
        this->setStyleSheet(nQSSInform);
    }
}

OBNMainWindow::~OBNMainWindow()
{
    delete ui;
}

void OBNMainWindow::displayDataList()
{
    switch(ui->tabWidget->currentIndex())
    {
    case 0:
    case 1:
    case 4:
        ui->treeView_DataList->hide();
        break;
    case 2:
    case 3:
        ui->treeView_DataList->show();
        break;
    default:
        return;
    }
}


void OBNMainWindow::setCurrentProjectInfrom(const QString& _projectName, const QString& _projectPath)
{
    m_currProjectName = _projectName;
    m_currProjectPath = _projectPath;

    m_projectInform.ProjectPath = m_currProjectPath;
    m_projectInform.ProjectName = m_currProjectName;

    ui->tabWidgetMain->setProjectInfo(m_currProjectPath, m_currProjectName);

    /// ====== 重新设置标题
    QString n_currentWindowTitle = tr("海底节点-控制系统") + " | " + _projectName;
    setWindowTitle(n_currentWindowTitle);

    /// ====== 初始化侧边栏
    initDataListInfoFunction();
}

void OBNMainWindow::paintEvent(QPaintEvent*)
{
}

///
void OBNMainWindow::slotRefreshTableStart(QString pFunc, QString Time)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(pFunc));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(Time));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(tr("运行中…")));
}

///
void OBNMainWindow::slotRefreshTableEnd(QString pFunc, QString Time)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setItem(row-1, 2, new QTableWidgetItem(tr("运行完成")));
    ui->tableWidget->setItem(row-1, 3, new QTableWidgetItem(Time));

    /// ====== 导入完成后刷新侧边栏
    /// showDataInfoListSeismicData();
}

void OBNMainWindow::initDataListInfoFunction()
{
#if 1
    if(NULL == m_dataItems)
    {
        m_dataItems = new QStandardItemModel;
    }
    else
    {
        m_dataItems->clear();
    }
    /// ======
    if(NULL == m_itemRoot)
    {
        m_itemRoot = new QStandardItem(tr("数据区"));
        m_itemRoot->setData(MARK_ITEM_ROOT, ROLE_MARK_FOLDER_PRI);
        m_dataItems->appendRow(m_itemRoot);
    }
    /// ====== 获取当前工区测边栏需要显示的内容
    showDataInfoListFunction();
    /// ======
    ui->treeView_DataList->setModel(m_dataItems);
    ui->treeView_DataList->expandAll();
    ui->treeView_DataList->header()->resizeSections(QHeaderView::ResizeToContents);
    ui->treeView_DataList->resizeColumnToContents(0);
#endif
}


/// 获取当前工区测边栏需要显示的内容
void OBNMainWindow::showDataInfoListFunction()
{
    /// ====== 清空树信息
    if(NULL == m_itemArea)
    {
        m_itemArea = new QStandardItem;
    }
    else
    {
        if(0 != m_itemArea->rowCount())
        {
            for(int iRow = m_itemArea->rowCount()-1; iRow >= 0; iRow --)
            {
                m_itemArea->removeRow(iRow);
            }
        }
    }
    /// ====== 获取当前Area列表
    QStringList nAreaNameList;
    if(Area::getAreaNames(m_projectInform, nAreaNameList))
    {
        return;
    }
    /// ====== 将Area列表设置到树上
    if(0 != nAreaNameList.count())
    {
        for(int iList = 0; iList < nAreaNameList.count(); iList ++)
        {
            QStandardItem* itemAram = new QStandardItem(QIcon(m_iconPath+"poststackcube.png"), nAreaNameList[iList]);
            itemAram->setData(MARK_ITEM_PRI,        DATA_MARK_FOLDER_SEC);

            QString areaPath = m_currProjectPath + "/" + m_currProjectName + nAreaNameList[iList];
            QDir    areaDir(areaPath);
            QFileInfoList fileInfoList = areaDir.entryInfoList();
            for(int iFile = 0; iFile < fileInfoList.count(); iFile ++)
            {
                if("R" == fileInfoList[iFile].suffix())
                {
                    QString nRFileName = fileInfoList[iFile].fileName();
                    QStandardItem* itemR = new QStandardItem(QIcon(m_iconPath+"poststackcube.png"), nAreaNameList[iList]);
                    itemR->setData(nRFileName,    ROLE_MARK_DATA_NAME);
                    itemR->setData(MARK_ITEM_SEC, DATA_MARK_FOLDER_SEC);
                    itemAram->appendRow(itemR);
                }
                if("S" == fileInfoList[iFile].suffix())
                {
                    QString nRFileName = fileInfoList[iFile].fileName();
                    QStandardItem* itemS = new QStandardItem(QIcon(m_iconPath+"poststackcube.png"), nAreaNameList[iList]);
                    itemS->setData(nRFileName,    ROLE_MARK_DATA_NAME);
                    itemS->setData(MARK_ITEM_SEC, DATA_MARK_FOLDER_SEC);
                    itemAram->appendRow(itemS);
                }
                if("X" == fileInfoList[iFile].suffix())
                {
                    QString nRFileName = fileInfoList[iFile].fileName();

                    QStandardItem* itemX = new QStandardItem(QIcon(m_iconPath+"poststackcube.png"), nAreaNameList[iList]);
                    itemX->setData(nRFileName,    ROLE_MARK_DATA_NAME);
                    itemX->setData(MARK_ITEM_SEC, DATA_MARK_FOLDER_SEC);
                    itemAram->appendRow(itemX);
                }
            }
            m_itemArea->appendRow(itemAram);
        }
    }
}

/// ====== QToolButton相关按钮槽函数
/// ====== 新建观测系统
void OBNMainWindow::slotNewArea(bool)
{
    m_labelStatubar->setText(tr("新建观测系统"));
    if(NULL == m_createArea)
    {
        m_createArea = new CreateAreaDialog(this);
        m_createArea->setProjectInfo(m_currProjectPath, m_currProjectName);
    }
    m_createArea->open();
}

/// ====== 打开观测系统
void OBNMainWindow::slotOpenArea(bool)
{
    m_labelStatubar->setText(tr("打开观测系统"));

    if(NULL != m_openLmgrListWdget)
    {
        delete m_openLmgrListWdget;
    }
    m_openLmgrListWdget = new OBNLMGRAreaListWidget(this);
    m_openLmgrListWdget->setProjectInform(m_currProjectPath, m_currProjectName);
    connect(m_openLmgrListWdget, &OBNLMGRAreaListWidget::signalCurrentAreaName, this, [=](const QString& _areaName){

        /// ====== 打开显示观测系统信息功能界面
        ui->tabWidgetMain->setLMGRDisplay(m_currProjectPath, m_currProjectName, _areaName);

        /// ====== 关闭观测系统列表界面
        m_openLmgrListWdget->close();
    });
    m_openLmgrListWdget->open();
}

/// ====== 修改观测系统
void OBNMainWindow::slotUpdateArea(bool)
{
    m_labelStatubar->setText(tr("修改观测系统"));
    if(NULL != m_updateArea)
    {
        m_updateArea->close();
        delete m_updateArea;
        m_updateArea = NULL;
    }
    m_updateArea = new UpdateAreaDialog(this);
    m_updateArea->open();
}

/// ====== 删除观测系统
void OBNMainWindow::slotDeleteArea(bool)
{
    m_labelStatubar->setText(tr("删除观测系统"));
}

/// ====== 节点管理
void OBNMainWindow::slotRNMFunction(bool)
{
    m_labelStatubar->setText(tr("远程节点管理器"));
    ui->tabWidgetMain->setRNMMainWindow();
}

/// ====== 标定
void OBNMainWindow::slotCalibration(bool)
{
    m_labelStatubar->setText(tr("标定数据显示"));
    ui->tabWidgetMain->setCalibrationDataDisplayProgrameWindow();
}

/// ====== 实时波形显示
void OBNMainWindow::slotRealTimWaveform(bool)
{
    m_labelStatubar->setText(tr("实时波形显示"));
    ui->tabWidgetMain->setRealTimeWaveformDispProgrameWindow();
}

/// ====== 软件升级
void OBNMainWindow::slotOTA(bool)
{
    m_labelStatubar->setText(tr("软件升级"));
    ui->tabWidgetMain->setOTAProgrameWindow();
}

/// ====== 定位系统
void OBNMainWindow::slotPositionSystem(bool)
{
    m_labelStatubar->setText(tr("定位系统"));
    ui->tabWidgetMain->setGPositiSystem();
}

/// ====== 显示SEG-Y
void OBNMainWindow::slotOpenSEGY(bool)
{
    m_labelStatubar->setText(tr("显示SEG-Y"));
    if(NULL == m_openSEGYDialog)
    {
        m_openSEGYDialog = new OpenSegyDlg(this);
        connect(m_openSEGYDialog, &OpenSegyDlg::signalOpenedFile, this, [=](QList<SegyFileHandle*> _pSegyHandle, int _maxTrace, int _startTrace, OpenFilesType _openFilesType){
            ui->tabWidgetMain->setDisplaySEGY(_pSegyHandle, _maxTrace, _startTrace, _openFilesType);
        });
    }
    m_openSEGYDialog->open();
}

/// ====== 导出SEG-Y
void OBNMainWindow::slotExportSEGY(bool)
{
    m_labelStatubar->setText(tr("导出SEG-Y"));
    if(NULL == m_exportSEGYDialog)
    {
        m_exportSEGYDialog = new ExportSegyDlg(this);
        m_exportSEGYDialog->setProjectInfo(m_projectInform);
    }
    m_exportSEGYDialog->open();
}

/// ====== 水深信号分析
void OBNMainWindow::slotHTimeAnilysis(bool)
{
    m_labelStatubar->setText(tr("水深信号分析"));
    ui->tabWidgetMain->setStdManagerDiffTime();
}

/// ====== Log信息显示
void OBNMainWindow::slotLogDisplay(bool)
{
    m_labelStatubar->setText(tr("Log信息显示"));
    ui->tabWidgetMain->setDisplayLogInform();
}

/// ====== 作业分析
void OBNMainWindow::slotJobAnalysis(bool)
{
    m_labelStatubar->setText(tr("作业分析"));
    ui->tabWidgetMain->setJobMonitorProgreamWindow();
}

/// ====== 帮助文档
void OBNMainWindow::slotOpenHelpPrograme(bool)
{
    m_labelStatubar->setText(tr("帮助文档"));
    bool ret = Assistant::showAssistant("Launcher");
    if(!ret)
    {
        QMessageBox::warning(this, tr("警告"), tr("打开帮助文档失败,请检查！"));
    }
}

#if 0
/// ======
void OBNMainWindow::showDataInfoListSeismicData()
{
    /// ==================== 地震数据 ======================
    QString IdxPath = m_currProjectPath+"Index/";

    QDir fileDir(IdxPath);
    fileDir.setFilter(QDir::Files);
    QFileInfoList fileInfoList = fileDir.entryInfoList();
    QStringList fileListIdx, fileListStk, fileListVel;
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(!fileInfo.isFile())
        {
            continue;
        }
        if(0 == fileInfo.suffix().compare("idx"))
        {
            QString fileName = fileInfo.fileName();
            fileListIdx.append(fileName);
        }
        if(0 == fileInfo.suffix().compare("stk"))
        {
            QString fileName = fileInfo.fileName();
            fileListStk.append(fileName);
        }
        if(0 == fileInfo.suffix().compare("vel"))
        {
            QString fileName = fileInfo.fileName();
            fileListVel.append(fileName);
        }
    }

    /// 清空树信息
    for(int iRow = m_itemSeismicData->rowCount()-1; iRow >= 0; iRow --)
    {
        m_itemSeismicData->removeRow(iRow);
    }
    for(int iRow = m_itemPostStackData->rowCount()-1; iRow >= 0; iRow --)
    {
        m_itemPostStackData->removeRow(iRow);
    }
    for(int iRow = m_itemVelocityData->rowCount()-1; iRow >= 0; iRow --)
    {
        m_itemVelocityData->removeRow(iRow);
    }
    ///
    foreach(QString nfileName, fileListIdx)
    {
        QStandardItem* itemIdx = new QStandardItem(QIcon(m_iconPath+"poststackcube.png"),nfileName);
        itemIdx->setData(MARK_ITEM_SEISMIC, DATA_MARK_FOLDER_SEC);
        itemIdx->setData(nfileName, ROLE_MARK_DATA_NAME);
        m_itemSeismicData->appendRow(itemIdx);
    }
    foreach(QString nfileName, fileListStk)
    {
        QStandardItem* itemIdx = new QStandardItem(QIcon(m_iconPath+"poststackcube.png"), nfileName);
        itemIdx->setData(MARK_ITEM_POSTSTAKE, DATA_MARK_FOLDER_SEC);
        itemIdx->setData(nfileName, ROLE_MARK_DATA_NAME);
        m_itemPostStackData->appendRow(itemIdx);
    }
    foreach (QString nfileName, fileListVel)
    {
        QStandardItem* itemIdx = new QStandardItem(QIcon(m_iconPath+"poststackcube.png"), nfileName);
        itemIdx->setData(MARK_ITEM_VELOCITY, DATA_MARK_FOLDER_SEC);
        itemIdx->setData(nfileName, ROLE_MARK_DATA_NAME);
        m_itemVelocityData->appendRow(itemIdx);
    }
}

/// ======
void OBNMainWindow::showDataInfoListHorizonData()
{
    /// 清空树信息
    for(int iRow = m_itemHorizonData->rowCount()-1; iRow >= 0; iRow --)
    {
        m_itemHorizonData->removeRow(iRow);
    }
    /// ==================== 层位数据 ======================
    QString nHorizonPath = m_currProjectPath+"Horizon/";
    QDir nHorizonDir(nHorizonPath);
    QStringList nPathNameListHorizon = nHorizonDir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);
    for(int iHorizon = 0; iHorizon < nPathNameListHorizon.count(); ++ iHorizon)
    {
        QStandardItem* itemHorizonInfo = new QStandardItem(QIcon(m_iconPath+"blackview.png"), nPathNameListHorizon.at(iHorizon));
        itemHorizonInfo->setData(MARK_ITEM_HORIZON_DATA, DATA_MARK_FOLDER_SEC);
        itemHorizonInfo->setData(nPathNameListHorizon.at(iHorizon), ROLE_MARK_HORIZON_SEC);
        m_itemHorizonData->appendRow(itemHorizonInfo);
    }
    nPathNameListHorizon.clear();
}

void OBNMainWindow::showDataInfoListLoggingData()
{
    /// 清空树信息
    for(int iRow = m_itemLoggingData->rowCount()-1; iRow >= 0; iRow --)
    {
        m_itemLoggingData->removeRow(iRow);
    }
    /// ==================== 测井数据 ======================
    QString nLoggingPath = m_currProjectPath+"Logging//";
    QDir nLoggingDir(nLoggingPath);
    QStringList nPathNameList = nLoggingDir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);
    for(int iLogName = 0; iLogName < nPathNameList.count(); ++ iLogName)
    {
        QStandardItem* itemLogName = new QStandardItem(QIcon(m_iconPath+"井架1.png"), nPathNameList.at(iLogName));
        itemLogName->setData(MARK_ITEM_SPEC_NAME,        DATA_MARK_FOLDER_SEC);
        itemLogName->setData(nPathNameList.at(iLogName), ROLE_MARK_LOGGING_SEC);

        QString loggingPath = m_currProjectPath + "Logging//" + nPathNameList[iLogName];
        QDir nLogDataDir(loggingPath);
        QFileInfoList nLogfileInfoList = nLogDataDir.entryInfoList(QDir::Files | QDir::CaseSensitive);
        foreach (QFileInfo nfileInfo, nLogfileInfoList)
        {
            if(nfileInfo.suffix().compare("lgging") == 0)
            {
                QStandardItem* itemDatavolume   = new QStandardItem(QIcon(m_iconPath+"测井曲线数据.png"), nfileInfo.baseName());
                itemDatavolume->setData(MARK_ITEM_LOGDATA, ROLE_MARK_DATA_SEC);
                itemLogName->appendRow(itemDatavolume);
            }
        }
        QString mudLogfName  = m_currProjectPath + "Logging//" + nPathNameList[iLogName] + "//ModLogFile";
        QStringList mudLogHeadList;
        QFile fileMudLog(mudLogfName);
        if(fileMudLog.exists())
        {
            if(fileMudLog.open(QIODevice::ReadOnly))
            {

                QTextCodec *code = NULL;
                code = QTextCodec::codecForName("utf8");

                QTextStream in(&fileMudLog);
                in.setCodec(code);

                while(!in.atEnd())
                {
                    QString n_readString = in.readLine().trimmed();
                    n_readString.replace(QRegExp("[\\s]+"), " ");
                    QStringList nListMudInfo = n_readString.split(" ");
                    mudLogHeadList.append(nListMudInfo[0]);
                }
                fileMudLog.close();
            }
        }
        if(0 != mudLogHeadList.count())
        {
            for(int iMudList = 0; iMudList < mudLogHeadList.count(); ++ iMudList)
            {
                QStandardItem* itemDataMudLog   = new QStandardItem(QIcon(m_iconPath+"录井层位.png"),mudLogHeadList[iMudList]);
                itemLogName->appendRow(itemDataMudLog);
            }
            mudLogHeadList.clear();
        }
        m_itemLoggingData->appendRow(itemLogName);
    }
    nPathNameList.clear();
}
#endif

/// 数据列表单击槽函数
void OBNMainWindow::slotClickedDataList(const QModelIndex& index)
{

}

void OBNMainWindow::slotRefushSidebarList()
{
    showDataInfoListFunction();
}

void OBNMainWindow::slotCustomContextDataMenuFunc(QPoint point)
{
    QModelIndex index = ui->treeView_DataList->indexAt(point);
    QVariant var;
    var = index.data(DATA_MARK_FOLDER_SEC);
#if 0
    if(var.isValid())
    {
        if(MARK_ITEM_SEISMIC == var.toInt())
        {
            m_currDataName = index.data(ROLE_MARK_DATA_NAME).toString();

            QMenu* seismicMenu = new QMenu();
            seismicMenu->exec(QCursor::pos());
            seismicMenu->clear();
        }
        if(MARK_ITEM_POSTSTAKE == var.toInt())
        {
            qDebug() << ("叠后数据");
            QMenu* postStackMenu = new QMenu();
            postStackMenu->exec(QCursor::pos());
            postStackMenu->clear();
        }
        if(MARK_ITEM_VELOCITY == var.toInt())
        {
            QMenu* postVelocityMenu = new QMenu();
            postVelocityMenu->exec(QCursor::pos());
            postVelocityMenu->clear();
        }
        if(MARK_ITEM_HORIZON == var.toInt())
        {
            qDebug() << ("层位数据");
            QMenu* horizonMenu = new QMenu();
            horizonMenu->exec(QCursor::pos());
            horizonMenu->clear();
        }
        if(MARK_ITEM_HORIZON_DATA == var.toInt())
        {
            QMenu* horizonMenu = new QMenu();
            horizonMenu->exec(QCursor::pos());
            horizonMenu->clear();
        }
        if(MARK_ITEM_LOGGING_NAME == var.toInt())
        {
            qDebug() << ("井名");

            QMenu* loggingMenu = new QMenu();
            loggingMenu->addAction(("新建井"), this, SLOT(slotNewLogging()));
            loggingMenu->exec(QCursor::pos());
            loggingMenu->clear();
        }
        if(MARK_ITEM_SPEC_NAME == var.toInt())
        {
            QMenu* logNameMenu = new QMenu();
            logNameMenu->exec(QCursor::pos());
            logNameMenu->clear();
        }
    }
#endif
}

void OBNMainWindow::initWindow()
{
    /// 设置表格内容
    QStringList tableHeader;
    ui->tableWidget->setColumnCount(4);
    tableHeader << tr("事件") << tr("起始时间") << tr("状态") << tr("终了时间");
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setShowGrid(false);

    /// ====== 观测系统相关
    setToolButtonIconInfo(ui->toolButtonNewArea);       ///< 新建观测系统
    setToolButtonStyleSheet(ui->toolButtonNewArea);

    setToolButtonIconInfo(ui->toolButtonOpenArea);      ///< 打开观测系统
    setToolButtonStyleSheet(ui->toolButtonOpenArea);

    setToolButtonIconInfo(ui->toolButtonUpdateArea);    ///< 修改观测系统
    setToolButtonStyleSheet(ui->toolButtonUpdateArea);

    setToolButtonIconInfo(ui->toolButtonDeleteArea);    ///< 删除观测系统
    setToolButtonStyleSheet(ui->toolButtonDeleteArea);

    /// ====== 节点管理相关
    setToolButtonIconInfo(ui->toolButtonRNM);           ///< 节点管理
    setToolButtonStyleSheet(ui->toolButtonRNM);

    setToolButtonIconInfo(ui->toolButtonCalibration);   ///< 标定
    setToolButtonStyleSheet(ui->toolButtonCalibration);

    setToolButtonIconInfo(ui->toolButtonRealTimWaveform);   ///< 实时波形显示
    setToolButtonStyleSheet(ui->toolButtonRealTimWaveform);

    setToolButtonIconInfo(ui->toolButtonOTA);           ///< 软件升级
    setToolButtonStyleSheet(ui->toolButtonOTA);

    setToolButtonIconInfo(ui->toolButtonPositionSystem);   ///< 定位系统
    setToolButtonStyleSheet(ui->toolButtonPositionSystem);

    /// ====== 数据管理相关
    setToolButtonIconInfo(ui->toolButtonOpenSEGY);              ///< 显示SEG-Y
    setToolButtonStyleSheet(ui->toolButtonOpenSEGY);

    setToolButtonIconInfo(ui->toolButtonExportSEGY);            ///< 导出SEG-Y
    setToolButtonStyleSheet(ui->toolButtonExportSEGY);

    setToolButtonIconInfo(ui->toolButtonHTimeAnilysis);   ///< 水深信号分析
    setToolButtonStyleSheet(ui->toolButtonHTimeAnilysis);

    setToolButtonIconInfo(ui->toolButtonLogDisplay);            ///< Log信息显示
    setToolButtonStyleSheet(ui->toolButtonLogDisplay);

    /// ====== 质量控制相关
    setToolButtonIconInfo(ui->toolButtonJobAnalysis);   ///< 作业状态分析
    setToolButtonStyleSheet(ui->toolButtonJobAnalysis);

    /// ======
    setToolButtonIconInfo(ui->toolButtonHelp);   ///< 作业状态分析
    setToolButtonStyleSheet(ui->toolButtonHelp);

    /// ======
    this->setFocusPolicy(Qt::StrongFocus);
}

/// ====== 设置QToolButton属性
void OBNMainWindow::setToolButtonStyleSheet(QToolButton* pToolButton)
{
    pToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    pToolButton->setContextMenuPolicy(Qt::CustomContextMenu);
    pToolButton->setStyleSheet("border:none");
}

/// ======
void OBNMainWindow::setToolButtonIconInfo(QToolButton* pToolButton)
{
    pToolButton->setFixedSize(100,78);

    /// ====== 观测系统相关
    if(pToolButton == ui->toolButtonNewArea)
    {
        pToolButton->setIcon(QIcon(":image/NewArea.png"));
        pToolButton->setText(tr("新建观测系统"));
    }
    if(pToolButton == ui->toolButtonOpenArea)
    {
        pToolButton->setIcon(QIcon(":image/OpenArea.png"));
        pToolButton->setText(tr("打开观测系统"));
    }
    if(pToolButton == ui->toolButtonUpdateArea)
    {
        pToolButton->setIcon(QIcon(":image/UpdateArea.png"));
        pToolButton->setText(tr("修改观测系统"));
    }
    if(pToolButton == ui->toolButtonDeleteArea)
    {
        pToolButton->setIcon(QIcon(":image/DeleteArea.png"));
        pToolButton->setText(tr("删除观测系统"));
    }
    /// ====== 节点管理相关
    if(pToolButton == ui->toolButtonRNM)
    {
        pToolButton->setIcon(QIcon(":image/NewArea.png"));
        pToolButton->setText(tr("节点管理"));
    }
    if(pToolButton == ui->toolButtonRealTimWaveform)
    {
        pToolButton->setIcon(QIcon(":image/RealTimeWareform.png"));
        pToolButton->setText(tr("实时波形显示"));
    }
    if(pToolButton == ui->toolButtonOTA)
    {
        pToolButton->setIcon(QIcon(":image/OTA.png"));
        pToolButton->setText(tr("软件升级"));
    }
    if(pToolButton == ui->toolButtonPositionSystem)
    {
        pToolButton->setIcon(QIcon(":image/PositionSystem.png"));
        pToolButton->setText(tr("定位系统"));
    }
    /// ====== 数据管理相关
    if(pToolButton == ui->toolButtonOpenSEGY)
    {
        pToolButton->setIcon(QIcon(":image/DataDisplay.png"));
        pToolButton->setText(tr("显示SEG-Y"));
    }
    if(pToolButton == ui->toolButtonExportSEGY)
    {
        pToolButton->setIcon(QIcon(":image/ExportSEGY.png"));
        pToolButton->setText(tr("导出SEG-Y"));
    }
    if(pToolButton == ui->toolButtonHTimeAnilysis)
    {
        pToolButton->setIcon(QIcon(":image/HTimeAnilysis.png"));
        pToolButton->setText(tr("水声信号分析"));
    }
    if(pToolButton == ui->toolButtonLogDisplay)
    {
        pToolButton->setIcon(QIcon(":image/LogDisplay.png"));
        pToolButton->setText(tr("Log信息显示"));
    }
    if(pToolButton == ui->toolButtonCalibration)
    {
        pToolButton->setIcon(QIcon(":image/Calibration.png"));
        pToolButton->setText(tr("标定数据显示"));
    }
    /// ====== 质量控制相关
    if(pToolButton == ui->toolButtonJobAnalysis)
    {
        pToolButton->setIcon(QIcon(":image/JobAnalysis.png"));
        pToolButton->setText(tr("作业分析"));
    }
    /// ====== 质量控制相关
    if(pToolButton == ui->toolButtonHelp)
    {
        pToolButton->setIcon(QIcon(":image/Help.png"));
        pToolButton->setText(tr("帮助文档"));
    }
    /// ======
    pToolButton->setIconSize(QSize(70, 70));
}

#if 0
void OBNMainWindow::slotDefault(bool)
{
    QString nDefaultInfo = "Default";
    swigd_setStyle(nDefaultInfo);
    swigd_updateStyle();
}
void OBNMainWindow::slotCoffee(bool)
{
    QString nDefaultInfo = "Coffee";
    swigd_setStyle(nDefaultInfo);
    swigd_updateStyle();
}
void OBNMainWindow::slotMetro(bool)
{
    QString nDefaultInfo = "MetroUI";
    swigd_setStyle(nDefaultInfo);
    swigd_updateStyle();
}
#endif

#if 0
void OBNMainWindow::slotDisplayData(bool)
{
    qDebug() << ("显示");
    m_labelStatubar->setText(("显示"));
    if(m_currProjectName.isEmpty())
    {
        QMessageBox::warning(this, ("提示"), ("请选择工区和数据后进行显示."));
        return;
    }
    int isStack = 0;
    QString n_gatherName;
    QModelIndex index = ui->treeView_DataList->currentIndex();
    QVariant inderVar = index.data(DATA_MARK_FOLDER_SEC);
    if(inderVar.isValid())
    {
        int isVar = index.data(DATA_MARK_FOLDER_SEC).toString().toInt();;
        if(isVar == MARK_ITEM_SEISMIC)
        {
            isStack = 0;
        }
        else if(isVar == MARK_ITEM_POSTSTAKE)
        {
            isStack = 1;
        }
        else if(isVar == MARK_ITEM_VELOCITY)
        {
            isStack = 2;
        }
        else
        {
            return;
        }
        n_gatherName = index.data(ROLE_MARK_DATA_NAME).toString();

        QFileInfo fName(n_gatherName);
        QString   nSuffixInfo = "."+fName.suffix();
        n_gatherName.replace(nSuffixInfo, "");

#if 1
        ui->tabWidgetMain->setDataDisplay(n_gatherName, isStack);
#else
        Display w;
        w.setProjectInfo(m_currProjectPath, m_currProjectName);
        w.setGatherInfo(n_gatherName, isStack);
#endif
    }
    else
    {
#if 1
        ui->tabWidgetMain->setDataDisplay();
#else
        DataMgrControl *w = new DataMgrControl(this);
        w->init(m_currProjectName, m_currProjectPath);
        w->show();
#endif
    }
#if 0
    QStringList argvList;
    argvList << m_currProjectPath << m_currProjectName << n_gatherName << QString::number(isStack);
    qDebug() << "argvList = " << argvList;
    QString nDisplayModuleName = m_binPath + "Display.exe";
    if(NULL == m_processDisplay)
    {
        m_processDisplay = new QProcess(this);
        m_processDisplay->setProcessChannelMode(QProcess::ForwardedChannels);
    }
    m_processDisplay->start(nDisplayModuleName, argvList);
#endif
}
#endif

void OBNMainWindow::slotRefreshDataList()
{
    showDataInfoListFunction();
}
