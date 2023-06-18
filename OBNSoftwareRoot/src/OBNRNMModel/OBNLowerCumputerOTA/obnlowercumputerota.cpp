#include "obnlowercumputerota.h"
#include "ui_obnlowercumputerota.h"

OBNLowerCumputerOTA::OBNLowerCumputerOTA(QWidget *parent)
    : QDialog(parent),m_obnSeatchHosts(NULL), m_curentNodes(NULL),m_startUpload(false),
      ui(new Ui::OBNLowerCumputerOTA)
{
    ui->setupUi(this);
    setWindowTitle(tr("底层软件升级"));

    m_connectedStyle    = "min-width:12px;min-height:12px;max-width:12px;max-height:12px;border-radius:6px;border:1px solid black;background:green";
    m_disConnectedStyle = "min-width:12px;min-height:12px;max-width:12px;max-height:12px;border-radius:6px;border:1px solid black;background:red";

    /// ====== 选择升级文件&选择工作目录
    connect(ui->pushButtonBrowse,  &QPushButton::clicked, this, [=](bool)
    {
        if(0 == ui->comboBoxOption->currentIndex())
        {
            m_fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home");
            if(!m_fileName.isEmpty())
            {
                ui->lineEditInputfName->setText(m_fileName);
            }
        }
        else
        {
            m_currentWorkPath = QFileDialog::getExistingDirectory(this, tr("选择当前工作目录"), QDir::currentPath());
            if(m_currentWorkPath.isEmpty())
            {
                return;
            }
            ui->lineEditInputfName->setText(m_currentWorkPath);
        }
    });

    /// ====== 开始升级
    connect(ui->pushButtonStart,   &QPushButton::clicked, this, [=](bool){
        /// ======
        if(0 >= ui->tableWidgetOTA->rowCount())
        {
            QMessageBox::information(this, tr("错误"), tr("请点击“筛选可用节点”按钮，获取可用节点列表。"), tr("确定"));
            return;
        }
        /// ======
        if(ui->lineEditInputfName->text().isEmpty())
        {
            QMessageBox::information(this, tr("错误"), tr("请点击“浏览”按钮，选择升级文件。"), tr("确定"));
            return;
        }

        /// ====== 设置按钮不可再次点击
        ui->pushButtonStart->setEnabled(false);

        switch(ui->comboBoxOption->currentIndex())
        {
        case 0:
            m_startUpload = true;
            startChangeConfigFileFunction();
#if 0
            for(int iRow = 0; iRow < m_curentNodeNum; iRow ++)
            {
                QCheckBox* nTempCheckBox =  (QCheckBox*)ui->tableWidgetOTA->cellWidget(iRow, 0);
                if(nTempCheckBox->isChecked())
                {
                    m_curentNodes[iRow].putOTAFileFunction(m_currentFileName, "/home/pi/out.txt");
                }
            }
#endif
            break;
        case 1:
        {
            m_startUpload = true;
            startChangeConfigFileFunction();
        }
            break;
        default:
            break;
        }
    });

    connect(ui->checkBoxSelAll, &QCheckBox::stateChanged, this, [=](int _state){
        /// ====== 设置选中状态
        if(0 != _state)
        {
            int tableRowCount = ui->tableWidgetOTA->rowCount();
            if(0 == tableRowCount)
            {
                QMessageBox::information(this, tr("错误"), tr("请点击“筛选可用节点”按钮，获取可用节点列表。"), tr("确定"));
                ui->checkBoxSelAll->setChecked(false);
                return;
            }
            for(int row = 0; row < tableRowCount; row ++)
            {
                QCheckBox* n_checkBox = (QCheckBox*)ui->tableWidgetOTA->cellWidget(row, 0);
                n_checkBox->setChecked(true);
            }
        }
        else
        {
            int tableRowCount = ui->tableWidgetOTA->rowCount();
            if(0 == tableRowCount)
            {
                QMessageBox::information(this, tr("错误"), tr("请点击“筛选可用节点”按钮，获取可用节点列表。"), tr("确定"));
                ui->checkBoxSelAll->setChecked(false);
                return;
            }
            QCheckBox* n_checkBox = (QCheckBox*)ui->tableWidgetOTA->cellWidget(0, 0);
            n_checkBox->setChecked(false);
        }
    });

    /// ====== 点击筛选可用节点按钮
    connect(ui->pushButtonGetAvailableNodes, &QPushButton::clicked, this, [=](bool){
        if(NULL == m_obnSeatchHosts){
            m_obnSeatchHosts = new ONBRetrieveAvailableNodes(this);
            connect(m_obnSeatchHosts, &ONBRetrieveAvailableNodes::signalCurrentHostsSend, this, [=](QVector<HostsState> hostStateVecotr){
                setCurrentOptionalInform(hostStateVecotr);
            });
        }
        m_obnSeatchHosts->open();
    });

    /// ====== 升级选项修改信号
    connect(ui->comboBoxOption, SIGNAL(currentIndexChanged(const int&)), this, SLOT(slotOTAOptionComboBoxIndexChange(const int&)));
    otaOptionIndexChange(ui->comboBoxOption->currentIndex());

    /// ====== 点击表格触发获取底层内容
    ui->tableWidgetOTA->setSelectionBehavior(QTableWidget::SelectRows);
    ui->tableWidgetOTA->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableWidgetOTA, &QTableWidget::itemClicked, this, [=](QTableWidgetItem *item)
    {
        if(m_currentWorkPath.isEmpty())
        {
            QMessageBox::information(this, tr("错误"), tr("请选择主机工作目录."), tr("确定"));
            ui->checkBoxSelAll->setChecked(false);
            return;
        }
        if(NULL != m_curentNodes)
        {
            m_curentNodes[item->row()].getConfigFile(m_hostVertor[item->row()].hostNum, m_currentWorkPath);
        }
    });
}

