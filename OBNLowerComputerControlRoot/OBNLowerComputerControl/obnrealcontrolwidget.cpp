#include "obnrealcontrolwidget.h"
#include "ui_obnrealcontrolwidget.h"

OBNRealControlWidget::OBNRealControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNRealControlWidget)
{
    ui->setupUi(this);
    QString nSetTabWidth   = QString("QTabBar::tab{min-width:280px}");
    this->setStyleSheet(nSetTabWidth);
}

OBNRealControlWidget::~OBNRealControlWidget()
{
    delete ui;
}

/// ====== 设置当前选中的节点
void OBNRealControlWidget::setCurrentOptionalInform(const QVector<HostsState>& pHostsInform)
{
    ui->tabOTA->setCurrentOptionalInform(pHostsInform);
}
