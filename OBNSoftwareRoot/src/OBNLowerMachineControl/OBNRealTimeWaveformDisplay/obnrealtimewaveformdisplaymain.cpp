#include "obnrealtimewaveformdisplaymain.h"
#include "ui_obnrealtimewaveformdisplaymain.h"

OBNRealTimeWaveformDisplayMain::OBNRealTimeWaveformDisplayMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OBNRealTimeWaveformDisplayMain)
{
    ui->setupUi(this);
    setWindowTitle(tr("实时波形显示"));
    setWindowState(Qt::WindowMaximized);
}

OBNRealTimeWaveformDisplayMain::~OBNRealTimeWaveformDisplayMain()
{
    delete ui;
}

/// ====== 设置当前可用设备列表
void OBNRealTimeWaveformDisplayMain::setCurrentAvailableHostInformList(const QStringList & pHostInformList)
{
    QScrollArea* mScrollArea = new QScrollArea;
    mScrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    mScrollArea->setWidgetResizable(true);

    QVBoxLayout* nVBoxLayout = new QVBoxLayout;
    nVBoxLayout->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);
    for(int iList = 0; iList < pHostInformList.count(); iList ++)
    {
        OBNRealTimeWaveformDispGroup* nWaveformDisp = new OBNRealTimeWaveformDispGroup();
        nWaveformDisp->setFixedHeight(300);
        nWaveformDisp->setCurrentDeviceID(pHostInformList[iList]);
        nVBoxLayout->addWidget(nWaveformDisp);
    }
    /// ======
    QWidget* widget = new QWidget(this);
    widget->setLayout(nVBoxLayout);
    /// ======
    mScrollArea->setWidget(widget);
    /// ======
    QVBoxLayout* mainHBoxLayout = new QVBoxLayout;
    mainHBoxLayout->addWidget(mScrollArea);

    this->setLayout(mainHBoxLayout);
}