OBNLowerCumputerOTA::~OBNLowerCumputerOTA()
{
    if(NULL != m_curentNodes)
    {
        delete [] m_curentNodes;
        m_curentNodes = NULL;
    }
    delete ui;
}

/// ====== 开始启动升级config配置文件 ----- 升级config配置文件流程
void OBNLowerCumputerOTA::startChangeConfigFileFunction()
{
    if(m_currentWorkPath.isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("请选择主机工作目录."), tr("确定"));
        ui->checkBoxSelAll->setChecked(false);
        return;
    }
    m_curentSelectedNodeList.clear();
    for(int iRow = 0; iRow < ui->tableWidgetOTA->rowCount(); iRow ++)
    {
        QCheckBox* nSelNodeCheckBox = (QCheckBox*)ui->tableWidgetOTA->cellWidget(iRow,0);
        if(nSelNodeCheckBox->isChecked())
        {
            int selRowNO = iRow;
            m_curentSelectedNodeList.append(selRowNO);
        }
    }
    if(0 == m_curentSelectedNodeList.count())
    {
        /// ====== 恢复按钮可点击
        ui->pushButtonStart->setEnabled(true);
        QMessageBox::information(this, tr("告警"), tr(""), tr("确定"));
        return;
    }
    /// ====== 开始执行升级操作
    switch(ui->comboBoxOption->currentIndex())
    {
    case 0:
    {
        m_currentFileName = ui->lineEditInputfName->text();
        m_curentNodefName = "/ota.run";
        putUpgradeFilesFunctio(m_currentFileName, m_curentNodefName);
    }
        break;
    case 1:
        getCurentChangeIDAlsoGetConfigFile();
        break;
    default:
        break;
    }
}

/// ====== 上传升级文件
void OBNLowerCumputerOTA::putUpgradeFilesFunctio(const QString& _otaFileName, const QString& _nodefName)
{
    if(0 == m_curentSelectedNodeList.count())
    {
        /// ====== 恢复按钮可点击
        ui->pushButtonStart->setEnabled(true);
        return;
    }
    int nCurrentReadRow = m_curentSelectedNodeList[0];
    m_curentNodes[nCurrentReadRow].putOTAFileFunction(_otaFileName, _nodefName);
}

