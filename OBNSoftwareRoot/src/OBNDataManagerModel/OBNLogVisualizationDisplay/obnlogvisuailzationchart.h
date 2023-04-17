#ifndef OBNLOGVISUAILZATIONCHART_H
#define OBNLOGVISUAILZATIONCHART_H

#include <QChart>
#include <QDebug>
#include <QWidget>
#include <QChartView>
#include <QValueAxis>
#include <QSplineSeries>
#include <QHBoxLayout>

QT_CHARTS_USE_NAMESPACE
class OBNLogVisuailzationChart : public QWidget
{
    Q_OBJECT
public:
    explicit OBNLogVisuailzationChart(const QString& pNameInform, QWidget *parent = nullptr);
    ~OBNLogVisuailzationChart();

    void setAxis(int curveNum, QString _xname, qreal _xmin, qreal _xmax, int _xtickc, QString _yname, qreal _ymin, qreal _ymax, int _ytickc, QList<QColor> _colorList);
    void setChartName(const QString&);

    void setCurrentDataRange(qreal _xmin, qreal _xmax, qreal _ymin, qreal _ymax);
    void setAxisCurrentYName(const QString);
    void setAxisCurrentXName(const QString);

    void setCurrentLogData(QList<QList<QPointF>>& plistPointfList);
    /// ====== 设置曲线颜色
    void setCurveColor(int iCurveNO, QColor pColor);
    /// ====== 设置是否显示当前曲线
    void changeLineDisplayState(int _curve_no, bool _state);
signals:


private:
    QChart *qchart;
    QChartView *chartview;
    QSplineSeries *series;
    QHBoxLayout *layout;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QList<QList<QPointF>> m_currentDisplayPoints;
};

#endif // OBNLOGVISUAILZATIONCHART_H
