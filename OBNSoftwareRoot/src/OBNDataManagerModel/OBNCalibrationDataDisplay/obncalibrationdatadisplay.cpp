#include "obncalibrationdatadisplay.h"
#include "ui_obncalibrationdatadisplay.h"

OBNCalibrationDataDisplay::OBNCalibrationDataDisplay(QWidget *parent)
    : QDialog(parent) , m_settings(NULL), m_chartXDisplay(NULL), m_chartYDisplay(NULL), m_chartZDisplay(NULL)
    , ui(new Ui::OBNCalibrationDataDisplay)
{
    ui->setupUi(this);
    /// ====== 设置软件默认最大化显示
    setWindowState(Qt::WindowMaximized);
    setWindowTitle(tr("显示标定数据"));

    m_readCalibation = new ReadCalibationData;
    connect(m_readCalibation, &ReadCalibationData::signal_current_adj_data_inform, this, &OBNCalibrationDataDisplay::slotReadAdjFileSuccess);

    m_readDataThread = new QThread;
    m_readCalibation->moveToThread(m_readDataThread);
    m_readDataThread->start();

    connect(this, &OBNCalibrationDataDisplay::signal_read_adj_data, m_readCalibation, &ReadCalibationData::slotReadCalibationDataFunction);

    connect(ui->pushButtonBrowse, &QPushButton::clicked, this, [=](bool){
        QString inputDir = QFileDialog::getExistingDirectory(this, tr("选择数据所在目录"), "/home/datuo/ZHW/Tool/OBNSoftwareRoot/data/ADJ", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(inputDir.isEmpty())
        {
            return;
        }
        ui->lineEditAdjPath->setText(inputDir);
    });

    /// ====== 设置单选按钮组
    ui->radioButtonOBN->setChecked(true);
    ui->radioButtonCDS->setChecked(false);
    connect(ui->radioButtonOBN, &QRadioButton::clicked, this, [=](const bool&){
        ui->radioButtonOBN->setChecked(true);
        ui->radioButtonCDS->setChecked(false);
    });
    connect(ui->radioButtonCDS, &QRadioButton::clicked, this, [=](const bool&){
        ui->radioButtonOBN->setChecked(false);
        ui->radioButtonCDS->setChecked(true);
    });

    /// ====== 显示按钮槽函数
    connect(ui->pushButtonDisplay, &QPushButton::clicked, this, [=](){

        if(ui->lineEditAdjPath->text().isEmpty())
        {
            QMessageBox::information(this, tr("错误"), tr("请先选择ADJ文件路径。"), tr("确定"));
            return;
        }
        QString NodeFilesDir = ui->lineEditAdjPath->text();
        m_adjFileNameList.clear();

        QDir nNodePath(NodeFilesDir);
        QStringList nodeNameList = nNodePath.entryList(QDir::NoDotAndDotDot|QDir::Dirs, QDir::Name);
        for(int iNodeList = 0; iNodeList < nodeNameList.count(); iNodeList ++)
        {
            QString nAdjfilePath = NodeFilesDir + "/" + nodeNameList[iNodeList];
            QDir nADJFileDir(nAdjfilePath);
            QStringList nADJPathFileList = nADJFileDir.entryList(QDir::NoDotAndDotDot|QDir::Files, QDir::Time);
            QString n_curentNodeADJFName;
            n_curentNodeADJFName.clear();
            for(int iFileNO = 0;  iFileNO < nADJPathFileList.count(); iFileNO ++)
            {
                if(-1 != nADJPathFileList[iFileNO].indexOf(".ADJ"))
                {
                    n_curentNodeADJFName = nAdjfilePath + "/"+ nADJPathFileList[iFileNO];
                }
            }
            if(!n_curentNodeADJFName.isEmpty())
                m_adjFileNameList.append(n_curentNodeADJFName);
        }
        if(0 == m_adjFileNameList.count())
        {
            QMessageBox::warning(this, tr("告警"), tr("当前目录下没有ADJ标定数据文件，请检查！"), tr("确定"));
            return;
        }
        /// ====== 获取当前数据模式
        if(ui->radioButtonOBN->isChecked())
        {
            m_curentAdjMode = 0;
        }
        else if(ui->radioButtonCDS->isChecked())
        {
            m_curentAdjMode = 1;
        }
#if 0
        /// ====== 获取当前路径下所有ADJ文件
        QDir adjPathDir(adjFilesDir);
        QStringList adjFileNameList = adjPathDir.entryList(QDir::NoDotAndDotDot|QDir::Files, QDir::Name);
        for(int iList = 0; iList < adjFileNameList.count(); iList ++)
        {
            if(-1 != adjFileNameList[iList].indexOf(".ADJ"))
            {
                QString nRealfileName = adjFilesDir + "/" + adjFileNameList[iList];
                m_adjFileNameList.append(nRealfileName);
            }
        }
        /// ====== 获取当前数据模式
        if(ui->radioButtonOBN->isChecked())
        {
            m_curentAdjMode = 0;
        }
        else if(ui->radioButtonCDS->isChecked())
        {
            m_curentAdjMode = 1;
        }
#endif
        emit signal_read_adj_data(m_curentAdjMode, m_adjFileNameList);
    });

    /// ======
    ui->tableWidgetDataInform->setMaximumHeight(260);
    ui->frameSetup->setMaximumWidth(350);

    /// ====== 双击表格
    connect(ui->tableWidgetLineColor, &QTableWidget::doubleClicked, this, [=](const QModelIndex &index){
        QColorDialog* n_colorDialog = new QColorDialog(m_adjXDataList[index.row()].nLineColor);
        connect(n_colorDialog, &QColorDialog::colorSelected, this, [=](const QColor &color){
            /// ======
            m_adjXDataList[index.row()].nLineColor = color;
            /// ======
            QLabel* labelTableItem = (QLabel*)(ui->tableWidgetLineColor->cellWidget(index.row(), 2));
            labelTableItem->setStyleSheet("QLabel{background-color:#" + QString::number(color.rgba(), 16)+"}");

            /// ======
            m_chartXDisplay->setCurveColor(index.row(), color);
            m_chartYDisplay->setCurveColor(index.row(), color);
            m_chartZDisplay->setCurveColor(index.row(), color);
        });
        n_colorDialog->open();
    });

    /// ====== 设置限定选项输入框仅可以输入INT类型数据
    ui->lineEditZeroErrorRangeColor->setValidator(new QIntValidator(INT_MIN, INT_MAX));
    ui->lineEditFreqRelatErorColor->setValidator(new QIntValidator(INT_MIN, INT_MAX));
    ui->lineEditStdEColor->setValidator(new QIntValidator(INT_MIN, INT_MAX));
    connect(ui->pushButtonApply, &QPushButton::clicked, this, [=](){
        if(ui->lineEditZeroErrorRangeColor->text().isEmpty() || ui->lineEditFreqRelatErorColor->text().isEmpty() || ui->lineEditStdEColor->text().isEmpty())
        {
            QMessageBox::information(this, tr("警告"), tr("限定选项数据信息不全,请检查!"), tr("确定"));
            return;
        }
        if(NULL != m_settings)
        {
            m_zeroerror     = ui->lineEditZeroErrorRangeColor->text().toInt();
            m_freqrelateror = ui->lineEditFreqRelatErorColor->text().toInt();
            m_stderror      = ui->lineEditStdEColor->text().toInt();
            m_settings->setValue("ZERO", m_zeroerror);
            m_settings->setValue("FREQ", m_freqrelateror);
            m_settings->setValue("RSDE", m_stderror);
        }
        /// ====== 改变表格颜色设置
    });
    connect(ui->pushButtonReset, &QPushButton::clicked, this, [=](){
        if(NULL != m_settings)
        {
            m_zeroerror     = m_settings->value("ZERO").toString().toInt();
            m_freqrelateror = m_settings->value("FREQ").toString().toInt();
            m_stderror      = m_settings->value("RSDE").toString().toInt();
            ui->lineEditZeroErrorRangeColor->setText(QString::number(m_zeroerror));
            ui->lineEditFreqRelatErorColor->setText(QString::number(m_freqrelateror));
            ui->lineEditStdEColor->setText(QString::number(m_stderror));
        }
    });
}

void OBNCalibrationDataDisplay::setProjectInfrom(const QString& _projPath, const QString& _projName)
{
    m_curentProjPath = _projPath;
    m_curentProjName = _projName;
    /// ====== 读取限制选项配置文件内容,如果没有则创建配置文件,并输入默认值
    QString LimitedOptionsfName = m_curentProjPath + Dir_Separator + "limitRange.ini";
    qDebug() << "LimitedOptionsfName = " << LimitedOptionsfName;
    QFileInfo limitOptionfInfo(LimitedOptionsfName);
    /// ====== 当文件已存在
    m_settings = new QSettings(LimitedOptionsfName, QSettings::IniFormat);
    m_settings->setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(limitOptionfInfo.exists())
    {
        m_zeroerror     = m_settings->value("ZERO").toString().toInt();
        m_freqrelateror = m_settings->value("FREQ").toString().toInt();
        m_stderror      = m_settings->value("RSDE").toString().toInt();
    }
    else    ///< 当文件不存在
    {
        m_zeroerror     = 5;
        m_freqrelateror = 10;
        m_stderror      = 5;
        m_settings->setValue("ZERO", m_zeroerror);
        m_settings->setValue("FREQ", m_freqrelateror);
        m_settings->setValue("RSDE", m_stderror);
    }
    ui->lineEditZeroErrorRangeColor->setText(QString::number(m_zeroerror));
    ui->lineEditFreqRelatErorColor->setText(QString::number(m_freqrelateror));
    ui->lineEditStdEColor->setText(QString::number(m_stderror));
}

OBNCalibrationDataDisplay::~OBNCalibrationDataDisplay()
{
    if(0 != m_adjXDataList.count())
    {
        for(int iList = 0; iList < m_adjXDataList.count(); iList ++)
            m_adjXDataList[iList].adjDataList.clear();
    }
    if(0 != m_adjYDataList.count())
    {
        for(int iList = 0; iList < m_adjYDataList.count(); iList ++)
            m_adjYDataList[iList].adjDataList.clear();
    }
    if(0 != m_adjZDataList.count())
    {
        for(int iList = 0; iList < m_adjZDataList.count(); iList ++)
            m_adjZDataList[iList].adjDataList.clear();
    }

    if(m_readDataThread->isRunning())
    {
        m_readDataThread->quit();
        m_readDataThread->wait();
    }
    delete ui;
}

/// ====== 读取ADJ文件成功
void OBNCalibrationDataDisplay::slotReadAdjFileSuccess(QVector<ADJDispInform> _AdjXDataList, QVector<ADJDispInform> _AdjYDataList,QVector<ADJDispInform> _AdjZDataList, ADJAllDataInform _addDataInform)
{
    m_adjXDataList = _AdjXDataList;
    m_adjYDataList = _AdjYDataList;
    m_adjZDataList = _AdjZDataList;

    QList<QColor> nColorList;
    for(int iList = 0; iList < m_adjXDataList.count(); iList ++)
    {
        QColor nTempColor = m_adjXDataList[iList].nLineColor;
        nColorList.append(nTempColor);
    }

    /// ====== X
    m_chartXDisplay = new OBNCalibratonDataChart("X");
    m_chartXDisplay->setAxis(m_adjXDataList.count(), tr(""), 0, 100, 10, tr(""), 0, 100, 10, nColorList);
    QHBoxLayout* nchartXLayout = new QHBoxLayout;
    nchartXLayout->setContentsMargins(0,0,0,0);
    nchartXLayout->addWidget(m_chartXDisplay);
    ui->widgetX->setLayout(nchartXLayout);

    /// ====== Y
    m_chartYDisplay = new OBNCalibratonDataChart("Y");
    m_chartYDisplay->setAxis(m_adjYDataList.count(), tr(""), 0, 100, 10, tr(""), 0, 100, 10, nColorList);
    QHBoxLayout* nchartYLayout = new QHBoxLayout;
    nchartYLayout->setContentsMargins(0,0,0,0);
    nchartYLayout->addWidget(m_chartYDisplay);
    ui->widgetY->setLayout(nchartYLayout);

    /// ====== Z
    m_chartZDisplay = new OBNCalibratonDataChart("Z");
    m_chartZDisplay->setAxis(m_adjZDataList.count(), tr(""), 0, 100, 10, tr(""), 0, 100, 10, nColorList);
    QHBoxLayout* nchartZLayout = new QHBoxLayout;
    nchartZLayout->setContentsMargins(0,0,0,0);
    nchartZLayout->addWidget(m_chartZDisplay);
    ui->widgetZ->setLayout(nchartZLayout);

    /// ====== 显示表格内容
    showLineColorTableWidgetFunction(m_adjXDataList);   ///<

    showLineInformTableWidgetFunction(m_adjXDataList, m_adjYDataList, m_adjZDataList, _addDataInform);


    /// ====== 显示数据
    displayADJFileInform();
}

/// ====== 设置数据是否显示
void OBNCalibrationDataDisplay::slotIsDisplayLineFunction(int index)
{
    for(int iTableRow = 0; iTableRow < ui->tableWidgetLineColor->rowCount(); iTableRow ++)
    {
        if(sender() == ui->tableWidgetLineColor->cellWidget(iTableRow, 0))
        {
            if(0 == index)
            {
                m_chartXDisplay->setCurentLienDispState(iTableRow, false);
                m_chartYDisplay->setCurentLienDispState(iTableRow, false);
                m_chartZDisplay->setCurentLienDispState(iTableRow, false);
            }
            else
            {
                m_chartXDisplay->setCurentLienDispState(iTableRow, true);
                m_chartYDisplay->setCurentLienDispState(iTableRow, true);
                m_chartZDisplay->setCurentLienDispState(iTableRow, true);
            }
            break;
        }
    }
}

/// ====== 显示数据颜色设置表格
void OBNCalibrationDataDisplay::showLineColorTableWidgetFunction(const QVector<ADJDispInform>& _AdjX)
{
    QStringList lineColorTableWidgetHeader;
    lineColorTableWidgetHeader << tr("是否显示") << tr("设备节点") << tr("线颜色");

    int n_tableRowCount     = _AdjX.count();
    int n_tableColumnCount  = 3;
    ui->tableWidgetLineColor->setRowCount(n_tableRowCount);
    ui->tableWidgetLineColor->setColumnCount(n_tableColumnCount);
    ui->tableWidgetLineColor->setHorizontalHeaderLabels(lineColorTableWidgetHeader);
    ui->tableWidgetLineColor->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetLineColor->setSelectionBehavior(QAbstractItemView::SelectRows);

    for(int iRow = 0; iRow < _AdjX.count(); iRow ++)
    {
        /// ====== 设置是否显示
        QCheckBox* checkBoxIsDisp = new QCheckBox;
        checkBoxIsDisp->setChecked(true);
        connect(checkBoxIsDisp, &QCheckBox::stateChanged, this, &OBNCalibrationDataDisplay::slotIsDisplayLineFunction);
        ui->tableWidgetLineColor->setCellWidget(iRow, 0, checkBoxIsDisp);

        /// ====== 设置节点名
        ui->tableWidgetLineColor->setItem(iRow, 1, new QTableWidgetItem(_AdjX[iRow].adjName));

        /// ====== 设置显示颜色
        QLabel* labelLine = new QLabel;
        labelLine->setStyleSheet("QLabel{background-color:#" + QString::number(_AdjX[iRow].nLineColor.rgba(), 16)+"}");
        ui->tableWidgetLineColor->setCellWidget(iRow, 2, labelLine);
    }
}

/// ====== 显示数据信息表格内容
void OBNCalibrationDataDisplay::showLineInformTableWidgetFunction(const QVector<ADJDispInform>& _AdjX, const QVector<ADJDispInform>& _AdjY, const QVector<ADJDispInform>& _adjZ, ADJAllDataInform & _allDataInform)
{
    if(ui->radioButtonOBN->isChecked())
    {
        QStringList tableHorizonList;
        tableHorizonList << tr("设备编号") << tr("通道") << tr("过零点") << tr("半带宽") << tr("波峰比") << tr("Theta") << tr("Gamma") << tr("Az");
        int n_tableRow    = 3*_AdjX.count();
        int n_tableColumn = tableHorizonList.count();
        ui->tableWidgetDataInform->setRowCount(n_tableRow);
        ui->tableWidgetDataInform->setColumnCount(n_tableColumn);
        ui->tableWidgetDataInform->setHorizontalHeaderLabels(tableHorizonList);
        ui->tableWidgetDataInform->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidgetDataInform->setSelectionBehavior(QAbstractItemView::SelectRows);
        for(int iColumn = 0; iColumn < tableHorizonList.count(); iColumn ++)
        {
            ui->tableWidgetDataInform->setColumnWidth(iColumn, this->width()/10);
        }
        int dataListNo = 0;
        for(int iRow = 0; iRow < n_tableRow; iRow += 3)
        {
            qDebug() << "iRow = " << iRow;
            /// ======
            ui->tableWidgetDataInform->setItem(iRow, 0, new QTableWidgetItem(_AdjX[dataListNo].adjName));
            ui->tableWidgetDataInform->setItem(iRow, 1, new QTableWidgetItem("X"));
            ui->tableWidgetDataInform->setItem(iRow, 2, new QTableWidgetItem(QString::number(_AdjX[dataListNo].n_zeroCrossNum)));
            ui->tableWidgetDataInform->setItem(iRow, 3, new QTableWidgetItem(QString::number(_AdjX[dataListNo].cycleInform)));
            ui->tableWidgetDataInform->setItem(iRow, 4, new QTableWidgetItem(QString::number(_AdjX[dataListNo].dampingInform)));
            ui->tableWidgetDataInform->setItem(iRow, 5, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow, 6, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow, 7, new QTableWidgetItem(""));
            /// ======
            ui->tableWidgetDataInform->setItem(iRow+1, 0, new QTableWidgetItem(_AdjY[dataListNo].adjName));
            ui->tableWidgetDataInform->setItem(iRow+1, 1, new QTableWidgetItem("Y"));
            ui->tableWidgetDataInform->setItem(iRow+1, 2, new QTableWidgetItem(QString::number(_AdjY[dataListNo].n_zeroCrossNum)));
            ui->tableWidgetDataInform->setItem(iRow+1, 3, new QTableWidgetItem(QString::number(_AdjY[dataListNo].cycleInform)));
            ui->tableWidgetDataInform->setItem(iRow+1, 4, new QTableWidgetItem(QString::number(_AdjY[dataListNo].dampingInform)));
            ui->tableWidgetDataInform->setItem(iRow+1, 5, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow+1, 6, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow+1, 7, new QTableWidgetItem(""));
            /// ======
            ui->tableWidgetDataInform->setItem(iRow+2, 0, new QTableWidgetItem(_AdjY[dataListNo].adjName));
            ui->tableWidgetDataInform->setItem(iRow+2, 1, new QTableWidgetItem("Z"));
            ui->tableWidgetDataInform->setItem(iRow+2, 2, new QTableWidgetItem(QString::number(_adjZ[dataListNo].n_zeroCrossNum)));
            ui->tableWidgetDataInform->setItem(iRow+2, 3, new QTableWidgetItem(QString::number(_adjZ[dataListNo].cycleInform)));
            ui->tableWidgetDataInform->setItem(iRow+2, 4, new QTableWidgetItem(QString::number(_adjZ[dataListNo].dampingInform)));
            ui->tableWidgetDataInform->setItem(iRow+2, 5, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow+2, 6, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow+2, 7, new QTableWidgetItem(""));

            dataListNo += 1;
        }
    }
    else if(ui->radioButtonCDS->isChecked())
    {
        QStringList tableHorizonList;
        tableHorizonList << tr("设备编号") << tr("通道") << tr("过零点")<< tr("阻尼") << tr("相对频率(Hz)") << tr("频率相对误差(%)") << tr("Theta") << tr("Gamma") << tr("Az");
        int n_tableRow    = 3*_AdjX.count()+6;
        int n_tableColumn = tableHorizonList.count();
        ui->tableWidgetDataInform->setRowCount(n_tableRow);
        ui->tableWidgetDataInform->setColumnCount(n_tableColumn);
        ui->tableWidgetDataInform->setHorizontalHeaderLabels(tableHorizonList);
        ui->tableWidgetDataInform->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidgetDataInform->setSelectionBehavior(QAbstractItemView::SelectRows);
        for(int iColumn = 0; iColumn < tableHorizonList.count(); iColumn ++)
        {
            ui->tableWidgetDataInform->setColumnWidth(iColumn, this->width()/10);
        }
        int dataListNo = 0;
        for(int iRow = 0; iRow < 3*_AdjX.count(); iRow += 3)
        {
            /// ======
            ui->tableWidgetDataInform->setItem(iRow, 0, new QTableWidgetItem(_AdjX[dataListNo].adjName));
            ui->tableWidgetDataInform->setItem(iRow, 1, new QTableWidgetItem("X"));
            ui->tableWidgetDataInform->setItem(iRow, 2, new QTableWidgetItem(QString::number(_AdjX[dataListNo].n_zeroCrossNum)));
            ui->tableWidgetDataInform->setItem(iRow, 3, new QTableWidgetItem(QString::number(_AdjX[dataListNo].dampingInform)));
            ui->tableWidgetDataInform->setItem(iRow, 4, new QTableWidgetItem(QString::number(_AdjX[dataListNo].relativeFrequency)));
            ui->tableWidgetDataInform->setItem(iRow, 5, new QTableWidgetItem(QString::number(_AdjY[dataListNo].relativeError)));
            ui->tableWidgetDataInform->setItem(iRow, 6, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow, 7, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow, 8, new QTableWidgetItem(""));
            /// ======
            ui->tableWidgetDataInform->setItem(iRow+1, 0, new QTableWidgetItem(_AdjY[dataListNo].adjName));
            ui->tableWidgetDataInform->setItem(iRow+1, 1, new QTableWidgetItem("Y"));
            ui->tableWidgetDataInform->setItem(iRow+1, 2, new QTableWidgetItem(QString::number(_AdjY[dataListNo].n_zeroCrossNum)));
            ui->tableWidgetDataInform->setItem(iRow+1, 3, new QTableWidgetItem(QString::number(_AdjY[dataListNo].dampingInform)));
            ui->tableWidgetDataInform->setItem(iRow+1, 4, new QTableWidgetItem(QString::number(_AdjY[dataListNo].relativeFrequency)));
            ui->tableWidgetDataInform->setItem(iRow+1, 5, new QTableWidgetItem(QString::number(_AdjY[dataListNo].relativeError)));
            ui->tableWidgetDataInform->setItem(iRow+1, 6, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow+1, 7, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow+1, 8, new QTableWidgetItem(""));
            /// ======
            ui->tableWidgetDataInform->setItem(iRow+2, 0, new QTableWidgetItem(_AdjY[dataListNo].adjName));
            ui->tableWidgetDataInform->setItem(iRow+2, 1, new QTableWidgetItem("Z"));
            ui->tableWidgetDataInform->setItem(iRow+2, 2, new QTableWidgetItem(QString::number(_adjZ[dataListNo].n_zeroCrossNum)));
            ui->tableWidgetDataInform->setItem(iRow+2, 3, new QTableWidgetItem(QString::number(_adjZ[dataListNo].dampingInform)));
            ui->tableWidgetDataInform->setItem(iRow+2, 4, new QTableWidgetItem(QString::number(_adjZ[dataListNo].relativeFrequency)));
            ui->tableWidgetDataInform->setItem(iRow+2, 5, new QTableWidgetItem(QString::number(_adjZ[dataListNo].relativeError)));
            ui->tableWidgetDataInform->setItem(iRow+2, 6, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow+2, 7, new QTableWidgetItem(""));
            ui->tableWidgetDataInform->setItem(iRow+2, 8, new QTableWidgetItem(""));
            dataListNo += 1;
        }
        int n_otherInformRow = _AdjX.count()*3;
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 0, new QTableWidgetItem(tr("X通道均值")));
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 1, new QTableWidgetItem(QString::number(_allDataInform.x_component.averageValue)));
        n_otherInformRow += 1;
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 0, new QTableWidgetItem(tr("X通道相对标准偏差")));
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 1, new QTableWidgetItem(QString::number(_allDataInform.x_component.standardDeviation)));
        n_otherInformRow += 1;
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 0, new QTableWidgetItem(tr("Y通道均值")));
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 1, new QTableWidgetItem(QString::number(_allDataInform.y_component.averageValue)));
        n_otherInformRow += 1;
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 0, new QTableWidgetItem(tr("Y通道相对标准偏差")));
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 1, new QTableWidgetItem(QString::number(_allDataInform.y_component.standardDeviation)));
        n_otherInformRow += 1;
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 0, new QTableWidgetItem(tr("Z通道均值")));
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 1, new QTableWidgetItem(QString::number(_allDataInform.z_component.averageValue)));
        n_otherInformRow += 1;
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 0, new QTableWidgetItem(tr("Z通道相对标准偏差")));
        ui->tableWidgetDataInform->setItem(n_otherInformRow, 1, new QTableWidgetItem(QString::number(_allDataInform.z_component.standardDeviation)));
    }
}

