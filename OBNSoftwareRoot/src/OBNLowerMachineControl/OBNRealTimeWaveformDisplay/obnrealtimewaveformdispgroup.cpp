#include "obnrealtimewaveformdispgroup.h"
#include "ui_obnrealtimewaveformdispgroup.h"

OBNRealTimeWaveformDispGroup::OBNRealTimeWaveformDispGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNRealTimeWaveformDispGroup)
{
    ui->setupUi(this);
    /// ====== 初始化显示界面
    initCurrentWidget();
}

OBNRealTimeWaveformDispGroup::~OBNRealTimeWaveformDispGroup()
{
    delete ui;
}

/// ====== 初始化显示界面
void OBNRealTimeWaveformDispGroup::initCurrentWidget()
{
    nChartX = new OBNChart(this, "X");
    nChartX->setAxis(tr("X"), 0, 100, 3, tr("Y"), 0, 100, 2);

    nChartY = new OBNChart(this, "Y");
    nChartY->setAxis(tr("X"), 0, 100, 3, tr("Y"), 0, 100, 2);

    nChartZ = new OBNChart(this, "Z");
    nChartZ->setAxis(tr("X"), 0, 100, 3, tr("Y"), 0, 100, 2);

    nChartH = new OBNChart(this, "H");
    nChartH->setAxis(tr("X"), 0, 100, 3, tr("Y"), 0, 100, 2);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(1);
    mainLayout->addWidget(nChartX);
    mainLayout->addWidget(nChartY);
    mainLayout->addWidget(nChartZ);
    mainLayout->addWidget(nChartH);

    ui->widget->setLayout(mainLayout);
}

/// ====== 设置当前显示数据的设备ID
void OBNRealTimeWaveformDispGroup::setCurrentDeviceID(const QString& pDeviceID)
{
    /// ====== 显示当前链接的设备IP地址
    ui->groupBox->setTitle(pDeviceID + "  ");

    /// ====== 根据传递过来的IP地址,建立Socket链接

}

/// ====== 获取当前X、Y、Z、H相关数据值
void OBNRealTimeWaveformDispGroup::getCurrentWaveformInform()
{
}


