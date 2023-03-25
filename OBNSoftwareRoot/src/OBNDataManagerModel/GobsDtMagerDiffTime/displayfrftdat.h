#ifndef DISPLAYFRFTDAT_H
#define DISPLAYFRFTDAT_H

//====显示flft输出数据信息

#include <QList>
#include <QFile>
#include <QPainter>
#include <QDialog>
#include <QDebug>
#include <QIODevice>
#include <QTextStream>

#define MAX(a,b) a>b?a:b

namespace Ui {
class DisplayFrftDat;
}

class DisplayFrftDat : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayFrftDat(QWidget *parent = 0);
    ~DisplayFrftDat();
    QPoint origin();
    void setFrftOutData(QString frftOneTFName);
private:
    virtual void paintEvent(QPaintEvent *event);
private:
    Ui::DisplayFrftDat *ui;
    float *mTimeData, *mDataInfo;
    int   mDataCont, mTimeCont;
};

#endif // DISPLAYFRFTDAT_H
