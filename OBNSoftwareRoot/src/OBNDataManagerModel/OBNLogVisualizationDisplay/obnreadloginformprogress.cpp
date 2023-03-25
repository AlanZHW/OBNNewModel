#include "obnreadloginformprogress.h"
#include "ui_obnreadloginformprogress.h"

OBNReadLogInformProgress::OBNReadLogInformProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNReadLogInformProgress)
{
    ui->setupUi(this);
    connect(ui->pushButtonCabcel, &QPushButton::clicked, this, &OBNReadLogInformProgress::signalCancenReadLogThread);
    connect(ui->pushButtonCabcel, &QPushButton::clicked, this, &OBNReadLogInformProgress::close);
}

OBNReadLogInformProgress::~OBNReadLogInformProgress()
{
    delete ui;
}

/// ======
void OBNReadLogInformProgress::setValue(const int& _value)
{
    ui->progressBar->setValue(_value);
}

/// ======
void OBNReadLogInformProgress::setRange(const int& _min, const int& _max)
{
    ui->progressBar->setRange(_min, _max);
}
