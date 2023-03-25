#ifndef DISPLAYACUDATA_H
#define DISPLAYACUDATA_H

#include <QFile>
#include <QDebug>
#include <QDialog>
#include <QString>
#include <QIODevice>
#include <QTextStream>
#include <QStringList>
#include <QPainter>

#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b

#include <iostream>
using namespace std;

typedef struct AcufInfo
{
    QString NodeName;
    QString AcufileName;
    QString AcufileStartTime;
}AcufileInfo;

namespace Ui {
class DisplayAcuData;
}

class DisplayAcuData : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayAcuData(QWidget *parent = 0);
    DisplayAcuData(QString pNodeName, QString &pAcuFile, int pHourNum);
    ~DisplayAcuData();
    void setAcuFileName(QString pNodeName, QString &pAcuFile, int pHourNum);
    QPoint origin();
private:
    virtual void paintEvent(QPaintEvent *event);
private:
    Ui::DisplayAcuData *ui;
    int   TimeErrCont;
    QString mNideName;
    int     mHourNum;
    QList<QList<float>> ArrayTimeErr;
};

#endif // DISPLAYACUDATA_H