/// ====== 显示数据
void OBNCalibrationDataDisplay::displayADJFileInform()
{
    if(0 == m_adjXDataList.count() || 0 == m_adjYDataList.count() || 0 == m_adjZDataList.count())
    {
        return;
    }

    int   n_dataNumber = 0;
    qreal min = 9999, max = -9999;
    QList<QList<PointInform>> pointXFListInform, pointYFListInform, pointZFListInform;
    getRange(m_adjXDataList, min, max, n_dataNumber, pointXFListInform);
    m_chartXDisplay->setAxisCurrentYName("X");
    m_chartXDisplay->setCurrentDataRange(0, n_dataNumber, min, max);
    m_chartXDisplay->setCurrentLogData(pointXFListInform);

    getRange(m_adjYDataList, min, max, n_dataNumber, pointYFListInform);
    m_chartYDisplay->setAxisCurrentYName("Y");
    m_chartYDisplay->setCurrentDataRange(0, n_dataNumber, min, max);
    m_chartYDisplay->setCurrentLogData(pointYFListInform);

    getRange(m_adjZDataList, min, max, n_dataNumber, pointZFListInform);
    m_chartZDisplay->setAxisCurrentYName("Z");
    m_chartZDisplay->setCurrentDataRange(0, n_dataNumber, min, max);
    m_chartZDisplay->setCurrentLogData(pointZFListInform);

    /// ====== 释放X空间
    for(int iList = 0; iList < pointXFListInform.count(); iList ++)
    {
        pointXFListInform[iList].clear();
    }
    pointXFListInform.clear();
    /// ====== 释放Y空间
    for(int iList = 0; iList < pointYFListInform.count(); iList ++)
    {
        pointYFListInform[iList].clear();
    }
    pointYFListInform.clear();
    /// ====== 释放Z空间
    for(int iList = 0; iList < pointZFListInform.count(); iList ++)
    {
        pointZFListInform[iList].clear();
    }
    pointZFListInform.clear();
}


