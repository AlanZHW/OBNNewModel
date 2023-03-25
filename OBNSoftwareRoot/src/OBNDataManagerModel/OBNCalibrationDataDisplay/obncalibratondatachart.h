#ifndef OBNCALIBRATONDATACHART_H
#define OBNCALIBRATONDATACHART_H

#include <QHash>
#include <QColor>
#include <QVariant>
#include <QXYSeries>

#include <QLabel>
#include <QChart>
#include <QDebug>
#include <QWidget>
#include <QPushButton>
#include <QValueAxis>
#include <QChartView>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QSplineSeries>
#include <QScatterSeries>
#include "obncalibrationlinecolorwidget.h"

QT_CHARTS_USE_NAMESPACE

typedef struct{
    bool isZeroCorss;
    QPointF nPointInfom;
}PointInform;

class OBNCalibratonDataChart : public QWidget
{
    Q_OBJECT
public:
    explicit OBNCalibratonDataChart(const QString&, QWidget *parent = nullptr);
    ~OBNCalibratonDataChart();

    void setAxis(int curveNum, QString _xname, qreal _xmin, qreal _xmax, int _xtickc, QString _yname, qreal _ymin, qreal _ymax, int _ytickc, QList<QColor> _colorList);
    void setChartName(const QString&);

    void setCurrentDataRange(qreal _xmin, qreal _xmax, qreal _ymin, qreal _ymax);
    void setAxisCurrentYName(const QString);
    void setAxisCurrentXName(const QString);

    void setCurrentLogData(QList<QList<PointInform>> plistPointfList);
    void setCurveColor(int iCurveNO, QColor pColor);

protected:
    void mouseDoubleClickEvent(QMouseEvent*);

signals:
    void signalRightButtonDoubleClick();

    private:
        QChart *qchart;
        QLabel     *m_valueLabel;
        QChartView *chartview;

        QSplineSeries *series;
        QScatterSeries*seriesZero;

        QHBoxLayout *layout;
        QValueAxis *axisX;
        QValueAxis *axisY;
        QList<QColor> m_colorList;
        /// ======
        bool isDisplayLineInform;
        QPushButton* pushButton;
        OBNCalibrationLineColorWidget* m_lineColorWidget;
    };

    #endif // OBNCALIBRATONDATACHART_H