/// ====== 取一个节点下载config文件
void OBNLowerCumputerOTA::getCurentChangeIDAlsoGetConfigFile()
{
    if(0 == m_curentSelectedNodeList.count())
    {
        /// ====== 恢复按钮可点击
        m_startUpload = false;
        ui->pushButtonStart->setEnabled(true);
        return;
    }
    int nCurrentReadRow = m_curentSelectedNodeList[0];
    /// ======
    m_curentNodes[nCurrentReadRow].getConfigFile(m_hostVertor[nCurrentReadRow].hostNum, m_currentWorkPath);
}

/// ====== 读取文件内容
void OBNLowerCumputerOTA::readCurrentConfigFileFunction(int _row, const QString&)
{
    /// ------ 检索目标文件
    QString nodePath = m_currentWorkPath+Dir_Separator+m_hostVertor[_row].hostNum;

    QDir fileDir(nodePath);
    fileDir.setFilter(QDir::Files);
    QFileInfoList fileInfoList = fileDir.entryInfoList();

    QStringList fileList;
    for(int inf = 0; inf < fileInfoList .count(); inf ++)
    {
        if("lst" == fileInfoList.at(inf).suffix())
        {
            m_curentHostConfigFileName = fileInfoList.at(inf).fileName();
        }
    }
    fileInfoList.clear();

    /// ------ 修改文件名
    QString nNameConfigOld = nodePath + Dir_Separator + m_curentHostConfigFileName;
    QString nNameConfigNew = nodePath + Dir_Separator + m_curentHostConfigFileName + ".download";
    QString nNameConfigUp  = nodePath + Dir_Separator + m_curentHostConfigFileName + ".upload";
    qDebug() << "nNameConfigOld = " << nNameConfigOld;
    qDebug() << "nNameConfigNew = " << nNameConfigNew;
    qDebug() << "nNameConfigUp = " << nNameConfigUp;
    QFile fileRename(nNameConfigOld);
    fileRename.rename(nNameConfigNew);

    /// ------ 读取目标文件内容
    QList<CFGInform> n_curentConfigInform;
    readConfigInformFunction(nNameConfigNew, n_curentConfigInform);

    /// ------ 调用修改文件内容函数
    updateCurrentConfigFileFunction(nNameConfigUp, n_curentConfigInform);

    /// ------ 调用上传文件
    QString nNameConfigFtpName= "/media/pi/OBN/"+m_curentHostConfigFileName;
    qDebug() << "nNameConfigUp = " << nNameConfigUp << "\t nNameConfigFtpName = " << nNameConfigFtpName;
    putCurrentConfigFileFunction(_row, nNameConfigUp, nNameConfigFtpName);
}

/// ====== 读取配置文件内容
void OBNLowerCumputerOTA::readConfigInformFunction(const QString& _configName, QList<CFGInform>& _configInformList)
{
    QFileInfo fileInform(_configName);
    if(!fileInform.exists())
    {
        QMessageBox::information(this, tr("告警"), tr("Config文件不存在,请检查!"), tr("确定"));
        return;
    }

    QFile fileRead(_configName);
    if(!fileRead.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(this, tr("告警"), tr("打开config文件失败,请检查!"), tr("确定"));
        return;
    }

    QTextStream in(&fileRead);
    while(!in.atEnd())
    {
        QString nReadCfgLine = in.readLine().trimmed().replace(QRegExp("[\\s]+"), " ");
        if(-1 == nReadCfgLine.indexOf(":"))
        {
            continue;
        }
        QStringList n_currentDataList = nReadCfgLine.split(":");
        CFGInform tmpCfgInform;
        tmpCfgInform._name = n_currentDataList[0];
        int idx = n_currentDataList[1].indexOf("//");
        if(-1 == idx)
        {
            tmpCfgInform._value = n_currentDataList[1];
        }
        else
        {
            tmpCfgInform._value  = n_currentDataList[1].mid(0, n_currentDataList[1].indexOf(" "));
            tmpCfgInform._explain= n_currentDataList[1].mid(n_currentDataList[1].indexOf(tmpCfgInform._value)+tmpCfgInform._value.length()+1, n_currentDataList[1].length()-1).trimmed();
        }
        _configInformList.append(tmpCfgInform);
    }
    fileRead.close();
}

