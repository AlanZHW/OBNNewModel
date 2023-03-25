#include "obnlowercumputerota.h"
#include "ui_obnlowercumputerota.h"

OBNLowerCumputerOTA::OBNLowerCumputerOTA(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OBNLowerCumputerOTA)
{
    ui->setupUi(this);

    connect(ui->pushButtonBrowse,  &QPushButton::clicked, this, &OBNLowerCumputerOTA::slotBrowseFunction);
    connect(ui->pushButtonStart,   &QPushButton::clicked, this, &OBNLowerCumputerOTA::slotStartFunction);
}

OBNLowerCumputerOTA::~OBNLowerCumputerOTA()
{
    delete ui;
}

/// =======选择升级文件
void OBNLowerCumputerOTA::slotBrowseFunction(const bool&)
{
    m_fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home");
    if(!m_fileName.isEmpty())
    {
        ui->lineEditInputfName->setText(m_fileName);
    }
}

/// =======开始升级
void OBNLowerCumputerOTA::slotStartFunction(const bool&)
{
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

                QProgressBar* nProgressBar = (QProgressBar*)ui->tableWidget->cellWidget(iHost, 2);
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

void OBNLowerCumputerOTA::slotDataTransferProgress(qint64 _t1, qint64 _t2)
{
}

/// ====== 设置当前选中的节点
void OBNLowerCumputerOTA::setCurrentOptionalInform(const QVector<HostsState>& pHostsInform)
{
    m_hostVertor = pHostsInform;

    /// ======
    ui->tableWidget->clear();
    /// ======
    ui->tableWidget->setRowCount(pHostsInform.count());
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    /// ======
    QStringList nHeaderInformList;
    nHeaderInformList << tr("主机名") << "IP" << tr("进度信息") << tr("状态");
    ui->tableWidget->setHorizontalHeaderLabels(nHeaderInformList);
    /// ======
    for(int iRow = 0; iRow < pHostsInform.count(); iRow ++)
    {
        ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(pHostsInform[iRow].hostNum));
        ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(pHostsInform[iRow].ip));
        QProgressBar* nProgressBar = new QProgressBar;
        nProgressBar->setRange(0, 100);
        ui->tableWidget->setCellWidget(iRow, 2, nProgressBar);
        ui->tableWidget->setItem(iRow, 3, new QTableWidgetItem(""));
    }
}

