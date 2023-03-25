#ifndef SYSTEMDISPLAY_H
#define SYSTEMDISPLAY_H

#include <QWidget>
#include <QDebug>
#include <QPainter>

#include "math.h"

typedef struct
{
    double GPSX;
    double GPSY;
    double x;
    double y;
}SystemCoord;

typedef struct
{
    double x;
    double y;
    double h;
}SystemCoordGOBS;

namespace Ui {
class systemdisplay;
}

class systemdisplay : public QWidget
{
    Q_OBJECT

public:
    explicit systemdisplay(QWidget *parent = 0);
    ~systemdisplay();
//    void initSystemDisplay();
    void initWindows();
    void dispCoordCurrent(const double, const double, const double, const double);
    void setCoordforGPS(const double& pX, const double& pY);
    void setGOBSCoord(const double& pX, const double& pY, const double& pZ);
    void setCoordSystemInfo(const double& pX0, const double& pY0, const double& pZ0);
    void setCoordAfterCalculator(const double& pX, const double& pY, const double& pZ);
protected:
    void paintEvent(QPaintEvent*);

private:
    Ui::systemdisplay *ui;
    double mX0, mY0, mZ0;
    double mXAfter, mYAfter, mZAfter;
    bool   flag, flagGPS, flagAfter;
    QVector<SystemCoord> m_SystemCoordVector;
    QVector<SystemCoordGOBS> m_SystemCoordGOBSVec;
//    QVector<SystemCoord> m_DispCoordVec;
    SystemCoord m_DispCoord;
};

#endif // SYSTEMDISPLAY_H