/// ====== 修改文件内容并存储到磁盘
void OBNLowerCumputerOTA::updateCurrentConfigFileFunction(const QString& _uploadFName, QList<CFGInform>& _configInformList)
{
    /// ====== 修改内容
    for(int iRow = 0; iRow < ui->tableWidgetCfgInform->rowCount(); iRow ++)
    {
        if(ui->tableWidgetCfgInform->item(iRow, 2)->text().isEmpty())
            continue;
        _configInformList[iRow]._name  = ui->tableWidgetCfgInform->item(iRow, 0)->text();
        _configInformList[iRow]._value = ui->tableWidgetCfgInform->item(iRow, 1)->text();
    }

    /// ====== 存储到磁盘
    FILE * m_fileNew = fopen(_uploadFName.toStdString().c_str(), "wb");
    if(NULL == m_fileNew)
    {
        QMessageBox::information(this, tr("告警"), tr("打开主机工作目录文件失败,请检查!"), tr("确定"));
        return;
    }
    for(int iNO = 0; iNO < 64; iNO ++)
    {
        fprintf(m_fileNew, "*");
    }
    fprintf(m_fileNew, "\n");
    for(int iRow = 0; iRow < ui->tableWidgetCfgInform->rowCount(); iRow ++)
    {
        if(_configInformList[iRow]._explain.isEmpty())
        {
            fprintf(m_fileNew, "%-27s:%s\n", _configInformList[iRow]._name.toStdString().c_str(), _configInformList[iRow]._value.toStdString().c_str());
        }
        else
        {
            fprintf(m_fileNew, "%-27s:%s    %s\n", _configInformList[iRow]._name.toStdString().c_str(), _configInformList[iRow]._value.toStdString().c_str(), _configInformList[iRow]._explain.toStdString().c_str());
        }
    }
    fclose(m_fileNew);
}

/// ====== 上传新的配置文件
void OBNLowerCumputerOTA::putCurrentConfigFileFunction(const int _row, const QString& n_uploadfName, const QString& _nodefName)
{
    m_curentNodes[_row].putOTAFileFunction(n_uploadfName, _nodefName);
}

/// ====== 发送升级文件成功
void OBNLowerCumputerOTA::slotPutOTAFileSuccess(int row)
{
    QString nCurentNode = m_hostVertor[row].hostNum;
    switch(ui->comboBoxOption->currentIndex())
    {
    case 0:     ///<上传升级文件成功
        qDebug() << "节点:" << nCurentNode << ",上传配置升级文件";
        m_curentSelectedNodeList.removeAt(0);
        putUpgradeFilesFunctio(m_currentFileName, m_curentNodefName);
        break;
    case 1:     ///<上传配置文件成功
        qDebug() << "节点:" << nCurentNode << ",上传配置文件成功";
        ui->tableWidgetOTA->item(m_curentSelectedNodeList.at(0), 5)->setText("上传配置文件成功");
        m_curentSelectedNodeList.removeAt(0);
        getCurentChangeIDAlsoGetConfigFile();
        break;
    default:
        break;
    }
}


