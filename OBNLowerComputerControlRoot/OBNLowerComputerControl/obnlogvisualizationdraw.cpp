#include "obnlogvisualizationdraw.h"
#include "ui_obnlogvisualizationdraw.h"

OBNLogVisualizationDraw::OBNLogVisualizationDraw(QWidget *parent) :
    QWidget(parent),isDrawBAT_V(false), isDrawT(false), isDrawP(false),
    isDrawTheta(false), isDrawGamma(false), isDrawAz(false),
    ui(new Ui::OBNLogVisualizationDraw)
{
    ui->setupUi(this);
}

OBNLogVisualizationDraw::~OBNLogVisualizationDraw()
{
    delete ui;
}

void OBNLogVisualizationDraw::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int iDrawDataNum = m_suctLOGInform->count();
    if(0 == iDrawDataNum){
        return;
    }
    int   n_width   = this->width();
    int   n_height  = this->height();
    float n_minData = 999999.9;
    float n_maxData =-999999.9;

    /// ====== 获取当前需要显示的数据最大值和最小值
    isDrawBAT_V = true;
    isDrawT     = true;
    isDrawP     = true;
    isDrawTheta = true;
    isDrawGamma = true;
    isDrawAz    = true;
    if(isDrawBAT_V)
    {
        for(int iList = 0; iList < iDrawDataNum; iList ++)
        {
            n_minData = min(n_minData, m_suctLOGInform->at(iList).batF);
            n_maxData = max(n_maxData, m_suctLOGInform->at(iList).batF);
        }
    }
    if(isDrawT)
    {
        for(int iList = 0; iList < iDrawDataNum; iList ++)
        {
            n_minData = min(n_minData, m_suctLOGInform->at(iList).TNum);
            n_maxData = max(n_maxData, m_suctLOGInform->at(iList).TNum);
        }
    }
    if(isDrawP)
    {
        for(int iList = 0; iList < iDrawDataNum; iList ++)
        {
            n_minData = min(n_minData, m_suctLOGInform->at(iList).PNum);
            n_maxData = max(n_maxData, m_suctLOGInform->at(iList).PNum);
        }
    }
    if(isDrawTheta)
    {
        for(int iList = 0; iList < iDrawDataNum; iList ++)
        {
            n_minData = min(n_minData, m_suctLOGInform->at(iList).ThetaNum);
            n_maxData = max(n_maxData, m_suctLOGInform->at(iList).ThetaNum);
        }
    }
    if(isDrawGamma)
    {
        for(int iList = 0; iList < iDrawDataNum; iList ++)
        {
            n_minData = min(n_minData, m_suctLOGInform->at(iList).GammaNum);
            n_maxData = max(n_maxData, m_suctLOGInform->at(iList).GammaNum);
        }
    }
    if(isDrawAz)
    {
        for(int iList = 0; iList < iDrawDataNum; iList ++)
        {
            n_minData = min(n_minData, m_suctLOGInform->at(iList).AzNum);
            n_maxData = max(n_maxData, m_suctLOGInform->at(iList).AzNum);
        }
    }
    if(n_maxData <= 10)
    {
        n_maxData += 0.3;
        n_minData -= 0.3;
    }
    if(n_maxData <= 100 && n_maxData > 10)
    {
        n_maxData += 5;
        n_minData -= 5;
    }
    if(n_maxData <= 1000 && n_maxData > 100)
    {
        n_maxData += 50;
        n_minData -= 50;
    }
    if(n_maxData <= 10000 && n_maxData > 1000)
    {
        n_maxData += 500;
        n_minData -= 500;
    }

    float originY = n_minData + (n_maxData-n_minData)/2.0;
    int   n_dtDisp= (n_width-10)/iDrawDataNum;


    QPainter nPainter;
    nPainter.begin(this);

    QPen nLinePen(Qt::black,   1, Qt::DotLine,   Qt::RoundCap, Qt::RoundJoin);
    QPen nLinePenDT(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    nPainter.setPen(nLinePen);

    nPainter.drawLine(QPointF(0, n_height/4),   QPointF(n_width, n_height/4));
    nPainter.drawLine(QPointF(0, n_height/2),   QPointF(n_width, n_height/2));
    nPainter.drawLine(QPointF(0, n_height/4*3), QPointF(n_width, n_height/4*3));


    nPainter.drawLine(QPointF(10,0),            QPointF(10, n_height));
    nPainter.drawLine(QPointF(n_width/2+10,0),  QPointF(n_width/2+10, n_height));

    nPainter.drawText(QPointF(0, n_height),   QString("%1").arg(n_maxData, 0, 'f', 2));
    nPainter.drawText(QPointF(0, n_height/2), QString("%1").arg(originY, 0, 'f', 2));
    nPainter.drawText(QPointF(0, 10),         QString("%1").arg(n_minData, 0, 'f', 2));


    qDebug() << "n_width = " << n_width << "\t n_height = " << n_height << "n_minData = " << n_minData << "\t n_maxData = " << n_maxData;

    nPainter.setPen(nLinePenDT);
    if(isDrawBAT_V)
    {
        QPointF leftPoint(10, ((m_suctLOGInform->at(0).batF-n_minData)*n_height)/(n_maxData-n_minData));
        for(int iList = 1; iList < m_suctLOGInform->count(); iList ++)
        {
            QPointF RightPoint(10+iList*n_dtDisp, ((m_suctLOGInform->at(iList).batF-n_minData)*n_height)/(n_maxData-n_minData));
            nPainter.drawLine(leftPoint, RightPoint);
            leftPoint = RightPoint;
        }
    }
    if(isDrawT)
    {
        QPointF leftPoint(10, ((m_suctLOGInform->at(0).TNum-n_minData)*n_height)/(n_maxData-n_minData));
        for(int iList = 1; iList < m_suctLOGInform->count(); iList ++)
        {
            QPointF RightPoint(10+iList*n_dtDisp, ((m_suctLOGInform->at(iList).TNum-n_minData)*n_height)/(n_maxData-n_minData));
            nPainter.drawLine(leftPoint, RightPoint);
            leftPoint = RightPoint;
        }
    }
    if(isDrawP)
    {
        QPointF leftPoint(10, ((m_suctLOGInform->at(0).PNum-n_minData)*n_height)/(n_maxData-n_minData));
        for(int iList = 1; iList < m_suctLOGInform->count(); iList ++)
        {
            QPointF RightPoint(10+iList*n_dtDisp, ((m_suctLOGInform->at(iList).PNum-n_minData)*n_height)/(n_maxData-n_minData));
            nPainter.drawLine(leftPoint, RightPoint);
            leftPoint = RightPoint;
        }
    }
    if(isDrawTheta)
    {
        QPointF leftPoint(10, ((m_suctLOGInform->at(0).ThetaNum-n_minData)*n_height)/(n_maxData-n_minData));
        for(int iList = 1; iList < m_suctLOGInform->count(); iList ++)
        {
            QPointF RightPoint(10+iList*n_dtDisp, ((m_suctLOGInform->at(iList).ThetaNum-n_minData)*n_height)/(n_maxData-n_minData));
            nPainter.drawLine(leftPoint, RightPoint);
            leftPoint = RightPoint;
        }
    }
    if(isDrawGamma)
    {
        QPointF leftPoint(10, ((m_suctLOGInform->at(0).GammaNum-n_minData)*n_height)/(n_maxData-n_minData));
        for(int iList = 1; iList < m_suctLOGInform->count(); iList ++)
        {
            QPointF RightPoint(10+iList*n_dtDisp, ((m_suctLOGInform->at(iList).GammaNum-n_minData)*n_height)/(n_maxData-n_minData));
            nPainter.drawLine(leftPoint, RightPoint);
            leftPoint = RightPoint;
        }
    }
    if(isDrawAz)
    {
        QPointF leftPoint(10, ((m_suctLOGInform->at(0).AzNum-n_minData)*n_height)/(n_maxData-n_minData));
        for(int iList = 1; iList < m_suctLOGInform->count(); iList ++)
        {
            QPointF RightPoint(10+iList*n_dtDisp, ((m_suctLOGInform->at(iList).AzNum-n_minData)*n_height)/(n_maxData-n_minData));
            nPainter.drawLine(leftPoint, RightPoint);
            leftPoint = RightPoint;
        }
    }
    nPainter.end();
}

/// ======设置是否显示电池电压
void OBNLogVisualizationDraw::setDrawBAT_V(bool state)
{
    isDrawBAT_V = state;
    this->update();
}
/// ======设置是否显示温度
void OBNLogVisualizationDraw::setDrawT(bool state)
{
    isDrawT = state;
    this->update();
}
/// ======设置是否显示舱压
void OBNLogVisualizationDraw::setDrawP(bool state)
{
    isDrawP = state;
    this->update();
}
/// ======设置是否显示俯仰角
void OBNLogVisualizationDraw::setDrawTheta(bool state)
{
    isDrawTheta = state;
    this->update();
}
/// ======设置是否显示翻滚角
void OBNLogVisualizationDraw::setDrawGamma(bool state)
{
    isDrawGamma = state;
    this->update();
}
/// ======设置是否显示方位角
void OBNLogVisualizationDraw::setDrawAz(bool state)
{
    isDrawAz = state;
    this->update();
}

/// ====== 设置当前画图所需要的数据
void OBNLogVisualizationDraw::setCurrentDrawDataInform(QList<SuctLOGInform>* pSuctLogInform)
{
    m_suctLOGInform = pSuctLogInform;
    this->update();
}
