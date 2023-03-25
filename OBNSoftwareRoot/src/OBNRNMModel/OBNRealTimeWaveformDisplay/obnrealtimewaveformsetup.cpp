#include "obnrealtimewaveformsetup.h"
#include "ui_obnrealtimewaveformsetup.h"

#include <QtSerialPort/QSerialPortInfo>

OBNRealTimeWaveformSetup::OBNRealTimeWaveformSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNRealTimeWaveformSetup)
{
    ui->setupUi(this);

    /// ====== 点击界面"取消"按钮
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &OBNRealTimeWaveformSetup::close);
    /// ====== 点击界面”确定”按钮
    connect(ui->pushButtonOK,     &QPushButton::clicked, this, [=](bool){
        /// ====== 判断节点信息是否可用
        if(0 == ui->tableWidgetRealTimeWaveformSetup->rowCount()){
            QMessageBox::warning(this, tr("错误"), tr("请先设置当前可用的节点信息"), tr("确定"));
            return;
        }
        QList<TCPInform> nTcpInformList;
        for(int iRow = 0; iRow < ui->tableWidgetRealTimeWaveformSetup->rowCount(); iRow ++){
            TCPInform ntempTcpInform;
            ntempTcpInform.ip   = ui->tableWidgetRealTimeWaveformSetup->item(iRow, 0)->text();
            ntempTcpInform.port = ui->tableWidgetRealTimeWaveformSetup->item(iRow, 1)->text().toInt();
            nTcpInformList.append(ntempTcpInform);
        }
        emit signalCurrentTcpInformList(nTcpInformList);
    });

    /// ====== 设置界面表格内容
    QStringList n_tableWidgetHeaders;
    n_tableWidgetHeaders << tr("IP") << tr("端口号");
    ui->tableWidgetRealTimeWaveformSetup->setColumnCount(2);
    ui->tableWidgetRealTimeWaveformSetup->setHorizontalHeaderLabels(n_tableWidgetHeaders);
    ui->tableWidgetRealTimeWaveformSetup->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetRealTimeWaveformSetup->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetRealTimeWaveformSetup->setColumnWidth(0, this->width()/2);
}

OBNRealTimeWaveformSetup::~OBNRealTimeWaveformSetup()
{
    delete ui;
}

void OBNRealTimeWaveformSetup::setCurrentHostInform(const QStringList & _hostNameList)
{
    /// ====== 获取当前可用串口列表
    QStringList comname;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        comname.append(info.portName());
    }
    /// ====== 设置表格内容
    ui->tableWidgetRealTimeWaveformSetup->setRowCount(_hostNameList.count());
    for(int iRow = 0; iRow < _hostNameList.count(); ++ iRow)
    {
        /// ====== 设置IP
        ui->tableWidgetRealTimeWaveformSetup->setItem(iRow, 0, new QTableWidgetItem(_hostNameList[iRow]));
        ui->tableWidgetRealTimeWaveformSetup->setItem(iRow, 1, new QTableWidgetItem("5000"));
    }
}