/// ======升级选项修改
void OBNLowerCumputerOTA::otaOptionIndexChange(const int& index)
{
    if(!ui->lineEditInputfName->text().isEmpty())
    {
        ui->lineEditInputfName->setText("");
    }
    switch (index)
    {
    case 0:
    {
        ui->labelInputfName->setText(tr("升级文件"));
        /// ====== 隐藏config文件内容表格
        ui->frame_3->hide();
        /// ======
        if(NULL != m_curentNodes)
        {
            for(int iNode = 0; iNode < m_curentNodeNum; iNode ++)
            {
                m_curentNodes[iNode].setCurrentWorkPath("/media/pi/OBN");
            }
        }
    }
        break;
    case 1:
    {
        ui->labelInputfName->setText(tr("工作目录"));
        /// ====== 显示config文件内容表格
        ui->frame_3->show();
        /// ======
        if(NULL != m_curentNodes)
        {
            for(int iNode = 0; iNode < m_curentNodeNum; iNode ++)
            {
                m_curentNodes[iNode].setCurrentWorkPath("/media/pi/OBN");
            }
        }
    }
        break;
    default:
        return;
    }
}

/// ======
void OBNLowerCumputerOTA::slotOTAOptionComboBoxIndexChange(const int& index)
{
    otaOptionIndexChange(index);
}

/// ====== ftp遇到错误
void OBNLowerCumputerOTA::slotOTAErrorFunction(int row, QString _errorInform)
{
    QString tipsInform = tr("节点") + m_hostVertor[row].ip + tr("接收到的ftp信号:") + _errorInform;
    qDebug() << __LINE__ << "\t tipsInform = " << tipsInform;
}

/// ====== 读取config文件成功
void OBNLowerCumputerOTA::slotOTAGetConfigFileSuccess(int row, const QString& _configfName)
{
    switch (ui->comboBoxOption->currentIndex())
    {
    case 0:
        break;
    case 1:
        if(!m_startUpload)  ///< 描述当前是否已经开始执行升级操作
        {
            initConfigTableInfrom(row, _configfName);
        }
        else
        {
            readCurrentConfigFileFunction(row, _configfName);
        }
        break;
    default:
        break;
    }
}

void OBNLowerCumputerOTA::initConfigTableInfrom(int _row, const QString& _configfName)
{
    QString nodePath = m_currentWorkPath+Dir_Separator+m_hostVertor[_row].hostNum;
    QString nConfigName = nodePath + Dir_Separator + _configfName;
    qDebug() << "_configfName = " << _configfName;

    /// ------ 读取目标文件内容
    QList<CFGInform> n_curentConfigInform;
    readConfigInformFunction(nConfigName, n_curentConfigInform);

    /// ======将配置文件内容显示到表格中
    ui->tableWidgetCfgInform->setRowCount(n_curentConfigInform.count());
    ui->tableWidgetCfgInform->setColumnCount(3);
    ui->tableWidgetCfgInform->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetCfgInform->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList n_curentCfgTableHeader;
    n_curentCfgTableHeader << tr("参数名") << tr("参数值") << tr("说明");
    ui->tableWidgetCfgInform->setHorizontalHeaderLabels(n_curentCfgTableHeader);
    for(int iRow = 0; iRow < n_curentConfigInform.count(); iRow ++)
    {
        ui->tableWidgetCfgInform->setItem(iRow, 0, new QTableWidgetItem(n_curentConfigInform[iRow]._name));
        ui->tableWidgetCfgInform->setItem(iRow, 1, new QTableWidgetItem(n_curentConfigInform[iRow]._value));
        if(n_curentConfigInform[iRow]._explain.isEmpty())
        {
            ui->tableWidgetCfgInform->item(iRow, 1)->setFlags(ui->tableWidgetCfgInform->item(iRow, 1)->flags() & ~Qt::ItemIsEnabled);
        }
        ui->tableWidgetCfgInform->setItem(iRow, 2, new QTableWidgetItem(n_curentConfigInform[iRow]._explain));
        ui->tableWidgetCfgInform->item(iRow, 2)->setFlags(ui->tableWidgetCfgInform->item(iRow, 2)->flags() & ~Qt::ItemIsEnabled);
    }
    n_curentConfigInform.clear();
}

/// ====== 获取升级进度
void OBNLowerCumputerOTA::slotCurrentProgress(int row, int value)
{
    QProgressBar* nProgressBar = (QProgressBar*)ui->tableWidgetOTA->cellWidget(row, 4);
    nProgressBar->setValue(value);
}

