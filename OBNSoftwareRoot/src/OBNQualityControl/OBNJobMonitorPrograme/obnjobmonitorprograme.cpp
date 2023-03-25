#include "obnjobmonitorprograme.h"
#include "ui_obnjobmonitorprograme.h"

OBNJobMonitorPrograme::OBNJobMonitorPrograme(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OBNJobMonitorPrograme)
{
    ui->setupUi(this);
    ui->mainSplitter->setStretchFactor(1,1);

    m_jobManager = new JobManager(this);
    m_jobManager->setProjInfo(m_projInfo);
    m_jobManager->init(ui->jobList,ui->logBrowser);
}

OBNJobMonitorPrograme::~OBNJobMonitorPrograme()
{
    delete ui;
}


void OBNJobMonitorPrograme::on_autoRefreshCbx_clicked(bool checked)
{
    ui->spinBox->setEnabled(checked);
    m_jobManager->setAutoRefreshEnable(checked);
}

void OBNJobMonitorPrograme::on_spinBox_valueChanged(int arg1)
{
    m_jobManager->setLogRefreshInterval(arg1);
}

void OBNJobMonitorPrograme::on_refreshBtn_clicked()
{
    m_jobManager->refreshLog();
}
