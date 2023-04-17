#include "obnlogvisuailzationdisplay.h"
#include "ui_obnlogvisuailzationdisplay.h"


OBNLogVisuailzationDisplay::OBNLogVisuailzationDisplay(QWidget *parent)
    : QDialog(parent), m_readLogThread(NULL), m_readLogProgress(NULL), m_logVisuailzationChart(NULL), m_curentDisplaying(false)
    , ui(new Ui::OBNLogVisuailzationDisplay)
{
    ui->setupUi(this);

    setWindowTitle(tr("Log显示"));
    /// ====== 设置输入框为只读属性
    ui->lineEditInputPath->setReadOnly(true);
    /// ====== 设置复选按钮默认为未选中
    ui->radioButtonT->setChecked(false);
    ui->radioButtonP->setChecked(false);
    ui->radioButtonBATV->setChecked(false);
    ui->radioButtonTheta->setChecked(false);
    ui->radioButtonGamma->setChecked(false);
    ui->radioButtonAz->setChecked(false);
    /// ====== 设置浏览按钮点击信号
    connect(ui->pushButtonBrowse, &QPushButton::clicked, this, &OBNLogVisuailzationDisplay::slotPushButtonBrowse);
    /// ====== 设置复选按钮状态改变信号
    connect(ui->radioButtonBATV,  &QRadioButton::clicked, this, &OBNLogVisuailzationDisplay::slotSetCurrentDisplayLabel);
    connect(ui->radioButtonT,     &QRadioButton::clicked, this, &OBNLogVisuailzationDisplay::slotSetCurrentDisplayLabel);
    connect(ui->radioButtonP,     &QRadioButton::clicked, this, &OBNLogVisuailzationDisplay::slotSetCurrentDisplayLabel);
    connect(ui->radioButtonTheta, &QRadioButton::clicked, this, &OBNLogVisuailzationDisplay::slotSetCurrentDisplayLabel);
    connect(ui->radioButtonGamma, &QRadioButton::clicked, this, &OBNLogVisuailzationDisplay::slotSetCurrentDisplayLabel);
    connect(ui->radioButtonAz,    &QRadioButton::clicked, this, &OBNLogVisuailzationDisplay::slotSetCurrentDisplayLabel);
    /// ====== 双击表格行
    connect(ui->tableWidgetSetupLineColor, &QTableWidget::doubleClicked, this, [=](const QModelIndex &index){
        int nCurentRowNO = index.row();

        QColorDialog* n_colorDialog = new QColorDialog(m_logInformDispData[nCurentRowNO].nLineColor);
        connect(n_colorDialog, &QColorDialog::colorSelected, this, [=](const QColor &color){
            /// ====== 保存选择的颜色
            m_logInformDispData[nCurentRowNO].nLineColor = color;
            /// ====== 改变表格显示的颜色
            QLabel * nTmpLabel = (QLabel*)(ui->tableWidgetSetupLineColor->cellWidget(nCurentRowNO, LINE_COLOR_COLUMN));
            nTmpLabel->setStyleSheet("QLabel{background-color:#" + QString::number(m_logInformDispData[nCurentRowNO].nLineColor.rgba(), 16)+"}");
            /// ====== 若已经选择了显示数据,则需要同步改变线颜色
            if(m_curentDisplaying)
            {
                m_logVisuailzationChart->setCurveColor(nCurentRowNO, color);
            }
        });
        n_colorDialog->open();
    });
}

OBNLogVisuailzationDisplay::~OBNLogVisuailzationDisplay()
{
    if(0 != m_logInformDispData.count())
    {
        for(int iList = 0; iList < m_logInformDispData.count(); iList ++)
        {
            m_logInformDispData[iList].nSuctLogInformList.clear();
        }
        m_logInformDispData.clear();
    }
    delete ui;
}

