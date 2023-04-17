#ifndef READCALIBATIONDATA_H
#define READCALIBATIONDATA_H

#include <QFile>
#include <QList>
#include <QDebug>
#include <QVector>
#include <QObject>
#include <QMetaType>
#include <QFileInfo>
#include <QTextStream>

#include <math.h>
#include <memory>

#include "obncalibrationdatapublic.h"

const double m_pi = 3.141592653;
const double d_min= 0.0000001;

/// ====== 去均值
template<typename T>
void detrend_IP(T *y, int m);
/// ====== 取平均数
template<typename T>
T average_value(T* data, int m);
/// ======  数组数据减掉一个数
template<typename T>
void minus_value(T* data, T m, int num);
/// ====== 求数据最大值,并返回最大值和最大值的位置
template<typename T>
void maxf(T* data, int num, T max_value, int max_locat);
/// ====== 求数据最小值,并返回最大值和最小值的位置
template<typename T>
void minf(T* data, int num, T max_value, int max_locat);

struct FilterCoeff
{
    int len;
    QVector<double> a;
    QVector<double> b;
};

class ReadCalibationData : public QObject
{
    Q_OBJECT
public:
    explicit ReadCalibationData(QObject *parent = nullptr);

public slots:
    void slotReadCalibationDataFunction(int, const QStringList&);

signals:
    /// ====== 读取完成数据后将内容通过信号转发给UI
    void signal_current_adj_data_inform(QVector<ADJDispInform>, QVector<ADJDispInform>, QVector<ADJDispInform>, ADJAllDataInform);
private:
    void readCalibationDataFunctionFromOBN(const QStringList&);
    void readCalibationDataFunctionFromCDS(const QStringList&);
    /// ====== 调用线性去趋势计算函数
    void adjDataDetrendFunction(QVector<ADJDispInform> & _adjPointInform);

    /// ====== 过滤
    void filteringFunction(QVector<ADJDispInform> & _adjPointInform);
    void BiDirectionalFilter(const double * sig, double * sout, const int data_len);
    void dataRollingOver(const double * sig,double * sout,const int data_len);
    int  signalExtend(const double *sig, double * sout, const int data_len, const int nfact);
    void FiltData(const double * sig, double * sout,const int data_len);
    bool queryDataZeroCross(QVector<ADJDispInform>&);

    /// ====== 单条线数据查找过零点
    int queryDataZeroCrossLine(QVector<ADJPointDataInform> _adjDataInfrom, int _left, int _right);
    /// ====== 获取最小值,最小值位置
    void queryExtremumMinFunction(QVector<ADJPointDataInform> _adjDataInfromList, int _left, int _right, int& _minLocat, double& _minValue);
    /// ====== 阻尼计算
    void smalldampCalculation(QVector<ADJDispInform>&);
    /// ====== 寻找第一个过零点位置
    /// int firstZeroCrossLocatFunction(ADJDispInform& _adjDataInfrom);
    /// ====== 寻找第二个过零点的位置
    /// int secondZeroCrossLocatFunction(ADJDispInform& _adjDataInfrom);
    /// ====== 获取最大值,最小值,最大值位置以及最小值位置
    void queryExtremumFunction(QVector<ADJPointDataInform> _adjDataInfrom, int _left, int _right, int& _maxLocat, double &_maxValue);
    /// ======
    void allDataParticipatedCalculations(QVector<ADJDispInform> _adjDataInformVector, ADJAllDataParameterInform& _ajdAllDataInform);
private:
    FilterCoeff myfilter;
};

#endif // READCALIBATIONDATA_H
