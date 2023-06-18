#include "filedetaildlg.h"

//FileDetailDlg------------------
FileDetailDlg::FileDetailDlg(QWidget *parent)
    :QDialog(parent)
{
    this->setWindowTitle(tr("SEGY道头对话框"));
    initDlg();
    this->resize(570,724);
}

void FileDetailDlg::initDlg()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QTabWidget *tabWg = new QTabWidget(this);

    //text header
    m_txtHeaderBrser = new QTextBrowser(this);
    tabWg->insertTab(0, m_txtHeaderBrser,tr("字段名"));

    //binary header
    m_binHeaderTab = new QTableWidget(this);
    m_binHeaderTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_binHeaderTab->setColumnCount(3);
    m_binHeaderTab->setHorizontalHeaderLabels(QStringList()<<tr("字段名") << tr("数据") << tr("说明"));
    m_binHeaderTab->setAlternatingRowColors(true);
    QStringList binaryHeaderInfos;
    getBinaryHeaderInfos(binaryHeaderInfos);
    m_binHeaderTab->setRowCount(binaryHeaderInfos.size()/2);
    for(int i =0;i<binaryHeaderInfos.size()/2;i++)
    {
        m_binHeaderTab->setItem(i,0,new QTableWidgetItem(binaryHeaderInfos[i*2]));
        m_binHeaderTab->setItem(i,2,new QTableWidgetItem(binaryHeaderInfos[i*2+1]));
    }
    m_binHeaderTab->horizontalHeader()->setStretchLastSection(true);
    tabWg->insertTab(1,m_binHeaderTab, tr("字段名"));

    mainLayout->addWidget(tabWg);
    mainLayout->addWidget(new GLine(this));
    QPushButton *okBtn = new QPushButton(tr("&确定"));
    okBtn->setMaximumWidth(44);
    mainLayout->addWidget(okBtn,0,Qt::AlignHCenter);
    this->setLayout(mainLayout);

    connect(okBtn,SIGNAL(clicked()),this,SLOT(close()));
}


void FileDetailDlg::setSegyFileInfo(char *textHeader,BinaryHead *header, SegyInfo*)
{
    //text header------
    m_txtHeaderBrser->setText(QString(textHeader));

    //binary header----
    m_binHeaderTab->setItem(0,1,new QTableWidgetItem(QString::number(header->jobid)));
    m_binHeaderTab->setItem(1,1,new QTableWidgetItem(QString::number(header->lineno)));
    m_binHeaderTab->setItem(2,1,new QTableWidgetItem(QString::number(header->reelno)));
    m_binHeaderTab->setItem(3,1,new QTableWidgetItem(QString::number(header->ntrace)));
    m_binHeaderTab->setItem(4,1,new QTableWidgetItem(QString::number(header->naux)));
    m_binHeaderTab->setItem(5,1,new QTableWidgetItem(QString::number(header->mudt)));
    m_binHeaderTab->setItem(6,1,new QTableWidgetItem(QString::number(header->omudt)));
    m_binHeaderTab->setItem(7,1,new QTableWidgetItem(QString::number(header->nt)));
    m_binHeaderTab->setItem(8,1,new QTableWidgetItem(QString::number(header->ont)));
    m_binHeaderTab->setItem(9,1,new QTableWidgetItem(QString::number(header->samptype)));
    //10-----------------------------------------
    m_binHeaderTab->setItem(10,1,new QTableWidgetItem(QString::number(header->fold)));
    m_binHeaderTab->setItem(11,1,new QTableWidgetItem(QString::number(header->sort)));
    m_binHeaderTab->setItem(12,1,new QTableWidgetItem(QString::number(header->sums)));
    m_binHeaderTab->setItem(13,1,new QTableWidgetItem(QString::number(header->sweep0)));
    m_binHeaderTab->setItem(14,1,new QTableWidgetItem(QString::number(header->sweepf)));
    m_binHeaderTab->setItem(15,1,new QTableWidgetItem(QString::number(header->sweepl)));
    m_binHeaderTab->setItem(16,1,new QTableWidgetItem(QString::number(header->sweept)));
    m_binHeaderTab->setItem(17,1,new QTableWidgetItem(QString::number(header->sweeptr)));
    m_binHeaderTab->setItem(18,1,new QTableWidgetItem(QString::number(header->taper0)));
    m_binHeaderTab->setItem(19,1,new QTableWidgetItem(QString::number(header->taperf)));
    //20-----------------------------------------
    m_binHeaderTab->setItem(20,1,new QTableWidgetItem(QString::number(header->tapert)));
    m_binHeaderTab->setItem(21,1,new QTableWidgetItem(QString::number(header->cor)));
    m_binHeaderTab->setItem(22,1,new QTableWidgetItem(QString::number(header->gain)));
    m_binHeaderTab->setItem(23,1,new QTableWidgetItem(QString::number(header->recov)));
    m_binHeaderTab->setItem(24,1,new QTableWidgetItem(QString::number(header->units)));
    m_binHeaderTab->setItem(25,1,new QTableWidgetItem(QString::number(header->pol)));
    m_binHeaderTab->setItem(26,1,new QTableWidgetItem(QString::number(header->vibpol)));
    //27-----------------------------------------

}

void FileDetailDlg::getBinaryHeaderInfos(QStringList &fieldAndDesc)
{
    fieldAndDesc<<"jobid"<<"Job identification number"
                <<"lineno"<<"Line number"
                <<"reelno"<<"Tape reel number"
                <<"ntrace"<<"number of data traces per record"
                <<"naux"<<"number of auxiliary traces per record"
                <<"mudt"<<"sample interval in micro secs for this reel"
                <<"omudt"<<"sample interval of original field data"
                <<"nt"<<"number of samples per data trace here"
                <<"ont"<<"number of samples per original field data trace"
                <<"samptype"<<"data sample format code"
                //10------------------------
                <<"fold"<<"expected CDP fold"
                <<"sort"<<"Trace sorting code"
                <<"sums"<<"Vertical sum code (how many summed)"
                <<"sweep0"<<"Sweep frequency start, Hz"
                <<"sweepf"<<"Sweep frequency end, Hz"
                <<"sweepl"<<"Sweep length, milliseconds"
                <<"sweept"<<"Sweep type code"
                <<"sweeptr"<<"Trace number of sweep channel"
                <<"taper0"<<"Sweep trace taper length at start, milliseconds"
                <<"taperf"<<"Sweep trace taper length at end, milliseconds"
                //20------------------------
                <<"tapert"<<"Sweep taper type "
                <<"cor"<<"Correlated data traces "
                <<"gain"<<"Binary gain recovered "
                <<"recov"<<"Gain recovered method code"
                <<"units"<<"Measurement system units"
                <<"pol"<<"Impulse signal polarity"
                <<"vibpol"<<"Vibratory polarity code";
}