void OBNCalibrationDataDisplay::getRange(QVector<ADJDispInform> _adjDispInform, qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<PointInform>>& pListPointfList)
{
    _min        = _adjDispInform[0].adjDataList[0].dataNumber;
    _max        = _adjDispInform[0].adjDataList[0].dataNumber;
    _dtNumMax   = _adjDispInform[0].adjDataList.count();
    for(int iList = 0; iList < _adjDispInform.count(); iList ++)
    {
        _dtNumMax   = qMax(_dtNumMax, _adjDispInform[iList].adjDataList.count());

        QList<PointInform> nPointListOfLine;
        for(int jList = 0; jList < _adjDispInform[iList].adjDataList.count(); jList ++)
        {
            _min = qMin(_min, _adjDispInform[iList].adjDataList[jList].dataNumber);
            _max = qMax(_max, _adjDispInform[iList].adjDataList[jList].dataNumber);

            PointInform nPointInform;
            nPointInform.isZeroCorss = _adjDispInform[iList].adjDataList[jList].isZeroCorss;
            nPointInform.nPointInfom.setX(jList);
            nPointInform.nPointInfom.setY(_adjDispInform[iList].adjDataList[jList].dataNumber);
            nPointListOfLine.append(nPointInform);
        }
        pListPointfList.append(nPointListOfLine);
    }
    _min -= 1000;
    _max += 1000;
}