/// ====== 点击不同的曲线进行显示
void OBNLogVisuailzationDisplay::slotSetCurrentDisplayLabel()
{
    if(0 == m_logInformDispData.count())
    {
        QMessageBox::information(this, tr("提示"), tr("提示：请先导入曲线！"), tr("确定"));
        return;
    }
    m_curentDisplaying = true;

    for(int iTableRow = 0; iTableRow < ui->tableWidgetSetupLineColor->rowCount(); iTableRow ++)
    {
        QCheckBox* nCheckBox = (QCheckBox*)ui->tableWidgetSetupLineColor->cellWidget(iTableRow, LINE_ISDISP_COLUMN);
        nCheckBox->setChecked(true);
    }

    qreal curveMin = 0, curveMax = 0;
    int   nDataMax = 0;
    QList<QList<QPointF>> nlistPointfList;
    if(NULL != m_logVisuailzationChart || 0 == m_logInformDispData.count())
    {
        if(ui->radioButtonBATV == sender())
        {
            m_logVisuailzationChart->setChartName("BAT-V(V)");
            /// ====== 显示BAT-V曲线
            getBatVRange(curveMin, curveMax, nDataMax, nlistPointfList);
            /// ====== 更新曲线坐标
            m_logVisuailzationChart->setCurrentDataRange(0, nDataMax, curveMin, curveMax);
            m_logVisuailzationChart->setCurrentLogData(nlistPointfList);
        }
        if(ui->radioButtonT == sender())
        {
            m_logVisuailzationChart->setChartName("T(°)");
            /// ====== 显示T曲线
            getTRange(curveMin, curveMax, nDataMax, nlistPointfList);
            /// ====== 更新曲线坐标
            m_logVisuailzationChart->setCurrentDataRange(0, nDataMax, curveMin, curveMax);
            m_logVisuailzationChart->setCurrentLogData(nlistPointfList);
        }
        if(ui->radioButtonP == sender())
        {
            m_logVisuailzationChart->setChartName("P(MPa)");
            /// ====== 显示P曲线
            getPVRange(curveMin, curveMax, nDataMax, nlistPointfList);
            /// ====== 更新曲线坐标
            m_logVisuailzationChart->setCurrentDataRange(0, nDataMax, curveMin, curveMax);
            m_logVisuailzationChart->setCurrentLogData(nlistPointfList);
        }
        if(ui->radioButtonTheta == sender())
        {
            m_logVisuailzationChart->setChartName("Theta(°)");
            /// ====== 显示Theta曲线
            getThetaRange(curveMin, curveMax, nDataMax, nlistPointfList);
            /// ====== 更新曲线坐标
            m_logVisuailzationChart->setCurrentDataRange(0, nDataMax, curveMin, curveMax);
            m_logVisuailzationChart->setCurrentLogData(nlistPointfList);
        }
        if(ui->radioButtonGamma == sender())
        {
            m_logVisuailzationChart->setChartName("Gamma(°)");
            /// ====== 显示Gamma曲线
            getGammaRange(curveMin, curveMax, nDataMax, nlistPointfList);
            /// ====== 更新曲线坐标
            m_logVisuailzationChart->setCurrentDataRange(0, nDataMax, curveMin, curveMax);
            m_logVisuailzationChart->setCurrentLogData(nlistPointfList);
        }
        if(ui->radioButtonAz == sender())
        {
            m_logVisuailzationChart->setChartName("Az(°)");
            /// ====== 显示Az曲线
            getAzRange(curveMin, curveMax, nDataMax, nlistPointfList);
            /// ====== 更新曲线坐标
            m_logVisuailzationChart->setCurrentDataRange(0, nDataMax, curveMin, curveMax);
            m_logVisuailzationChart->setCurrentLogData(nlistPointfList);
        }
    }
    /// ====== 释放空间
    for(int iList = 0; iList < nlistPointfList.count(); iList ++)
    {
        nlistPointfList[iList].clear();
    }
    nlistPointfList.clear();
}

void OBNLogVisuailzationDisplay::getBatVRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF>>& pListPointfList)
{
    _min        = m_logInformDispData[0].nSuctLogInformList[0].batF;
    _max        = m_logInformDispData[0].nSuctLogInformList[0].batF;
    _dtNumMax   = m_logInformDispData[0].nSuctLogInformList.count();
    for(int iList = 0; iList < m_logInformDispData.count(); iList ++)
    {
        _dtNumMax = qMax(_dtNumMax, m_logInformDispData[iList].nSuctLogInformList.count());

        QList<QPointF> nTempPointfList;
        for(int jList = 0; jList < m_logInformDispData[iList].nSuctLogInformList.count(); jList ++)
        {
            _min = qMin(_min, m_logInformDispData[iList].nSuctLogInformList[jList].batF);
            _max = qMax(_max, m_logInformDispData[iList].nSuctLogInformList[jList].batF);

            QPointF pointF(jList, m_logInformDispData[iList].nSuctLogInformList[jList].batF);
            nTempPointfList.append(pointF);
        }
        pListPointfList.append(nTempPointfList);
    }
    _min -= 0.5;
    _max += 0.5;
}

