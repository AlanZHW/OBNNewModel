#ifndef OBNCHART_H
#define OBNCHART_H

#include <QChart>
#include <QWidget>
#include <QChartView>
#include <QValueAxis>
#include <QSplineSeries>
#include <QHBoxLayout>

QT_CHARTS_USE_NAMESPACE
class OBNChart : public QWidget
{
    Q_OBJECT
public:
    explicit OBNChart(QWidget* parent = 0, QString _chartname = "曲线图");
    ~OBNChart(){}
    /// ====== 初始化坐标系
    void setAxis(QString _xname, qreal _xmin, qreal _xmax, int _xtickc, QString _yname, qreal _ymin, qreal _ymax, int _ytickc);
    /// ====== 重新设置坐标系范围
    void setAddPointF(QPointF _pointInfom, qreal _xmin, qreal _xmax, qreal _ymin, qreal _ymax);
private:
    QChart *qchart;
    QChartView *chartview;
    QSplineSeries *series;

    QHBoxLayout *layout;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QString chartname;

    /// ====== 坐标轴参数
    QString xname;
    qreal xmin;
    qreal xmax;
    int xtickc;

    QString yname;
    qreal ymin;
    qreal ymax;
    int ytickc;
};

#endif // OBNCHART_H
