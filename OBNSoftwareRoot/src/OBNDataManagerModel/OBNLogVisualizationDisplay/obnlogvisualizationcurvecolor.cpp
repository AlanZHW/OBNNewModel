#include "obnlogvisualizationcurvecolor.h"
#include "ui_obnlogvisualizationcurvecolor.h"

OBNLogVisualizationCurveColor::OBNLogVisualizationCurveColor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNLogVisualizationCurveColor)
{
    ui->setupUi(this);
    setWindowTitle(tr("设置曲线颜色"));

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);

    QStringList nTableHeaderList;
    nTableHeaderList << tr("设备节点") << tr("颜色");
    ui->tableWidget->setHorizontalHeaderLabels(nTableHeaderList);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->pushButton, &QPushButton::clicked, this, &OBNLogVisualizationCurveColor::close);
}

OBNLogVisualizationCurveColor::~OBNLogVisualizationCurveColor()
{
    delete ui;
}

void OBNLogVisualizationCurveColor::setCurrentColorInformList(const QStringList& pDeviceNameList, const QList<QColor>& pCurveColorList)
{
    ui->tableWidget->setRowCount(pDeviceNameList.count());
    for(int iList = 0; iList < pDeviceNameList.count(); iList ++)
    {
        ui->tableWidget->setItem(iList, 0, new QTableWidgetItem(pDeviceNameList[iList]));
        QLabel* nLabelInform = new QLabel;
        nLabelInform->setStyleSheet("QLabel{background-color:#" + QString::number(pCurveColorList[iList].rgba(), 16)+"}");
        ui->tableWidget->setCellWidget(iList, 1, nLabelInform);
    }
}
