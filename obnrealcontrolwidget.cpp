#include "obnrealcontrolwidget.h"
#include "ui_obnrealcontrolwidget.h"

OBNRealControlWidget::OBNRealControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNRealControlWidget)
{
    ui->setupUi(this);

    QString nSetTabWidth   = QString("QTabBar::tab{min-width:300px}");
    this->setStyleSheet(nSetTabWidth);
}

OBNRealControlWidget::~OBNRealControlWidget()
{
    delete ui;
}