void OBNLogVisuailzationDisplay::getTRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF>>& pListPointfList)
{
    _min = m_logInformDispData[0].nSuctLogInformList[0].TNum;
    _max = m_logInformDispData[0].nSuctLogInformList[0].TNum;
    _dtNumMax   = m_logInformDispData[0].nSuctLogInformList.count();
    for(int iList = 0; iList < m_logInformDispData.count(); iList ++)
    {
        _dtNumMax = qMax(_dtNumMax, m_logInformDispData[iList].nSuctLogInformList.count());

        QList<QPointF> nTempPointfList;
        for(int jList = 0; jList < m_logInformDispData[iList].nSuctLogInformList.count(); jList ++)
        {
            _min = qMin(_min, m_logInformDispData[iList].nSuctLogInformList[jList].TNum);
            _max = qMax(_max, m_logInformDispData[iList].nSuctLogInformList[jList].TNum);

            QPointF pointF(jList, m_logInformDispData[iList].nSuctLogInformList[jList].TNum);
            nTempPointfList.append(pointF);
        }
        pListPointfList.append(nTempPointfList);
    }
    _min -= 100;
    _max += 100;
}

void OBNLogVisuailzationDisplay::getPVRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF>>& pListPointfList)
{
    _min = m_logInformDispData[0].nSuctLogInformList[0].PNum;
    _max = m_logInformDispData[0].nSuctLogInformList[0].PNum;
    _dtNumMax   = m_logInformDispData[0].nSuctLogInformList.count();
    for(int iList = 0; iList < m_logInformDispData.count(); iList ++)
    {
        _dtNumMax = qMax(_dtNumMax, m_logInformDispData[iList].nSuctLogInformList.count());

        QList<QPointF> nTempPointfList;
        for(int jList = 0; jList < m_logInformDispData[iList].nSuctLogInformList.count(); jList ++)
        {
            _min = qMin(_min, m_logInformDispData[iList].nSuctLogInformList[jList].PNum);
            _max = qMax(_max, m_logInformDispData[iList].nSuctLogInformList[jList].PNum);

            QPointF pointF(jList, m_logInformDispData[iList].nSuctLogInformList[jList].PNum);
            nTempPointfList.append(pointF);
        }
        pListPointfList.append(nTempPointfList);
    }
    _min -= 1000;
    _max += 1000;
}

void OBNLogVisuailzationDisplay::getThetaRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF>>& pListPointfList)
{
    _min = m_logInformDispData[0].nSuctLogInformList[0].ThetaNum;
    _max = m_logInformDispData[0].nSuctLogInformList[0].ThetaNum;
    _dtNumMax   = m_logInformDispData[0].nSuctLogInformList.count();
    for(int iList = 0; iList < m_logInformDispData.count(); iList ++)
    {
        _dtNumMax = qMax(_dtNumMax, m_logInformDispData[iList].nSuctLogInformList.count());

        QList<QPointF> nTempPointfList;
        for(int jList = 0; jList < m_logInformDispData[iList].nSuctLogInformList.count(); jList ++)
        {
            _min = qMin(_min, m_logInformDispData[iList].nSuctLogInformList[jList].ThetaNum);
            _max = qMax(_max, m_logInformDispData[iList].nSuctLogInformList[jList].ThetaNum);

            QPointF pointF(jList, m_logInformDispData[iList].nSuctLogInformList[jList].ThetaNum);
            nTempPointfList.append(pointF);
        }
        pListPointfList.append(nTempPointfList);
    }
    _min -= 100;
    _max += 100;
}

void OBNLogVisuailzationDisplay::getGammaRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF>>& pListPointfList)
{
    _min = m_logInformDispData[0].nSuctLogInformList[0].GammaNum;
    _max = m_logInformDispData[0].nSuctLogInformList[0].GammaNum;
    _dtNumMax   = m_logInformDispData[0].nSuctLogInformList.count();
    for(int iList = 0; iList < m_logInformDispData.count(); iList ++)
    {
        _dtNumMax = qMax(_dtNumMax, m_logInformDispData[iList].nSuctLogInformList.count());

        QList<QPointF> nTempPointfList;
        for(int jList = 0; jList < m_logInformDispData[iList].nSuctLogInformList.count(); jList ++)
        {
            _min = qMin(_min, m_logInformDispData[iList].nSuctLogInformList[jList].GammaNum);
            _max = qMax(_max, m_logInformDispData[iList].nSuctLogInformList[jList].GammaNum);

            QPointF pointF(jList, m_logInformDispData[iList].nSuctLogInformList[jList].GammaNum);
            nTempPointfList.append(pointF);
        }
        pListPointfList.append(nTempPointfList);
    }
    _min -= 5;
    _max += 5;
}

