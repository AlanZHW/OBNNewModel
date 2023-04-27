#include "obnchart.h"

OBNChart::OBNChart(QWidget* parent, QString _chartname): m_curentDataNum(0)
{
    setParent(parent);

    chartname = _chartname;

    /// ======
    series = new QSplineSeries(this);
    series->setPen(QPen(Qt::yellow,1,Qt::SolidLine));
    series->setUseOpenGL(true);

    /// ======
    qchart = new QChart;
    qchart->setTheme(QChart::ChartTheme::ChartThemeDark);
//    qchart->setFont(QFont("宋体"));
    qchart->setTitle(chartname);
    qchart->setContentsMargins(0,0,0,0);
    qchart->setMargins(QMargins(0,0,0,0));
    qchart->setBackgroundRoundness(0);
    qchart->addSeries(series);//输入数据

    /// ======
    chartview= new QChartView(qchart);
    chartview->setContentsMargins(0,0,0,0);
    chartview->setRenderHint(QPainter::Antialiasing);//防止图形走样

    layout   = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    axisX    = new QValueAxis(this);
    axisY    = new QValueAxis(this);
    axisInfo = new QCategoryAxis;

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
void OBNChart::setAxis(QString _xname, qreal _xmin, qreal _xmax, int _xtickc, QString _yname, int _ymin, int _ymax, int _ytickc)
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
    axisX->setLabelsFont(QFont("宋体"));
    axisX->setTitleText(xname);  //设置描述

    axisY->setRange(ymin, ymax);
    axisY->setLabelFormat("%d");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(ytickc);
    axisY->setMinorTickCount(1);
    axisY->setLabelsFont(QFont("宋体"));
    axisY->setTitleText(yname);

    axisInfo->setMin(0);
    axisInfo->setMax(2);
    axisInfo->setGridLineVisible(false);
    axisInfo->setLabelsFont(QFont("宋体"));
    axisInfo->append("MIN=", 0);
    axisInfo->append("RAN=", 1);
    axisInfo->append("MAX=", 2);
    axisInfo->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    qchart->addAxis(axisX, Qt::AlignBottom); //下：Qt::AlignBottom  上：Qt::AlignTop
    qchart->addAxis(axisY, Qt::AlignLeft);   //左：Qt::AlignLeft    右：Qt::AlignRight
    qchart->addAxis(axisInfo, Qt::AlignRight);

#if 0
    qchart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线动画模式
#else
    qchart->setAnimationOptions(QChart::NoAnimation);//设置曲线动画模式
#endif
    qchart->legend()->hide(); //隐藏图例

    series->attachAxis(axisX);
    series->attachAxis(axisY);
    series->attachAxis(axisInfo);
}

void OBNChart::addData(int _data)
{
    QPointF point(QPoint(m_curentDataNum, _data));
    if(m_curentDataNum < m_currentDisplayPointNumb)
    {
        series->append(point);
        m_curentDataNum += 1;

        ymin   = qMin(ymin, _data);
        ymax   = qMax(ymax, _data);
        qchart->axisY()->setRange(ymin, ymax);

        axisInfo->remove("MIN=");
        axisInfo->remove("RAN=");
        axisInfo->remove("MAX=");
        int tempNum = (ymax-ymin)/2;
        axisInfo->setMin(ymin);
        axisInfo->setMax(ymax);
        axisInfo->append("MIN=", ymin);
        axisInfo->append("RAN=", tempNum);
        axisInfo->append("MAX=", ymax);
    }
    else
    {

        m_curentDataNum += 1;
        if(10 > temp200.count())
        {
            temp200.append(point);
        }
        else
        {
            QVector<QPointF> pts0ld = series->pointsVector();//原始数据
            QVector<QPointF> ptsNew;//更新后的数据

            ymin = 8000000;
            ymax = -8000000;
            //将后面数据向前平移
            qint64 iCp =0;
            int    iTempData = 0;
            for(iCp = 0; iCp < pts0ld.count()-10; iCp++)
            {
                iTempData = pts0ld[10 + iCp].y();
                ymin   = qMin(ymin, iTempData);
                ymax   = qMax(ymax, iTempData);
                ptsNew.append(QPointF(iCp, pts0ld[10 + iCp].y()));//将后面数据平移到开头
            }

            for(qint64 i = iCp, iList = 0; iList < temp200.count(); i ++, iList ++)
            {
                iTempData = temp200.at(iList).y();
                ymin   = qMin(ymin, iTempData);
                ymax   = qMax(ymax, iTempData);

                QPointF newPoint(i, temp200.at(iList).y());
                ptsNew.append(newPoint);
            }
            temp200.clear();
            series->replace(ptsNew);

            qchart->axisY()->setRange(ymin, ymax);

            axisInfo->remove("MIN=");
            axisInfo->remove("RAN=");
            axisInfo->remove("MAX=");
            int tempNum = (ymax-ymin)/2;
            axisInfo->setMin(ymin);
            axisInfo->setMax(ymax);
            axisInfo->append("MIN=", ymin);
            axisInfo->append("RAN=", tempNum);
            axisInfo->append("MAX=", ymax);
        }
    }
}

/// ====== 重新设置坐标系范围
void OBNChart::setAddPointF(QPointF _pointInfom, qreal _xmin, qreal _xmax, qreal _ymin, qreal _ymax)
{
    /// ====== 当显示的点超过1000个,将删除第一个,设置当前每次只能显示1000个点
    if(1000 >= series->points().count())
    {
        series->remove(0);
    }
//    qchart->axisX()->setRange(_xmin, _xmax);
    QValueAxis *axisY = qobject_cast<QValueAxis *>(qchart->axisY());
    double yRange = axisY->max() - axisY->min();
    axisY->setRange(axisY->max() - yRange / 2.0, axisY->max() + yRange / 2.0);
//    qchart->axisY()->setRange(_ymin, _ymax);
    series->append(_pointInfom);
}
