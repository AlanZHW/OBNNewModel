#include "obnlogvisualization.h"
#include "ui_obnlogvisualization.h"

OBNLogVisualization::OBNLogVisualization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OBNLogVisualization)
{
    ui->setupUi(this);

    QStringList mList;
    mList << "A" << "B" << "A" << "B";
    setHostInformList(mList);
}

OBNLogVisualization::~OBNLogVisualization()
{
    delete ui;
}

void OBNLogVisualization::setHostInformList(const QStringList& pFileNameList)
{
    QScrollArea* mScrollArea = new QScrollArea;
    mScrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    mScrollArea->setWidgetResizable(true);

    QVBoxLayout* nVBoxLayout = new QVBoxLayout;
    nVBoxLayout->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);
    for(int iList = 0; iList < pFileNameList.count(); iList ++)
    {
        OBNLogVisualizationDsp* nlogVisualizationDisp = new OBNLogVisualizationDsp(pFileNameList[iList]);
        nVBoxLayout->addWidget(nlogVisualizationDisp);
    }
    QWidget* widget = new QWidget(this);
    widget->setLayout(nVBoxLayout);

    mScrollArea->setWidget(widget);

    QHBoxLayout* mainHBoxLayout = new QHBoxLayout;
    mainHBoxLayout->addWidget(mScrollArea);

    this->setLayout(mainHBoxLayout);
}
