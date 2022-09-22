#include "obnwelcomemodel.h"
#include "ui_obnwelcomemodel.h"

OBNWelcomeModel::OBNWelcomeModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OBNWelcomeModel)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->buttonEnterTheSystem, &QPushButton::clicked, this, &OBNWelcomeModel::slotEnterTheSystem);

    QString nQSSInform;
    QFile qssFile(":QSS/dialog.qss");
    if(qssFile.open(QIODevice::ReadOnly))
    {
        nQSSInform = qssFile.readAll();
        qssFile.close();
        this->setStyleSheet(nQSSInform);
    }
}

OBNWelcomeModel::~OBNWelcomeModel()
{
    delete ui;
}

void OBNWelcomeModel::slotEnterTheSystem()
{
    OBNLowerComputerControl* m_obnLowerComputerControl = new OBNLowerComputerControl;
    m_obnLowerComputerControl->show();
    this->close();
}
