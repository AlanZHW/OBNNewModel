#ifndef OBNCALIBRATIONDATAPUBLIC_H
#define OBNCALIBRATIONDATAPUBLIC_H

#include <QColor>
#include <QVector>
#include <QString>


/// ====== 数据点信息
typedef struct{
    bool    isZeroCorss;    ///< 当前点是否是过零点
    double  dataNumber;     ///< 当前点数据值
}ADJPointDataInform;

/// ===== 显示线信息
typedef struct {
    QString adjName;        ///< 当前线名称
    QColor  nLineColor;     ///< 当前线颜色
    int     n_zeroCrossNum; ///< 过零点位置
    double  dampingInform;  ///< 阻尼
    double  cycleInform;    ///< 周期
    QVector<ADJPointDataInform> adjDataList;    ///< 当前数据列表
}ADJDispInform;

#endif // OBNCALIBRATIONDATAPUBLIC_H
