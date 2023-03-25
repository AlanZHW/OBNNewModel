#include "obnlmgrarealistwidget.h"
#include "ui_obnlmgrarealistwidget.h"

OBNLMGRAreaListWidget::OBNLMGRAreaListWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OBNLMGRAreaListWidget)
{
    ui->setupUi(this);

    /// ======
    ui->tableWidget->setColumnCount(1);

    QStringList nTableHeaderList;
    nTableHeaderList << tr("Area名称");
    ui->tableWidget->setHorizontalHeaderLabels(nTableHeaderList);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &OBNLMGRAreaListWidget::close);
    connect(ui->pushButtonOK,     &QPushButton::clicked, this, &OBNLMGRAreaListWidget::slotSelectArea);
}

OBNLMGRAreaListWidget::~OBNLMGRAreaListWidget()
{
    delete ui;
}

void OBNLMGRAreaListWidget::setProjectInform(const QString& _projectPath, const QString& _projectName)
{
    m_projInform.ProjectPath = _projectPath;
    m_projInform.ProjectName = _projectName;

    /// ======
    initTableWidget();
}

void OBNLMGRAreaListWidget::initTableWidget()
{
    QStringList areaNameList;
    if(Area::getAreaNames(m_projInform, areaNameList))
    {
        int areaNum = areaNameList.count();
        ui->tableWidget->setRowCount(areaNum);
        for(int iRow = 0; iRow < areaNameList.count(); iRow ++)
        {
            ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(areaNameList[iRow]));
        }
    }
}

void OBNLMGRAreaListWidget::slotSelectArea(const bool&)
{
    if(0 == ui->tableWidget->rowCount())
    {
        QMessageBox::information(this, tr("错误"), tr("没有有效的Area,请检查"), tr("确定"));
        return;
    }
    QString nCurrentIdxName = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();
    qDebug() << "nCurrentIdxName = " << nCurrentIdxName;
    emit signalCurrentAreaName(nCurrentIdxName);
}