/// ====== 设置当前选中的节点
void OBNLowerCumputerOTA::setCurrentOptionalInform(const QVector<HostsState>& pHostsInform)
{
    m_hostVertor = pHostsInform;

    if(NULL != m_curentNodes)
    {
        delete [] m_curentNodes;
        m_curentNodes = NULL;
    }
    m_curentNodeNum=pHostsInform.count();
    m_curentNodes = new OBNOtaNode[pHostsInform.count()];
    for(int iNode = 0; iNode < m_curentNodeNum; iNode ++)
    {
        connect(&m_curentNodes[iNode], &OBNOtaNode::node_signal_error, this, &OBNLowerCumputerOTA::slotOTAErrorFunction);
        connect(&m_curentNodes[iNode], &OBNOtaNode::node_signal_get_config_file_success, this, &OBNLowerCumputerOTA::slotOTAGetConfigFileSuccess);
        connect(&m_curentNodes[iNode], &OBNOtaNode::node_signal_put_ota_file_success, this, &OBNLowerCumputerOTA::slotPutOTAFileSuccess);
        connect(&m_curentNodes[iNode], &OBNOtaNode::node_signal_curent_progress, this, &OBNLowerCumputerOTA::slotCurrentProgress);
    }

    /// ======
    ui->tableWidgetOTA->clear();
    /// ======
    ui->tableWidgetOTA->setRowCount(pHostsInform.count());
    ui->tableWidgetOTA->setColumnCount(6);
    ui->tableWidgetOTA->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    /// ======
    QStringList nHeaderInformList;
    nHeaderInformList << tr("是否选中")<< tr("链接状态") << tr("主机名") << "IP" << tr("进度信息") << tr("状态");
    ui->tableWidgetOTA->setHorizontalHeaderLabels(nHeaderInformList);
    /// ======
    for(int iRow = 0; iRow < pHostsInform.count(); iRow ++)
    {
        QCheckBox* n_checkBox = new QCheckBox;
        connect(n_checkBox, &QCheckBox::stateChanged, this, &OBNLowerCumputerOTA::slotNodeTableCheckBoxStateChange);
        ui->tableWidgetOTA->setCellWidget(iRow, 0, n_checkBox);
        QLabel* m_labelState = new QLabel;
        if(pHostsInform[iRow].state)
        {
            m_labelState->setStyleSheet(m_connectedStyle);
        }
        else
        {
            m_labelState->setStyleSheet(m_disConnectedStyle);
        }
        ui->tableWidgetOTA->setCellWidget(iRow, 1, m_labelState);
        ui->tableWidgetOTA->setItem(iRow, 2, new QTableWidgetItem(pHostsInform[iRow].hostNum));
        ui->tableWidgetOTA->setItem(iRow, 3, new QTableWidgetItem(pHostsInform[iRow].ip));
        QProgressBar* nProgressBar = new QProgressBar;
        nProgressBar->setRange(0, 100);
        ui->tableWidgetOTA->setCellWidget(iRow, 4, nProgressBar);
        ui->tableWidgetOTA->setItem(iRow, 5, new QTableWidgetItem(tr("就绪")));

        /// ====== 设置每个节点的信息
        m_curentNodes[iRow].setFtpServerIp(iRow, pHostsInform[iRow].ip);
    }
}

/// ====== 表格复选按钮状态变化信号
void OBNLowerCumputerOTA::slotNodeTableCheckBoxStateChange(int)
{
    bool nSelectedAll = true;
    for(int iRow = 0; iRow < ui->tableWidgetOTA->rowCount(); iRow ++)
    {
        QCheckBox * checkBoxTable = (QCheckBox*)ui->tableWidgetOTA->cellWidget(iRow,0);
        if(!checkBoxTable->isChecked())
        {
            nSelectedAll = false;
            break;
        }
    }
    ui->checkBoxSelAll->setChecked(nSelectedAll);
}

