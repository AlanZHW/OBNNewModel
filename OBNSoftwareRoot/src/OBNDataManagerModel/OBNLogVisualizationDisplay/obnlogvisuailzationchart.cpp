#include "obnlogvisuailzationchart.h"

OBNLogVisuailzationChart::OBNLogVisuailzationChart(const QString& pNameInform, QWidget *parent)
    : QWidget(parent), series(NULL)
{
    setParent(parent);

    /// ======
    qchart = new QChart;
    qchart->setTitle(pNameInform);

    /// ======
    chartview= new QChartView(qchart);
    chartview->setRenderHint(QPainter::Antialiasing);//防止图形走样

    /// ======
    axisX  = new QValueAxis(this);
    axisY  = new QValueAxis(this);

    /// ======
    layout = new QHBoxLayout(this);
    layout->addWidget(chartview);
    setLayout(layout);
}

OBNLogVisuailzationChart::~OBNLogVisuailzationChart()
{
    if(NULL != series)
    {
        series->clear();
        delete [] series;
    }
}


void OBNLogVisuailzationChart::setChartName(const QString& pChartName)
{
    if(NULL != qchart)
    {
        qchart->setTitle(pChartName);
    }
}

void OBNLogVisuailzationChart::setAxis(int curveNum,
                                       QString _xname, qreal _xmin, qreal _xmax, int _xtickc,
                                       QString _yname, qreal _ymin, qreal _ymax, int _ytickc,
                                       QList<QColor> _colorList)
{
    axisX->setRange(_xmin, _xmax);    //设置范围
    axisX->setLabelFormat("%u");      //设置刻度的格式(%u:无符号十进制整数,%s:字符串,%c:一个字符,%d:有符号十进制整数,%e:浮点数、e-记数法,%f:浮点数、十进制记数法,%s:字符串)
    axisX->setGridLineVisible(true);  //网格线可见
    axisX->setTickCount(_xtickc);     //设置多少个大格
    axisX->setMinorTickCount(1);      //设置每个大格里面小刻度线的数目
    axisX->setTitleText(_xname);      //设置描述

    axisY->setRange(_ymin, _ymax);
    axisY->setLabelFormat("%f");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(_ytickc);
    axisY->setMinorTickCount(1);
    axisY->setTitleText(_yname);

    qchart->addAxis(axisX, Qt::AlignBottom); //下：Qt::AlignBottom  上：Qt::AlignTop
    qchart->addAxis(axisY, Qt::AlignLeft);   //左：Qt::AlignLeft    右：Qt::AlignRight
    qchart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线动画模式
    qchart->legend()->hide(); //隐藏图例

    /// ======
    series = new QSplineSeries[curveNum];
    for(int iList = 0; iList < curveNum; iList ++)
    {
        series[iList].setPen(QPen(_colorList[iList], 2, Qt::SolidLine));
        series[iList].setPointsVisible(true);

        qchart->addSeries(&(series[iList]));//输入数据

        series[iList].attachAxis(axisX);
        series[iList].attachAxis(axisY);
    }
}

/// ====== 重新设置当前坐标系
void OBNLogVisuailzationChart::setCurrentDataRange(qreal _xmin, qreal _xmax, qreal _ymin, qreal _ymax)
{
    qchart->axisX()->setRange(_xmin, _xmax);
    qchart->axisY()->setRange(_ymin, _ymax);
}

void OBNLogVisuailzationChart::setAxisCurrentYName(const QString pYName)
{
    qchart->axisY()->setTitleText(pYName);
}

void OBNLogVisuailzationChart::setAxisCurrentXName(const QString pXName)
{
    qchart->axisX()->setTitleText(pXName);
}

/// ====== 设置曲线颜色
void OBNLogVisuailzationChart::setCurveColor(int iCurveNO, QColor pColor)
{
}

/// ====== 设置显示当前选中曲线
void OBNLogVisuailzationChart::setCurrentLogData(QList<QList<QPointF>> plistPointfList)
{
    /// ====== 先将当前显示的曲线清除
    for(int iSeries = 0; iSeries < plistPointfList.count(); iSeries ++)
    {
        series[iSeries].clear();
    }
    /// ======
    for(int iList = 0; iList < plistPointfList.count(); iList ++)
    {
        for(int jList = 0; jList < plistPointfList[iList].count(); jList ++)
        {
            //qDebug() << "iList = " << iList << "\t jList = " << jList << "\t" << plistPointfList[iList].at(jList);
            series[iList].append(plistPointfList[iList].at(jList));
        }
    }
}
