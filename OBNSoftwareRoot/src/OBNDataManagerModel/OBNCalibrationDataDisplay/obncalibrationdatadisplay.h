#ifndef OBNCALIBRATIONDATADISPLAY_H
#define OBNCALIBRATIONDATADISPLAY_H

#include <QDir>
#include <QFile>
#include <QDialog>
#include <QString>
#include <QRadioButton>
#include <QTextStream>
#include <QFileDialog>

#include "obnadjdatalist.h"
#include "obncalibratondatachart.h"
#include "obncalibrationdatapublic.h"
#include "obncalibrationdatadisplay_global.h"


struct FilterCoeff
{
    int len;
    QVector<double> a;
    QVector<double> b;
};

QT_BEGIN_NAMESPACE
namespace Ui { class OBNCalibrationDataDisplay; }
QT_END_NAMESPACE

class OBNCALIBRATIONDATADISPLAY_EXPORT OBNCalibrationDataDisplay : public QDialog
{
    Q_OBJECT

public:
    OBNCalibrationDataDisplay(QWidget *parent = nullptr);
    ~OBNCalibrationDataDisplay();
    /// ====== 读取ADJ文件内容
    void readADJFileInforms(const QStringList &);
    /// ====== 显示ADJ文件内容
    void displayADJFileInform();

private:
    void getRange(QList<ADJDispInform> _adjDispInform, qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<PointInform>>& pListPointfList);

private:
    /// ====== 过滤相关
    void filteringRoot();
    void BiDirectionalFilter(const double * sig, double * sout, const int data_len);
    void dataRollingOver(const double * sig,double * sout,const int data_len);
    void FiltData(const double * sig, double * sout,const int data_len);
    int  signalExtend(const double *sig, double * sout, const int data_len, const int nfact);
    /// ======获取当前数据过零点
    bool queryDataZeroCross(QList<ADJDispInform>& _adjDataList);
private:
    FilterCoeff myfilter;

    /// ====== 当前ADJ文件列表
    QStringList m_adjFileNameList;
    QList<ADJDispInform> m_adjXDataList, m_adjYDataList, m_adjZDataList;

    OBNCalibratonDataChart* m_chartXDisplay, *m_chartYDisplay, *m_chartZDisplay;

    Ui::OBNCalibrationDataDisplay *ui;
};
#endif // OBNCALIBRATIONDATADISPLAY_H
