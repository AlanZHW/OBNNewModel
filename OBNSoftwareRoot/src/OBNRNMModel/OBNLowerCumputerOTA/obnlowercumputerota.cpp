#include "obnlowercumputerota.h"
#include "ui_obnlowercumputerota.h"

OBNLowerCumputerOTA::OBNLowerCumputerOTA(QWidget *parent)
    : QDialog(parent),m_obnSeatchHosts(NULL),
      ui(new Ui::OBNLowerCumputerOTA)
{
    ui->setupUi(this);
    setWindowTitle(tr("底层软件升级"));

    /// ====== 选择升级文件
    connect(ui->pushButtonBrowse,  &QPushButton::clicked, this, [=](bool){
        m_fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home");
        if(!m_fileName.isEmpty())
        {
            ui->lineEditInputfName->setText(m_fileName);
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
        putCurrentOTAFile();
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
    connect(ui->tableWidgetOTA, &QTableWidget::itemClicked, this, [=](QTableWidgetItem *item){
    });

//    /// ====== 设置软件风格
//    QString nQSSInform;
//    QFile qssFile(":qss/obnlowercumputerota.qss");
//    if(qssFile.open(QIODevice::ReadOnly))
//    {
//        nQSSInform = qssFile.readAll();
//        qssFile.close();
//        this->setStyleSheet(nQSSInform);
//    }
}

OBNLowerCumputerOTA::~OBNLowerCumputerOTA()
{
    delete ui;
}

/// ======升级选项修改
void OBNLowerCumputerOTA::otaOptionIndexChange(const int& index)
{
    switch (index)
    {
    case 0:
        ui->tableWidgetCfgInform->hide();
        break;
    case 1:
        ui->tableWidgetCfgInform->show();
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

/// ====== 发送OTA升级文件给远端服务器
void OBNLowerCumputerOTA::putCurrentOTAFile()
{
    QFile file(m_fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        for(int iHost = 0; iHost < m_hostVertor.count(); iHost ++)
        {
            QFtp* nFtp = new QFtp;
            connect(nFtp, &QFtp::dataTransferProgress, this, [=, &nFtp](qint64 readBytes, qint64 totalBytes){
                auto percent = (qreal)readBytes/totalBytes;
                int  nprogess= (int)(percent*100);

                QProgressBar* nProgressBar = (QProgressBar*)ui->tableWidgetOTA->cellWidget(iHost, 2);
                nProgressBar->setValue(nprogess);
                if(1 == percent)
                {
                    /// ====== 设置进度为100
                    nProgressBar->setValue(100);
                    nFtp->disconnect();
                    nFtp->close();
                }
                });
            nFtp->connectToHost(m_hostVertor[iHost].ip, 21);
            nFtp->login(FTP_USER_NAME, FTP_USER_PASSWORD);
            nFtp->put(&file, "a.txt");
        }
        file.close();
    }
}

/// ====== 设置当前选中的节点
void OBNLowerCumputerOTA::setCurrentOptionalInform(const QVector<HostsState>& pHostsInform)
{
    m_hostVertor = pHostsInform;

    /// ======
    ui->tableWidgetOTA->clear();
    /// ======
    ui->tableWidgetOTA->setRowCount(pHostsInform.count());
    ui->tableWidgetOTA->setColumnCount(4);
    ui->tableWidgetOTA->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    /// ======
    QStringList nHeaderInformList;
    nHeaderInformList << tr("主机名") << "IP" << tr("进度信息") << tr("状态");
    ui->tableWidgetOTA->setHorizontalHeaderLabels(nHeaderInformList);
    /// ======
    for(int iRow = 0; iRow < pHostsInform.count(); iRow ++)
    {
        ui->tableWidgetOTA->setItem(iRow, 0, new QTableWidgetItem(pHostsInform[iRow].hostNum));
        ui->tableWidgetOTA->setItem(iRow, 1, new QTableWidgetItem(pHostsInform[iRow].ip));
        QProgressBar* nProgressBar = new QProgressBar;
        nProgressBar->setRange(0, 100);
        ui->tableWidgetOTA->setCellWidget(iRow, 2, nProgressBar);
        ui->tableWidgetOTA->setItem(iRow, 3, new QTableWidgetItem(""));
    }
}

