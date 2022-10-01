#include "obnlowercomputerota.h"
#include "ui_obnlowercomputerota.h"

OBNLowerComputerOTA::OBNLowerComputerOTA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNLowerComputerOTA)
{
    ui->setupUi(this);

    connect(ui->pushButtonBrowse,  &QPushButton::clicked, this, &OBNLowerComputerOTA::slotBrowseFunction);
    connect(ui->pushButtonStart,   &QPushButton::clicked, this, &OBNLowerComputerOTA::slotStartFunction);

    /// ======
    QString nQSSInform;
    QFile qssFile(":QSS/defaultStyle.qss");
    if(qssFile.open(QIODevice::ReadOnly))
    {
        nQSSInform = qssFile.readAll();
        qssFile.close();
        this->setStyleSheet(nQSSInform);
    }
}

OBNLowerComputerOTA::~OBNLowerComputerOTA()
{
    delete ui;
}

/// =======选择升级文件
void OBNLowerComputerOTA::slotBrowseFunction(const bool&)
{
}

/// =======开始升级
void OBNLowerComputerOTA::slotStartFunction(const bool&)
{
}

/// ====== 设置当前选中的节点
void OBNLowerComputerOTA::setCurrentOptionalInform(const QVector<HostsState>& pHostsInform)
{
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
        ui->tableWidget->setCellWidget(iRow, 2, nProgressBar);
        ui->tableWidget->setItem(iRow, 3, new QTableWidgetItem(""));
    }
}
