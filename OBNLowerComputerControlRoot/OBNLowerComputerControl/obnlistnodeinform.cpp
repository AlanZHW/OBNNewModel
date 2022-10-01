#include "obnlistnodeinform.h"
#include "ui_obnlistnodeinform.h"

OBNListNodeInform::OBNListNodeInform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNListNodeInform)
{
    ui->setupUi(this);
}

OBNListNodeInform::~OBNListNodeInform()
{
    delete ui;
}

/// ======设置当前所有的主机信息
void OBNListNodeInform::setHostInforms(const QVector<HostsState> & pHostInforms)
{
    ui->tableWidget->clear();
    /// ======
    ui->tableWidget->setColumnCount(4);
    QStringList nTableHeaderList;
    nTableHeaderList << tr("选中状态") << tr("连接状态") << tr("机器编号") << tr("机器IP");
    ui->tableWidget->setHorizontalHeaderLabels(nTableHeaderList);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowCount(pHostInforms.count());

    for(int iList = 0; iList < pHostInforms.count(); iList ++)
    {
        QCheckBox* nChcckBox = new QCheckBox;
//        connect(nChcckBox, &QCheckBox::stateChanged, this, &OBNListNodeInform::slotCheckBoxStateChange);
        connect(nChcckBox, &QCheckBox::clicked, this, &OBNListNodeInform::slotCheckBoxStateChange);
        ui->tableWidget->setCellWidget(iList, 0, nChcckBox);

        QLabel* nLabelHostState = new QLabel;
        nLabelHostState->setStyleSheet("background:#00ff00");
        ui->tableWidget->setCellWidget(iList, 1, nLabelHostState);

        ui->tableWidget->setItem(iList, 2, new QTableWidgetItem(pHostInforms[iList].hostNum));
        ui->tableWidget->setItem(iList, 3, new QTableWidgetItem(pHostInforms[iList].ip));
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

/// ====== 复选按钮状态改变触发信号
void OBNListNodeInform::OBNListNodeInform::slotCheckBoxStateChange(const int&)
{
//    QObject* nObjWidget = sender();
//    for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
//    {
//        QCheckBox* nChcckBox = (QCheckBox*)(ui->tableWidget->cellWidget(iRow, 0));
//        if(nObjWidget == nChcckBox)
//        {
//        }
//    }
    mInformHosts.clear();
    /// ======
    for(int iList = 0; iList < ui->tableWidget->rowCount(); iList ++)
    {
        QCheckBox* nChcckBox = (QCheckBox*)(ui->tableWidget->cellWidget(iList, 0));
        if(nChcckBox->isChecked())
        {
            HostsState nTempHostInfo;
            nTempHostInfo.state = true;
            nTempHostInfo.hostNum=ui->tableWidget->item(iList, 2)->text().trimmed();
            nTempHostInfo.ip    = ui->tableWidget->item(iList, 3)->text().trimmed();
            mInformHosts.append(nTempHostInfo);
        }
    }
    /// ====== 发送当前选中节点列表
    emit signalOptionalHosts(mInformHosts);

}

/// ======设置当全可通信的主机信息
void OBNListNodeInform::selectAllFunction(bool nSelState)
{
    int rowCount = ui->tableWidget->rowCount();
    if(0 >= rowCount)
    {
        return;
    }
    mInformHosts.clear();
    /// ======
    for(int iList = 0; iList < rowCount; iList ++)
    {
        QCheckBox* nChcckBox = (QCheckBox*)(ui->tableWidget->cellWidget(iList, 0));
        if(nSelState)
        {
            nChcckBox->setCheckState(Qt::Checked);

            HostsState nTempHostInfo;
            nTempHostInfo.state = true;
            nTempHostInfo.hostNum=ui->tableWidget->item(iList, 2)->text().trimmed();
            nTempHostInfo.ip    = ui->tableWidget->item(iList, 3)->text().trimmed();
            mInformHosts.append(nTempHostInfo);
        }
        else
        {
            nChcckBox->setCheckState(Qt::Unchecked);
        }
    }
    /// ====== 发送当前选中节点列表
    emit signalOptionalHosts(mInformHosts);
}























