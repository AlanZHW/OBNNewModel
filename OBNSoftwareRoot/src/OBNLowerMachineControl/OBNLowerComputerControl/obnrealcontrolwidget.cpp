#include "obnrealcontrolwidget.h"
#include "ui_obnrealcontrolwidget.h"

OBNRealControlWidget::OBNRealControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNRealControlWidget)
{
    ui->setupUi(this);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &OBNRealControlWidget::slotCurrentTabChange);

    QString nSetTabWidth   = QString("QTabBar::tab{min-width:280px}");
    this->setStyleSheet(nSetTabWidth);
}

OBNRealControlWidget::~OBNRealControlWidget()
{
    delete ui;
}

void OBNRealControlWidget::slotCurrentTabChange(const int & index)
{
    emit signalCurrentTabChange(index);
}

/// ====== 设置全选
void OBNRealControlWidget::selectAllFunction(bool flag)
{
    switch(ui->tabWidget->currentIndex())
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        //ui->tabLogVisualization->selectAllFunction(flag);
        break;
    default:
        return;
    }
}

/// ====== 设置当前选中的节点
void OBNRealControlWidget::setCurrentOptionalInform(const QVector<HostsState>& pHostsInform)
{
//    ui->tabOTA->setCurrentOptionalInform(pHostsInform);
}
