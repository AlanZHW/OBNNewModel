#include "obneditporjectinterface.h"
#include "ui_obneditporjectinterface.h"

OBNEditPorjectInterface::OBNEditPorjectInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNEditPorjectInterface)
{
    ui->setupUi(this);
}

OBNEditPorjectInterface::~OBNEditPorjectInterface()
{
    delete ui;
}
