#include "obndisplaysegy.h"
#include "ui_obndisplaysegy.h"

OBNDisplaySEGY::OBNDisplaySEGY(QWidget *parent)
    : QMainWindow(parent), m_headers(NULL), m_data(NULL), m_gatherRecord(NULL)
    , ui(new Ui::OBNDisplaySEGY)
{
    ui->setupUi(this);
    setWindowTitle(tr("显示SEGY数据"));

    m_menuInform = new MenuManager(this);
    m_menuInform->createMenu(this, ui->menubar);

    m_toolInfrom = new ToolManager(this);
    m_toolInfrom->createTools(this, ui->displaySEGYToolBar);

    m_QCPlotter = new QCPlotter;
    m_QCPlotter->Initial(ui->statusbar, &m_gatherInfo);
    m_paramDlg = new PlotParamDlg(m_QCPlotter,this);

    QVBoxLayout *plotterLayout = new QVBoxLayout;
    plotterLayout->addWidget(m_QCPlotter);
    ui->widget->setLayout(plotterLayout);

    m_gatherRecord = new GatherRecord(this);
    connect(m_gatherRecord, &GatherRecord::signalReadGather, this, &OBNDisplaySEGY::slotReadGather);
}

OBNDisplaySEGY::~OBNDisplaySEGY()
{
    delete ui;
}

void OBNDisplaySEGY::setCurrentSEGYFileHandles(QList<SegyFileHandle*> _pSegyFileHandle, int _maxTrace, int _startTrace, OpenFilesType _openFilesType)
{
    /// ======
    m_FileHandles = _pSegyFileHandle;
    /// ======
    m_startTrace = _startTrace - _maxTrace * ceil(float(_startTrace)/float(_maxTrace));

    m_maxShowTraces = _maxTrace;

    if(NULL == m_data)
    {
        delete [] m_data;
        m_data = NULL;
    }
    if(NULL == m_headers)
    {
        delete[] m_headers;
        m_headers = NULL;
    }

    /// ====== 申请内存
    m_headers = new TraceHead[m_maxShowTraces*m_FileHandles.size()];
    if(NULL == m_headers)
    {
        return;
    }

    /// ====== 数据类型，采样点数，道数
    int ns      = m_FileHandles[0]->binaryhead->nt;
    int dtype   = m_FileHandles[0]->binaryhead->samptype;
    int byte_num= 4;
    if(dtype == 3)
    {
        byte_num= 2;
    }
    m_data = new char[m_maxShowTraces*ns*byte_num*m_FileHandles.size()];
    if(NULL == m_data)
    {
    }

    m_gatherInfo.gatherName = m_FileHandles[0]->fileName.mid(m_FileHandles[0]->fileName.lastIndexOf("/")+1);
    m_gatherInfo.Ns         = ns;
    m_gatherInfo.DType      = dtype;
    m_gatherInfo.NTraces    = 0;
    m_gatherInfo.sampleInterval =  m_FileHandles[0]->segyInfo->sampleInterval;

    m_gatherRecord->setGatherInfo(m_FileHandles[0]->segyInfo->traces, _maxTrace, _startTrace);
    m_QCPlotter->setComponents(_openFilesType);
}

void OBNDisplaySEGY::slotReadGather(const int& gatherNo)
{
    long long startTrace =  m_startTrace+m_maxShowTraces*(gatherNo-1);
    startTrace = startTrace<0?0:startTrace;
    //读取数据---------------------
    int ok = -1;
    long long readTraces   = 0;
    long long total_traces = 0;
    int ns = m_gatherInfo.Ns;
    int bypes = 4;
    for(int i=0;i<m_FileHandles.size();i++)
    {
        gobs_read_segy_func(m_FileHandles[i]->openTrace,startTrace,m_maxShowTraces,
                            m_headers+total_traces,m_data+total_traces*ns*bypes,
                            &readTraces,
                            &ok);
        if(ok != 0)
        {
            QMessageBox::critical(this,"Error",QString("Read Gather %1 Failed,ok=%2.").arg(gatherNo).arg(ok));
            return;
        }
        if(readTraces == 0)
        {
            QMessageBox::critical(this,"Error",QString("Gather %1 has no trace.").arg(gatherNo));
            return;
        }
        total_traces += readTraces;
    }

    /// ====== 设置切换道集选项使能
    int gatherNum = m_gatherRecord->gatherNumer();
    QList<QAction *> toolActions = ui->displaySEGYToolBar->actions();
    if(gatherNo == gatherNum)
    {
        toolActions[3]->setEnabled(false);
    }
    else
    {
        toolActions[3]->setEnabled(true);
    }
    if(gatherNo == 1)
    {
        toolActions[2]->setEnabled(false);
    }
    else
    {
        toolActions[2]->setEnabled(true);
    }
    m_gatherInfo.NTraces = total_traces;
    m_gatherInfo.gatherNum = m_gatherRecord->gatherNumer();
    m_gatherInfo.gatherNo  = m_gatherRecord->gatherNo();

    /// ====== 读取数据后，设置图像数据，更新显示
    m_QCPlotter->setData(m_headers,m_data);
}

/// ====== FILE-Menu
void OBNDisplaySEGY::slotAbout()
{
}

void OBNDisplaySEGY::slotExit()
{
    this->close();
}

void OBNDisplaySEGY::slotDisplayOption()
{
    if(NULL != m_paramDlg)
    {
        m_paramDlg->show();
    }
}

/// ======
void OBNDisplaySEGY::slotPreviousGather()
{
    if(m_FileHandles.size()>0)
        m_gatherRecord->readPrevGather();
}

void OBNDisplaySEGY::slotNextGather()
{
    if(m_FileHandles.size()>0)
        m_gatherRecord->readNextGather();
}

void OBNDisplaySEGY::slotMoveToGather()
{
    if(m_FileHandles.size()>0)
        m_gatherRecord->show();
}

void OBNDisplaySEGY::slotZoomIn(const bool &enable)
{
    if(enable && NULL != m_QCPlotter)
    {
        m_QCPlotter->setMouseFunction(MF_ZOOM);
    }
    else
    {
        m_QCPlotter->setMouseFunction(MF_NOTHING);
    }
}

void OBNDisplaySEGY::slotZoomOut()
{
    if(NULL != m_QCPlotter)
    {
        m_QCPlotter->zoomOut();
    }
}

void OBNDisplaySEGY::slotTraceInform(const bool& enable)
{
    if(enable && NULL != m_QCPlotter)
    {
        m_QCPlotter->setMouseFunction(MF_ANALYSE);
    }
    else
    {
        m_QCPlotter->setMouseFunction(MF_NOTHING);
    }
}
