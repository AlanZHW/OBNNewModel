#include "obnlogvisualizationdsp.h"
#include "ui_obnlogvisualizationdsp.h"

OBNLogVisualizationDsp::OBNLogVisualizationDsp(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNLogVisualizationDsp)
{
    ui->setupUi(this);
    ui->label->setText(name);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    QStringList nTableHeaderList;
    nTableHeaderList << tr("是否选中") << tr("曲线名") << tr("颜色");
    ui->tableWidget->setHorizontalHeaderLabels(nTableHeaderList);

    QStringList nColumnNameList;
    nColumnNameList << "BAT_V" << "T" << "P" << "Theta" << "Gamma" << "Az";

    QStringList nColorInformList;
    nColorInformList << "#FF0000" << "#00FF00" << "#0000FF" << "#000000" << "#0F0F0F" << "#F00F00";

    ui->tableWidget->setRowCount(nColumnNameList.count());
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int iList = 0; iList < nColumnNameList.count(); iList ++)
    {
        QCheckBox* nCheckBox = new QCheckBox;
        connect(nCheckBox, &QCheckBox::stateChanged, this, &OBNLogVisualizationDsp::slotTableWidgetCheckBoxStateChange);
        ui->tableWidget->setCellWidget(iList, 0, nCheckBox);
        ui->tableWidget->setItem(iList, 1, new QTableWidgetItem(nColumnNameList[iList]));

        QLabel* labelColor = new QLabel;
        labelColor->setFixedSize(60, 25);
        labelColor->setStyleSheet("background:"+nColorInformList[iList]);
        ui->tableWidget->setCellWidget(iList, 2, labelColor);
    }

    connect(ui->checkBox, &QCheckBox::stateChanged, this, &OBNLogVisualizationDsp::slotSelAllCheckBoxStateChange);

    readLogFileFunction("E:\\BaiduNetdiskDownload\\20220822-DT\\20220822\\C0002_220817\\C0002228.log");
}

OBNLogVisualizationDsp::~OBNLogVisualizationDsp()
{
    delete ui;
}

/// ====== 响应全选按钮状态变化
void OBNLogVisualizationDsp::slotSelAllCheckBoxStateChange(const int&)
{
    if(ui->checkBox->isChecked())
    {
        for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
        {
            QCheckBox* nChcckBox = (QCheckBox*)(ui->tableWidget->cellWidget(iRow, 0));
            nChcckBox->setChecked(true);
        }
    }
    else
    {
        for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
        {
            QCheckBox* nChcckBox = (QCheckBox*)(ui->tableWidget->cellWidget(iRow, 0));
            nChcckBox->setChecked(false);
        }
    }
}

/// ====== 响应表格复选按钮状态变化
void OBNLogVisualizationDsp::slotTableWidgetCheckBoxStateChange(const int&)
{
#if 0
    for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
    {
        QCheckBox* nChcckBox = (QCheckBox*)(ui->tableWidget->cellWidget(iRow, 0));
        if(nChcckBox->isChecked())
        {
            qDebug() << "iRow = " << iRow;
        }
    }
#else
    QObject* nObjWidget = sender();
    for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
    {
        QCheckBox* nChcckBox = (QCheckBox*)(ui->tableWidget->cellWidget(iRow, 0));
        if(nObjWidget == nChcckBox)
        {
        }
    }
#endif
}
//void OBNLogVisualizationDsp::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event);
//    QPainter nPainter;
//    nPainter.begin(ui->widget);
//    nPainter.drawLine(QPointF(0,0), QPointF(100,100));
//    nPainter.end();
//}

/// ====== 读取log文件
void OBNLogVisualizationDsp::readLogFileFunction(const QString& fileName)
{
    QFile openFile(fileName);
    if(!openFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "open file error";
        return ;
    }
    /// ======
    nLOGInformList.clear();
    /// ======
    QTextStream in(&openFile);
    /// ======
    QString ReadLine = in.readLine();
    QStringList nReadLineList;
    QStringList nScreenDataList;
    while(!in.atEnd())
    {
        /// ======读取一行数据
        ReadLine      = in.readLine().trimmed();
        /// ======通过","进行截取数据
        nReadLineList = ReadLine.split(",");

        /// ======
        SuctLOGInform n_suctLOGInform;
        /// ======筛选当前数据
        for(int iLst = 0; iLst < nReadLineList.count(); iLst ++)
        {
            if(-1 != nReadLineList[iLst].indexOf("BAT_V"))
            {
                nScreenDataList = nReadLineList[iLst].split("=");
                n_suctLOGInform.batF = nScreenDataList[1].toFloat();
            }
            if(-1 != nReadLineList[iLst].indexOf("T"))
            {
                nScreenDataList = nReadLineList[iLst].split("=");
                n_suctLOGInform.TNum = nScreenDataList[1].toFloat();
            }
            if(-1 != nReadLineList[iLst].indexOf("P"))
            {
                nScreenDataList = nReadLineList[iLst].split("=");
                n_suctLOGInform.PNum = nScreenDataList[1].toFloat();
            }
            if(-1 != nReadLineList[iLst].indexOf("Theta"))
            {
                nScreenDataList = nReadLineList[iLst].split("=");
                n_suctLOGInform.ThetaNum = nScreenDataList[1].toFloat();
            }
            if(-1 != nReadLineList[iLst].indexOf("Gamma"))
            {
                nScreenDataList = nReadLineList[iLst].split("=");
                n_suctLOGInform.GammaNum = nScreenDataList[1].toFloat();
            }
            if(-1 != nReadLineList[iLst].indexOf("Az"))
            {
                nScreenDataList = nReadLineList[iLst].split("=");
                n_suctLOGInform.AzNum = nScreenDataList[1].toFloat();
            }
        }
        nLOGInformList.append(n_suctLOGInform);
    }

#if 0
    for(int iList = 0; iList < nLOGInformList.count(); iList ++)
    {
        qDebug() << "batF = " << nLOGInformList[iList].batF
                 << "TNum = " << nLOGInformList[iList].TNum
                 << "PNum = " << nLOGInformList[iList].PNum
                 << "ThetaNum = " << nLOGInformList[iList].ThetaNum
                 << "GammaNum = " << nLOGInformList[iList].GammaNum
                 << "AzNum = " << nLOGInformList[iList].AzNum;
    }
#endif
    ui->widget->setCurrentDrawDataInform(&nLOGInformList);
}




































