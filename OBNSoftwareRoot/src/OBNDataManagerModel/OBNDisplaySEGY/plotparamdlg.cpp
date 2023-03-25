#include "plotparamdlg.h"
#include "ui_plotparamdlg.h"

//参数控制面板-PlotParamDlg-----------------------------
PlotParamDlg::PlotParamDlg(QCPlotter *plotter,QWidget *parent)
    :QDialog(parent)
    ,ui(new Ui::PlotParamDlg)
    ,m_QCPlotter(plotter)
{
    ui->setupUi(this);
    this->setWindowTitle("QCPlot Option Dialog");
    initDlg();
    ui->tabWidget->setCurrentIndex(0);
}

void PlotParamDlg::initDlg()
{
    //WT/VA----------------------  //图像模式
    QButtonGroup *m_graphModeGrp = new QButtonGroup(this);
    m_graphModeGrp->addButton(ui->WTVArBtn,0);
    ui->WTVArBtn->setChecked(true);
    m_graphModeGrp->addButton(ui->WTrBtn,1);
    m_graphModeGrp->addButton(ui->VArBtn,2);

    //interpolation---------
    QButtonGroup *m_interpolatoinGrp= new QButtonGroup(this);
    m_interpolatoinGrp->addButton(ui->sincRBtn,2);
    ui->sincRBtn->setChecked(true);
    m_interpolatoinGrp->addButton(ui->linearRbtn,1);

    //brush
    ui->positiveCbx->setChecked(true);

    //gain
    ui->gainEdit->setValidator(new QDoubleValidator(0.0,1000.f,6,this));
    ui->gainEdit->setText("1.0");
    //trace inc
    ui->traceIncSpx->setRange(1,1000);
    ui->traceIncSpx->setValue(1);

    //Show header label
    ui->horiAxesLbl->addItems(showHeaderPosList);

    //Axes Min Length
    ui->horiAxesMinLenEdit->setRange(10,1000);
    ui->horiAxesMinLenEdit->setValue(50);
    ui->vertAxesMinLenEdit->setRange(5,1000);
    ui->vertAxesMinLenEdit->setValue(40);

    connect(m_graphModeGrp,SIGNAL(buttonToggled(int,bool)),this,SLOT(slotGraphModeChanged(int,bool)));
    connect(m_interpolatoinGrp,SIGNAL(buttonClicked(int)),this,SLOT(slotInterpolationChanged(int)));

    //start-end Time scope
    ui->startTimeEdit->setValidator(new QIntValidator(0,20000));
    ui->endTimeEdit->setValidator(new QIntValidator(0,20000));
}

void PlotParamDlg::on_positiveCbx_toggled(bool checked)
{
    //四种情况
    if(checked && ui->negativeCbx->isChecked())
        m_QCPlotter->setBrushMode(BrushBoth);
    else if(checked && !ui->negativeCbx->isChecked())
        m_QCPlotter->setBrushMode(BrushPositive);
    else if(!checked && ui->negativeCbx->isChecked())
        m_QCPlotter->setBrushMode(BrushNegative);
    else
    {
        ui->WTrBtn->setChecked(true);
        m_QCPlotter->setBrushMode(NoBrush);
    }
}

void PlotParamDlg::on_negativeCbx_toggled(bool checked)
{
    //四种情况-------------
    if(checked && ui->positiveCbx->isChecked())
        m_QCPlotter->setBrushMode(BrushBoth);
    else if(checked && !ui->positiveCbx->isChecked())
        m_QCPlotter->setBrushMode(BrushNegative);
    else if(!checked && ui->positiveCbx->isChecked())
        m_QCPlotter->setBrushMode(BrushPositive);
    else
    {
        ui->WTrBtn->setChecked(true);
        m_QCPlotter->setBrushMode(NoBrush);
    }
}

void PlotParamDlg::on_ScaleScopeCbx_currentIndexChanged(int index)
{
    if(index == 0)
        m_QCPlotter->setScaleScope(Global);
    else if(index == 1)
        m_QCPlotter->setScaleScope(Trace);
}

void PlotParamDlg::on_gainEdit_textChanged(const QString &arg1)
{
    if(arg1.trimmed().isEmpty())
        return;
    float value = arg1.trimmed().toFloat();
    value = value<0?10e-6:value;
    value = 1.0/value;
    m_QCPlotter->setGain(value);
}

void PlotParamDlg::on_okBtn_clicked()
{
    this->close();
}

