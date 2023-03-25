#include "gatherrecord.h"

GatherRecord::GatherRecord(QWidget *parent)
    :QDialog(parent)
{
    this->setWindowTitle("Read Gather");

    initDlg();
    this->resize(276,84);
}

void GatherRecord::initDlg()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    m_readLabel  = new QLabel("Read Gather()");
    m_gatherSpx  = new QSpinBox;
    QHBoxLayout *horiLayout = new QHBoxLayout;
    horiLayout->addWidget(m_readLabel);
    horiLayout->addWidget(m_gatherSpx);

    QPushButton *okBtn     = new QPushButton(tr("&Ok"));
    QPushButton *closeBtn = new QPushButton(tr("&Close"));

    QHBoxLayout *horiLayout1 = new QHBoxLayout;
    horiLayout1->addWidget(okBtn,0,Qt::AlignHCenter);
    horiLayout1->addWidget(closeBtn,0,Qt::AlignHCenter);

    connect(okBtn,SIGNAL(clicked()),this,SLOT(slotOkClicked()));
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(slotCloseClicked()));

    mainLayout->addLayout(horiLayout);
    mainLayout->addLayout(horiLayout1);
    this->setLayout(mainLayout);
}

void GatherRecord::setGatherInfo(const int &totalTraces,const int &maxTraces,const int &startTrace)
{
    if(totalTraces<1){
        QMessageBox::warning(this,"warning","Read no trace.");
        return;
    }
    //计算总的道集数
    m_gatherNum = ceil(float(startTrace)/float(maxTraces))
            + ceil(float(totalTraces-startTrace)/float(maxTraces));

    m_readLabel->setText(QString("Read Gather(%1~%2)").arg(1)
                         .arg(m_gatherNum));

    m_CurrentGather = ceil(float(startTrace)/float(maxTraces))+1;
    m_gatherSpx->setRange(1,m_gatherNum);
    m_gatherSpx->setValue(m_CurrentGather);

    emit signalReadGather(m_CurrentGather);
}

void GatherRecord::readNextGather()
{
    if(m_CurrentGather<m_gatherNum)
    {
        m_CurrentGather++;
        m_gatherSpx->setValue(m_CurrentGather);

        emit signalReadGather(m_CurrentGather);
    }
}

void GatherRecord::readPrevGather()
{
    if(m_CurrentGather>1)
    {
        m_CurrentGather--;
        m_gatherSpx->setValue(m_CurrentGather);
        emit signalReadGather(m_CurrentGather);
    }
}

void GatherRecord::slotOkClicked()
{
    int gatherNo = m_gatherSpx->value();
    m_CurrentGather = gatherNo;

    emit signalReadGather(m_CurrentGather);
}

void GatherRecord::slotCloseClicked()
{
    this->close();
}
