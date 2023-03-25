#include "obnchart.h"

OBNChart::OBNChart(QWidget* parent, QString _chartname)
{
    setParent(parent);

    chartname = _chartname;

    /// ======
    series = new QSplineSeries(this);
    series->setPen(QPen(Qt::blue,1,Qt::SolidLine));
    series->setPointsVisible(true);

    /// ======
    qchart = new QChart;
    qchart->setTitle(chartname);
    qchart->setContentsMargins(0,0,0,0);
    qchart->setMargins(QMargins(0,0,0,0));
    qchart->setBackgroundRoundness(0);
    qchart->addSeries(series);//输入数据

    /// ======
    chartview= new QChartView(qchart);
    chartview->setContentsMargins(0,0,0,0);
    chartview->setRenderHint(QPainter::Antialiasing);//防止图形走样
    chartview->setStyleSheet("background-color:#FF0000");

    layout   = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    axisX    = new QValueAxis(this);
    axisY    = new QValueAxis(this);

    /// ======在ui里面添加了一个Widget并把曲线图添加进去
    layout->addWidget(chartview);
    setLayout(layout);
}

/// ====== 设置坐标系信息
/// 参数说明
/// _xname: X轴名称
/// _xmin:  X轴最小值
/// _xmax:  X轴最大值
/// _xtickc:X轴坐标系显示段数
/// _yname: Y轴名称
/// _ymin:  Y轴最小值
/// _ymax:  Y轴最大值
/// _ytickc:Y轴坐标系显示段数
void OBNChart::setAxis(QString _xname, qreal _xmin, qreal _xmax, int _xtickc, QString _yname, qreal _ymin, qreal _ymax, int _ytickc)
{
    xname  = _xname;
    xmin   = _xmin;
    xmax   = _xmax;
    xtickc = _xtickc;
    yname  = _yname;
    ymin   = _ymin;
    ymax   = _ymax;
    ytickc = _ytickc;

    axisX->setRange(xmin, xmax);    //设置范围
    axisX->setLabelFormat("%u");   //设置刻度的格式(%u:无符号十进制整数,%s:字符串,%c:一个字符,%d:有符号十进制整数,%e:浮点数、e-记数法,%f:浮点数、十进制记数法,%s:字符串)
    axisX->setGridLineVisible(true);   //网格线可见
    axisX->setTickCount(xtickc);       //设置多少个大格
    axisX->setMinorTickCount(1);   //设置每个大格里面小刻度线的数目
    axisX->setTitleText(xname);  //设置描述

    axisY->setRange(ymin, ymax);
    axisY->setLabelFormat("%u");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(ytickc);
    axisY->setMinorTickCount(1);
    axisY->setTitleText(yname);

    qchart->addAxis(axisX, Qt::AlignBottom); //下：Qt::AlignBottom  上：Qt::AlignTop
    qchart->addAxis(axisY, Qt::AlignLeft);   //左：Qt::AlignLeft    右：Qt::AlignRight
    qchart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线动画模式
    qchart->legend()->hide(); //隐藏图例

    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

/// ====== 重新设置坐标系范围
void OBNChart::setAddPointF(QPointF _pointInfom, qreal _xmin, qreal _xmax, qreal _ymin, qreal _ymax)
{
    /// ====== 当显示的点超过100个,将删除第一个,设置当前每次只能显示100个点
    if(100 >= series->points().count())
    {
        series->remove(0);
    }
    qchart->axisX()->setRange(_xmin, _xmax);
    qchart->axisY()->setRange(_ymin, _ymax);
    series->append(_pointInfom);
}