void OBNLogVisuailzationDisplay::getAzRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF>>& pListPointfList)
{
    _min = m_logInformDispData[0].nSuctLogInformList[0].AzNum;
    _max = m_logInformDispData[0].nSuctLogInformList[0].AzNum;
    _dtNumMax   = m_logInformDispData[0].nSuctLogInformList.count();
    for(int iList = 0; iList < m_logInformDispData.count(); iList ++)
    {
        _dtNumMax = qMax(_dtNumMax, m_logInformDispData[iList].nSuctLogInformList.count());

        QList<QPointF> nTempPointfList;
        for(int jList = 0; jList < m_logInformDispData[iList].nSuctLogInformList.count(); jList ++)
        {
            _min = qMin(_min, m_logInformDispData[iList].nSuctLogInformList[jList].AzNum);
            _max = qMax(_max, m_logInformDispData[iList].nSuctLogInformList[jList].AzNum);

            QPointF pointF(jList, m_logInformDispData[iList].nSuctLogInformList[jList].AzNum);
            nTempPointfList.append(pointF);
        }
        pListPointfList.append(nTempPointfList);
    }
    _min -= 100;
    _max += 100;
}

void OBNLogVisuailzationDisplay::slotPushButtonBrowse()
{
    QString inputDir = QFileDialog::getExistingDirectory(this, tr("选择数据所在目录"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(inputDir.isEmpty())
    {
        return;
    }
    ui->lineEditInputPath->setText(inputDir);

    QDir dirInputPath(inputDir);
    QStringList subDirList = dirInputPath.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    /// ======  通过当前目录获取当前目录下所有log文件
    QDir        nDataPath, nLOGDataPath;
    QString     logFilePath;
    QStringList nDataPathList, tmpFileNameList;
    for(int iList = 0; iList < subDirList.count(); iList ++)
    {
        logFilePath = inputDir + "/" + subDirList[iList];
        /// ======
        nDataPath.setPath(logFilePath);

        nDataPathList = nDataPath.entryList(QDir::NoDotAndDotDot|QDir::Dirs, QDir::Name);
        for(int iPath = 0; iPath < nDataPathList.count(); iPath ++)
        {
            QString dataPathValue = logFilePath+"/"+nDataPathList[iPath];
            nLOGDataPath.setPath(dataPathValue);
            tmpFileNameList = nLOGDataPath.entryList(QDir::NoDotAndDotDot|QDir::Files, QDir::Name);

            for(int iRow = 0; iRow < tmpFileNameList.count(); ++ iRow)
            {
                if(-1 != tmpFileNameList[iRow].indexOf(".log"))
                {
                    QString nRealfileName = dataPathValue + "/" + tmpFileNameList[iRow];
                    m_logFileList.append(nRealfileName);
                    break;
                }
            }
        }
    }
    if(0 == m_logFileList.count())
    {
        QMessageBox::information(this, tr("错误"), tr("当前路径没有可用日志文件，请检查！"), tr("确定"));
        return;
    }

    /// ====== 开辟线程进行读取log日志信息工作
    if(NULL == m_readLogThread)
    {
        m_readLogThread = new OBNReadLoghread(this);
        connect(m_readLogThread, &OBNReadLoghread::signalCurrentReadProgress,         this, &OBNLogVisuailzationDisplay::slotReadLogInformProgress);
        connect(m_readLogThread, &OBNReadLoghread::signalCurrentVisualizationInforms, this, &OBNLogVisuailzationDisplay::slotReadLogInformSuccess);
    }
    m_readLogThread->setCurrentLogFileList(m_logFileList);
    m_readLogThread->start();

    if(NULL == m_readLogProgress)
    {
        m_readLogProgress = new OBNReadLogInformProgress(this);
        connect(m_readLogProgress, &OBNReadLogInformProgress::signalCancenReadLogThread, this, &OBNLogVisuailzationDisplay::slotCancelReadLogThread);
    }
    m_readLogProgress->setRange(0, m_logFileList.count());
    m_readLogProgress->open();
}

/// ====== 点击进度条取消按钮,取消读取日志信息
void OBNLogVisuailzationDisplay::slotCancelReadLogThread()
{
    if(NULL != m_readLogThread)
    {
        m_readLogThread->wait();
    }
}

/// ====== 读取日志文件进度
void OBNLogVisuailzationDisplay::slotReadLogInformProgress(const int& _progressValue)
{
    if(NULL != m_readLogProgress)
    {
        m_readLogProgress->setValue(_progressValue);
    }
}

/// ====== 读取日志信息功能完成槽函数
void OBNLogVisuailzationDisplay::slotReadLogInformSuccess(const QList<SuctLOGDrawInform>& _logDataInformList)
{
    m_logInformDispData = _logDataInformList;

    QStringList   nCurveNameList;
    QList<QColor> nColorList;
    for(int iList = 0; iList < m_logInformDispData.count(); iList ++)
    {
        QString nDeviceName = m_logInformDispData[iList].nNodeName;
        nCurveNameList.append(nDeviceName);

        QColor nTempColor = m_logInformDispData[iList].nLineColor;
        nColorList.append(nTempColor);
    }
    /// ====== 关闭显示的进度条
    m_readLogProgress->close();

    /// ====== 判断当前数据列表是否为空
    if(0 == m_logInformDispData.count())
    {
        QMessageBox::information(this, tr("错误"), tr("读取当前路径下所有Log文件,没有找到可用数据,请检查！"), tr("确定"));
        return;
    }

    /// ====== 显示颜色表格内容
    int tableRowCount = m_logInformDispData.count();
    ui->tableWidgetSetupLineColor->setRowCount(tableRowCount);
    ui->tableWidgetSetupLineColor->setColumnCount(3);
    QStringList n_deviceLineColorHeader;
    n_deviceLineColorHeader << tr("是否显示") << tr("设备编号") << tr("颜色");
    ui->tableWidgetSetupLineColor->setHorizontalHeaderLabels(n_deviceLineColorHeader);
    ui->tableWidgetSetupLineColor->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetSetupLineColor->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int iRow = 0; iRow < m_logInformDispData.count(); iRow ++)
    {
        QCheckBox* nCheckBox = new QCheckBox;
        nCheckBox->setChecked(true);
        connect(nCheckBox, &QCheckBox::stateChanged, this, &OBNLogVisuailzationDisplay::slotLineDisplayStateChange);
        ui->tableWidgetSetupLineColor->setCellWidget(iRow, LINE_ISDISP_COLUMN, nCheckBox);
        /// ======
        ui->tableWidgetSetupLineColor->setItem(iRow, LINE_NAME_COLUMN, new QTableWidgetItem(m_logInformDispData[iRow].nNodeName));
        /// ======
        QLabel * n_labelColor = new QLabel;
        n_labelColor->setStyleSheet("QLabel{background-color:#" + QString::number(m_logInformDispData[iRow].nLineColor.rgba(), 16)+"}");
        ui->tableWidgetSetupLineColor->setCellWidget(iRow, LINE_COLOR_COLUMN, n_labelColor);
    }

    /// ====== 开始进行显示操作
    if(NULL == m_logVisuailzationChart)
    {
        m_logVisuailzationChart = new OBNLogVisuailzationChart("LOG显示");
    }
    m_logVisuailzationChart->setAxis(m_logInformDispData.count(), tr("Time"), 0, 100, 10, tr("Value"), 0, 100, 10, nColorList);

    QVBoxLayout* chartLayout = new QVBoxLayout(ui->widgetLogVisuailzation);
    chartLayout->setContentsMargins(0,0,0,0);
    chartLayout->addWidget(m_logVisuailzationChart);

    /// ====== 设置初始化显示BAT-V
    QTimer::singleShot(1000, this, [=](){
        ui->radioButtonBATV->click();
    });
}

/// ====== 调整表格中数据显示状态
void OBNLogVisuailzationDisplay::slotLineDisplayStateChange(int index)
{
    for(int iRow = 0; iRow < ui->tableWidgetSetupLineColor->rowCount(); iRow ++)
    {
        QCheckBox* nTempCheckBox = (QCheckBox*)(ui->tableWidgetSetupLineColor->cellWidget(iRow, LINE_ISDISP_COLUMN));
        if(nTempCheckBox != sender())
            continue;
        /// ====== 0表示取消显示
        if(0 == index)
        {
            m_logVisuailzationChart->changeLineDisplayState(iRow, false);
        }
        else
        {
            m_logVisuailzationChart->changeLineDisplayState(iRow, true);
        }
        qDebug() << "iRow = " << iRow << "\t index = " << index;
    }
}



