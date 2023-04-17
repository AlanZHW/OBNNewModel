#include "obncalibratondatachart.h"


OBNCalibratonDataChart::OBNCalibratonDataChart(const QString & pName, QWidget *parent)
    : QWidget(parent), series(NULL), seriesZero(NULL), isDisplayLineInform(false)
{
    setParent(parent);

    m_valueLabel = new QLabel;

    /// ======
    qchart = new QChart;
    qchart->setTitle(pName);

    /// ======
    chartview= new QChartView(qchart);
    chartview->setRenderHint(QPainter::Antialiasing);//防止图形走样

    /// ======
    axisX  = new QValueAxis(this);
    axisY  = new QValueAxis(this);

    /// ======
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(chartview);
    setLayout(layout);
}

OBNCalibratonDataChart::~OBNCalibratonDataChart()
{
    if(NULL != series)
    {
        series->clear();
        delete [] series;
    }
    if(NULL != seriesZero)
    {
        seriesZero->clear();
        delete [] seriesZero;
    }
}

void OBNCalibratonDataChart::setChartName(const QString& pChartName)
{
    if(NULL != qchart)
    {
        qchart->setTitle(pChartName);
    }
}

void OBNCalibratonDataChart::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(Qt::LeftButton == event->button())
    {
        emit signalRightButtonDoubleClick();
    }
}

void OBNCalibratonDataChart::setAxis(int curveNum,
                                       QString _xname, qreal _xmin, qreal _xmax, int _xtickc,
                                       QString _yname, qreal _ymin, qreal _ymax, int _ytickc,
                                       QList<QColor> _colorList)
{
    for(int iList = 0; iList < _colorList.count(); iList ++)
    {
        QColor nLineColor = _colorList[iList];
        m_colorList.append(nLineColor);
    }

    axisX->setRange(_xmin, _xmax);    //设置范围
    axisX->setLabelFormat("%d");      //设置刻度的格式(%u:无符号十进制整数,%s:字符串,%c:一个字符,%d:有符号十进制整数,%e:浮点数、e-记数法,%f:浮点数、十进制记数法,%s:字符串)
    axisX->setGridLineVisible(true);  //网格线可见
    axisX->setTickCount(_xtickc);     //设置多少个大格
    axisX->setMinorTickCount(1);      //设置每个大格里面小刻度线的数目
    axisX->setTitleText(_xname);      //设置描述

    axisY->setRange(_ymin, _ymax);
    axisY->setLabelFormat("%d");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(_ytickc);
    axisY->setMinorTickCount(1);
    axisY->setTitleText(_yname);

    qchart->addAxis(axisX, Qt::AlignBottom); //下：Qt::AlignBottom  上：Qt::AlignTop
    qchart->addAxis(axisY, Qt::AlignLeft);   //左：Qt::AlignLeft    右：Qt::AlignRight
    qchart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线动画模式
    qchart->legend()->hide(); //隐藏图例

    /// ======
    series      = new QSplineSeries[curveNum];
    seriesZero  = new QScatterSeries[curveNum];
    for(int iList = 0; iList < curveNum; iList ++)
    {
        series[iList].setPen(QPen(_colorList[iList], 1, Qt::SolidLine));
        series[iList].setUseOpenGL(true);
        qchart->addSeries(&(series[iList]));//输入数据
        series[iList].attachAxis(axisX);
        series[iList].attachAxis(axisY);

        seriesZero[iList].setMarkerShape(QScatterSeries::MarkerShapeCircle);//圆形的点
        seriesZero[iList].setBrush(QBrush(_colorList[iList]));
        seriesZero[iList].setMarkerSize(8);//点大小
        qchart->addSeries(&(seriesZero[iList]));
        seriesZero[iList].attachAxis(axisX);
        seriesZero[iList].attachAxis(axisY);
    }
}

/// ====== 重新设置当前坐标系
void OBNCalibratonDataChart::setCurrentDataRange(qreal _xmin, qreal _xmax, qreal _ymin, qreal _ymax)
{
    qchart->axisX()->setRange(_xmin, _xmax);
    qchart->axisY()->setRange(_ymin, _ymax);
}

void OBNCalibratonDataChart::setAxisCurrentYName(const QString pYName)
{
    qchart->axisY()->setTitleText(pYName);
}

void OBNCalibratonDataChart::setAxisCurrentXName(const QString pXName)
{
    qchart->axisX()->setTitleText(pXName);
}

/// ====== 设置曲线颜色
void OBNCalibratonDataChart::setCurveColor(int iCurveNO, QColor pColor)
{
    series[iCurveNO].setColor(pColor);
}

/// ====== 设置是否显示当前线
void OBNCalibratonDataChart::setCurentLienDispState(int iCurveNO, bool _displayState)
{
    if(_displayState)
    {
        series[iCurveNO].clear();
        for(int iList = 0; iList < m_pointInformsList[iCurveNO].count(); iList ++)
        {
            series[iCurveNO].append(m_pointInformsList[iCurveNO][iList].nPointInfom);
        }
    }
    else
    {
        series[iCurveNO].clear();
    }
}

/// ====== 设置显示当前选中曲线
void OBNCalibratonDataChart::setCurrentLogData(QList<QList<PointInform>> plistPointfList)
{
    m_pointInformsList = plistPointfList;

    /// ====== 先将当前显示的曲线清除
    for(int iSeries = 0; iSeries < m_pointInformsList.count(); iSeries ++)
    {
        series[iSeries].clear();
    }
    /// ======
    for(int iList = 0; iList < m_pointInformsList.count(); iList ++)
    {
        /// ======
        for(int jList = 0; jList < m_pointInformsList[iList].count(); jList ++)
        {
            series[iList].append(plistPointfList[iList][jList].nPointInfom);
            if(m_pointInformsList[iList][jList].isZeroCorss)
            {
                if(500 > jList)
                {
                    seriesZero[iList].setBrush(QBrush(Qt::red));
                }
                else
                {
                    seriesZero[iList].setBrush(QBrush(m_colorList[iList]));
                }
                seriesZero[iList].append(m_pointInformsList[iList][jList].nPointInfom);
            }
        }
    }
}





