void PlotParamDlg::on_horiAxesLbl_currentIndexChanged(const QString &headField)
{
    TraceHead      traceHead;
    char*          pos0 = (char*)&traceHead;
    HeaderFieldPos headerFieldPos;
    headerFieldPos.fieldName = headField;
    if(headField == "Trace No.")
    {
        //道号tracr
        headerFieldPos.pos = (char*)&traceHead.tracr-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "FFID")
    {
        headerFieldPos.pos   = (char*)&traceHead.fldr-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "TraceSeqFFID")
    {
        headerFieldPos.pos = (char*)&traceHead.tracf-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "TraceSeqLine")
    {
        headerFieldPos.pos = (char*)&traceHead.tracl-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "TraceSeqReel")
    {
        headerFieldPos.pos = (char*)&traceHead.tracr-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "CDP")
    {
        headerFieldPos.pos = (char*)&traceHead.cdp-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "OFFSET")
    {
        headerFieldPos.pos = (char*)&traceHead.offset-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "Source Point")
    {
        headerFieldPos.pos = (char*)&traceHead.ep-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "Source X")
    {
        headerFieldPos.pos = (char*)&traceHead.sx-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "Source Y")
    {
        headerFieldPos.pos = (char*)&traceHead.sy-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "Receiver X")
    {
        headerFieldPos.pos = (char*)&traceHead.gx-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "Receiver Y")
    {
        headerFieldPos.pos   = (char*)&traceHead.gy-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "Receiver Line")
    {
        headerFieldPos.pos   = (char*)&traceHead.unass[2]-pos0;
        headerFieldPos.dType = Int_Type;
    }
    else if(headField == "Receiver No.")
    {
        headerFieldPos.pos   = (char*)&traceHead.unass[3]-pos0;
        headerFieldPos.dType = Int_Type;
    }

    m_QCPlotter->setShowHeaderFielPos(headerFieldPos);
}

void PlotParamDlg::on_vertAxesLbl_currentIndexChanged(int index)
{
    if(index == 0)
        m_QCPlotter->setVertScaleType(ScaleTime);
    if(index == 1)
        m_QCPlotter->setVertScaleType(ScaleDepth);
}

void PlotParamDlg::on_horiAxesMinLenEdit_valueChanged(int arg1)
{
    m_QCPlotter->setMinAxesLength(Qt::Horizontal,arg1);
}

void PlotParamDlg::on_vertAxesMinLenEdit_valueChanged(int arg1)
{
    m_QCPlotter->setMinAxesLength(Qt::Vertical,arg1);
}

void PlotParamDlg::on_showHoriGridCbx_clicked(bool checked)
{
    if(checked)
        m_QCPlotter->setGridShow(HorizontalGrid);
    else
        m_QCPlotter->setGridShow(NoneGrid);
}

void PlotParamDlg::on_traceIncSpx_valueChanged(int arg1)
{
    m_QCPlotter->setTraceInc(arg1);
}

void PlotParamDlg::slotGraphModeChanged(int mode,bool checked)
{
    if(checked){
        if(mode == 0){
            m_QCPlotter->setGraphMode(VAWG);
            //保证笔刷选中其一
            if(!ui->positiveCbx->isChecked() && !ui->negativeCbx->isChecked())
            {
                ui->positiveCbx->setChecked(true);
            }
        }
        else if(mode == 1)
            m_QCPlotter->setGraphMode(WG);
        else if(mode == 2){
            m_QCPlotter->setGraphMode(VA);
            //保证笔刷选中其一
            if(!ui->positiveCbx->isChecked() && !ui->negativeCbx->isChecked())
            {
                ui->positiveCbx->setChecked(true);
            }
        }
    }
}

void PlotParamDlg::slotInterpolationChanged(int interType)
{
    m_QCPlotter->setInterType(interType);
}

void PlotParamDlg::on_startTimeEdit_editingFinished()
{
    int startTime = ui->startTimeEdit->text().toInt();
    int endTime   = ui->endTimeEdit->text().toInt();
    if(startTime>endTime)
        return;
    m_QCPlotter->setFixedTimeScope(QPair<int,int>(startTime,endTime));
}

void PlotParamDlg::on_endTimeEdit_editingFinished()
{
    int startTime = ui->startTimeEdit->text().toInt();
    int endTime   = ui->endTimeEdit->text().toInt();
    if(startTime>endTime)
        return;
    m_QCPlotter->setFixedTimeScope(QPair<int,int>(startTime,endTime));
}
