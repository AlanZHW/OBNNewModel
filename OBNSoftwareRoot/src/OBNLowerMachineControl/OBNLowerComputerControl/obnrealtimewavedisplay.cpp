#include "obnrealtimewavedisplay.h"
#include "ui_obnrealtimewavedisplay.h"

OBNRealTimeWaveDisplay::OBNRealTimeWaveDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNRealTimeWaveDisplay)
{
    ui->setupUi(this);
}

OBNRealTimeWaveDisplay::~OBNRealTimeWaveDisplay()
{
    delete ui;
}
