#include "obncalibrationlinecolorwidget.h"
#include "ui_obncalibrationlinecolorwidget.h"

OBNCalibrationLineColorWidget::OBNCalibrationLineColorWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNCalibrationLineColorWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

OBNCalibrationLineColorWidget::~OBNCalibrationLineColorWidget()
{
    delete ui;
}

void OBNCalibrationLineColorWidget::setADJDataInform()
{
}
