#include "obnadjdatalist.h"
#include "ui_obnadjdatalist.h"

OBNADJDataList::OBNADJDataList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNADJDataList)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("数据信息"));
    connect(ui->pushButtonOK,     &QPushButton::clicked, this, &OBNADJDataList::close);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &OBNADJDataList::close);

    /// ====== 设置表格属性
}

OBNADJDataList::~OBNADJDataList()
{
    delete ui;
}

/// ====== 设置当前显示的数据
void OBNADJDataList::setCurrentDataVector(const QList<ADJDispInform>& _adjXDataInform, const QList<ADJDispInform>& _adjYDataInform, const QList<ADJDispInform>& _adjZDataInform)
{
    if(0 == _adjXDataInform.count() ||0 == _adjYDataInform.count() || 0 == _adjZDataInform.count())
    {
        return;
    }
    if(0 == _adjXDataInform[0].adjDataList.count() ||
       0 == _adjYDataInform[0].adjDataList.count() ||
       0 == _adjZDataInform[0].adjDataList.count())
    {
        return;
    }

    QStringList tableHorizonList;
    tableHorizonList << tr("设备编号") << tr("通道") << tr("过零点") << tr("半带宽") << tr("波峰比") << tr("Theta") << tr("Gamma") << tr("Az");
    int n_tableRow    = 3*_adjXDataInform.count();
    int n_tableColumn = tableHorizonList.count();
    qDebug() << "n_tableRow = " << n_tableRow << "\t n_tableColumn = " << n_tableColumn;
    ui->tableWidgetADJInform->setRowCount(n_tableRow);
    ui->tableWidgetADJInform->setColumnCount(n_tableColumn);
    ui->tableWidgetADJInform->setHorizontalHeaderLabels(tableHorizonList);
    ui->tableWidgetADJInform->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetADJInform->setSelectionBehavior(QAbstractItemView::SelectRows);
    for(int iColumn = 0; iColumn < tableHorizonList.count(); iColumn ++)
    {
        ui->tableWidgetADJInform->setColumnWidth(iColumn, this->width()/5);
    }

    int dataListNo = 0;
    for(int iRow = 0; iRow < n_tableRow; iRow += 3)
    {
        ui->tableWidgetADJInform->setItem(iRow, 0, new QTableWidgetItem(_adjXDataInform[dataListNo].adjName));
        ui->tableWidgetADJInform->setItem(iRow, 1, new QTableWidgetItem("X"));
#if 0
        QLabel* n_labelX = new QLabel;
        n_labelX->setText(QString::number(_adjXDataInform[dataListNo].n_zeroCrossNum));
        if(_adjXDataInform[dataListNo].n_zeroCrossNum < 500)
        {
            n_labelX->setStyleSheet("background-color:#FF0000");
        }
        ui->tableWidgetADJInform->setCellWidget(iRow, 2, n_labelX);
#else
        ui->tableWidgetADJInform->setItem(iRow, 2, new QTableWidgetItem(QString::number(_adjXDataInform[dataListNo].n_zeroCrossNum)));
#endif
        ui->tableWidgetADJInform->setItem(iRow, 3, new QTableWidgetItem(QString::number(_adjXDataInform[dataListNo].cycleInform)));
        ui->tableWidgetADJInform->setItem(iRow, 4, new QTableWidgetItem(QString::number(_adjXDataInform[dataListNo].dampingInform)));
        ui->tableWidgetADJInform->setItem(iRow, 5, new QTableWidgetItem(""));
        ui->tableWidgetADJInform->setItem(iRow, 6, new QTableWidgetItem(""));
        ui->tableWidgetADJInform->setItem(iRow, 7, new QTableWidgetItem(""));

        ui->tableWidgetADJInform->setItem(iRow+1, 0, new QTableWidgetItem(_adjYDataInform[dataListNo].adjName));
        ui->tableWidgetADJInform->setItem(iRow+1, 1, new QTableWidgetItem("Y"));
#if 0
        QLabel* n_labelY = new QLabel;
        n_labelY->setText(QString::number(_adjYDataInform[dataListNo].n_zeroCrossNum));
        if(_adjYDataInform[dataListNo].n_zeroCrossNum < 500)
        {
            n_labelY->setStyleSheet("background-color:#FF0000");
        }
        ui->tableWidgetADJInform->setCellWidget(iRow+1, 2, n_labelY);
#else
        ui->tableWidgetADJInform->setItem(iRow+1, 2, new QTableWidgetItem(QString::number(_adjYDataInform[dataListNo].n_zeroCrossNum)));
#endif
        ui->tableWidgetADJInform->setItem(iRow+1, 3, new QTableWidgetItem(QString::number(_adjYDataInform[dataListNo].cycleInform)));
        ui->tableWidgetADJInform->setItem(iRow+1, 4, new QTableWidgetItem(QString::number(_adjYDataInform[dataListNo].dampingInform)));
        ui->tableWidgetADJInform->setItem(iRow+1, 5, new QTableWidgetItem(""));
        ui->tableWidgetADJInform->setItem(iRow+1, 6, new QTableWidgetItem(""));
        ui->tableWidgetADJInform->setItem(iRow+1, 7, new QTableWidgetItem(""));

        ui->tableWidgetADJInform->setItem(iRow+2, 0, new QTableWidgetItem(_adjZDataInform[dataListNo].adjName));
        ui->tableWidgetADJInform->setItem(iRow+2, 1, new QTableWidgetItem("Z"));
#if 0
        QLabel* n_labelZ = new QLabel;
        n_labelZ->setText(QString::number(_adjZDataInform[dataListNo].n_zeroCrossNum));
        if(_adjZDataInform[dataListNo].n_zeroCrossNum < 500)
        {
            n_labelZ->setStyleSheet("background-color:#FF0000");
        }
        ui->tableWidgetADJInform->setCellWidget(iRow+2, 2, n_labelZ);
#else
        ui->tableWidgetADJInform->setItem(iRow+2, 2, new QTableWidgetItem(QString::number(_adjZDataInform[dataListNo].n_zeroCrossNum)));
#endif
        ui->tableWidgetADJInform->setItem(iRow+2, 3, new QTableWidgetItem(QString::number(_adjZDataInform[dataListNo].cycleInform)));
        ui->tableWidgetADJInform->setItem(iRow+2, 4, new QTableWidgetItem(QString::number(_adjZDataInform[dataListNo].dampingInform)));
        ui->tableWidgetADJInform->setItem(iRow+2, 5, new QTableWidgetItem(""));
        ui->tableWidgetADJInform->setItem(iRow+2, 6, new QTableWidgetItem(""));
        ui->tableWidgetADJInform->setItem(iRow+2, 7, new QTableWidgetItem(""));

        dataListNo += 1;
    }
}
