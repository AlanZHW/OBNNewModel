#include "obnlistnodeinform.h"
#include "ui_obnlistnodeinform.h"

OBNListNodeInform::OBNListNodeInform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNListNodeInform)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    QStringList nTableHeaderList;
    nTableHeaderList << tr("选中状态") << tr("连接状态") << tr("机器编号") << tr("机器IP");
    ui->tableWidget->setHorizontalHeaderLabels(nTableHeaderList);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

OBNListNodeInform::~OBNListNodeInform()
{
    delete ui;
}

void OBNListNodeInform::setHostInforms(QVector<HostsState> pHostInforms)
{
    ui->tableWidget->setRowCount(pHostInforms.count());
    for(int iList = 0; iList < pHostInforms.count(); iList ++)
    {
        QCheckBox* nChcckBox = new QCheckBox;
        ui->tableWidget->setCellWidget(iList, 0, nChcckBox);

        QLabel* nLabelHostState = new QLabel;
        nLabelHostState->setStyleSheet("background:#00ff00");
        ui->tableWidget->setCellWidget(iList, 1, nLabelHostState);

        ui->tableWidget->setItem(iList, 2, new QTableWidgetItem(pHostInforms[iList].hostNum));
        ui->tableWidget->setItem(iList, 3, new QTableWidgetItem(pHostInforms[iList].ip));
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
