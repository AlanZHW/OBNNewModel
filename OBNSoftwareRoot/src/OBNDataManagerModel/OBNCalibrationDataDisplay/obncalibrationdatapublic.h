#ifndef OBNCALIBRATIONDATAPUBLIC_H
#define OBNCALIBRATIONDATAPUBLIC_H

#include <QColor>
#include <QVector>
#include <QString>

typedef struct {
    double  averageValue;       ///< 平均值
    double  standardDeviation;  ///< 标准差
}ADJAllDataParameterInform;

/// ====== 涉及到所有数据计算参数内容
typedef struct {
    ADJAllDataParameterInform x_component;
    ADJAllDataParameterInform y_component;
    ADJAllDataParameterInform z_component;
}ADJAllDataInform;

/// ====== 数据点信息
typedef struct{
    bool    isZeroCorss;    ///< 当前点是否是过零点
    double  dataNumber;     ///< 当前点数据值
}ADJPointDataInform;

/// ===== 显示线信息
typedef struct adj_display_infom{
    adj_display_infom(){
        adjName.clear();
        n_zeroCrossNum = 0;     ///< 过零点位置
        dampingInform = 0;      ///< 阻尼
        cycleInform = 0;        ///< 周期
        averageValue = 0;       ///< 平均值
        relativeError = 0;      ///< 相对误差
        relativeFrequency = 0;  ///<相对频率
    }
    QString adjName;        ///< 当前线名称
    QColor  nLineColor;     ///< 当前线颜色
    int     n_zeroCrossNum; ///< 过零点位置
    double  dampingInform;  ///< 阻尼
    double  cycleInform;    ///< 周期
    double  averageValue;   ///< 平均值
    double  relativeError;  ///< 相对误差
    double  relativeFrequency;///<相对频率
    QVector<ADJPointDataInform> adjDataList;    ///< 当前数据列表
}ADJDispInform;

/// ====== 当前标定文件格式
typedef enum{
    OBN = 0,
    CDS
}CalibrationDataMode;

#endif // OBNCALIBRATIONDATAPUBLIC_H
