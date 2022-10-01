#ifndef OBNLOGVISUALIZATIONDRAW_H
#define OBNLOGVISUALIZATIONDRAW_H

#include <QWidget>
#include <QDebug>
#include <QPainter>

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

typedef struct {
    float batF;
    float TNum;
    float PNum;
    float ThetaNum;
    float GammaNum;
    float AzNum;
}SuctLOGInform;

namespace Ui {
class OBNLogVisualizationDraw;
}

class OBNLogVisualizationDraw : public QWidget
{
    Q_OBJECT

public:
    explicit OBNLogVisualizationDraw(QWidget *parent = nullptr);
    ~OBNLogVisualizationDraw();

    void paintEvent(QPaintEvent *event);


    void setCurrentDrawDataInform(QList<SuctLOGInform>* pSuctLogInform);

    void setDrawBAT_V(bool state);
    void setDrawT(bool state);
    void setDrawP(bool state);
    void setDrawTheta(bool state);
    void setDrawGamma(bool state);
    void setDrawAz(bool state);

private:
    bool isDrawBAT_V, isDrawT, isDrawP, isDrawTheta, isDrawGamma, isDrawAz;
    QList<SuctLOGInform>* m_suctLOGInform;
    Ui::OBNLogVisualizationDraw *ui;
};

#endif // OBNLOGVISUALIZATIONDRAW_H
