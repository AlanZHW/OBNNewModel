#ifndef OBNCHART_H
#define OBNCHART_H

#include <QChart>
#include <QWidget>
#include <QDebug>
#include <QChartView>
#include <QValueAxis>
#include <QCategoryAxis>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QOpenGLWidget>

QT_CHARTS_USE_NAMESPACE
class OBNChart : public QWidget
{
    Q_OBJECT
public:
    explicit OBNChart(QWidget* parent = 0, QString _chartname = "曲线图");
    ~OBNChart(){
        if(NULL != series && 0 != series->count())
            series->clear();
    }
    /// ====== 初始化坐标系
    void setAxis(QString _xname, qreal _xmin, qreal _xmax, int _xtickc, QString _yname, int _ymin, int _ymax, int _ytickc);
    /// ====== 重新设置坐标系范围
    void setAddPointF(QPointF _pointInfom, qreal _xmin, qreal _xmax, qreal _ymin, qreal _ymax);
    /// ======
    void addData(int _data);
private:
    QChart *qchart;
    QChartView *chartview;
    QSplineSeries *series;

    int m_curentDataNum;

    QHBoxLayout *layout;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QCategoryAxis *axisInfo;
    QString chartname;
    /// ====== 坐标轴参数
    QString xname;
    qreal xmin;
    qreal xmax;
    int xtickc;
    QString yname;
    int ymin;
    int ymax;
    int ytickc;
    bool isDisplayLine2 = false;

    int m_currentDisplayPointNumb = 2000;

    QVector<QPointF> temp200;
};

#endif // OBNCHART_H
