#ifndef GPSPUBLIC_H
#define GPSPUBLIC_H

#include <QtGlobal>
#include <functional>
#include <QDebug>

/// 用于解算结构体
struct GPSInfo
{
    double x;
    double y;
    double z;
    double t;
};

//GPS 坐标
struct Coord
{
    double gpsX;
    double gpsY;
    double x;
    double y;
};

struct   GpsCoord : public Coord
{
    GpsCoord();
    GpsCoord toXy();

    quint32  utc_sec = 0; //utc毫秒
};

struct GobsCoord : public Coord
{
    double z;//gobs 增加z坐标分量
};

//数据范围
struct DataScope
{
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ = 0;
    float maxZ = 0;
};



#ifdef __cplusplus
extern "C"{
#endif

//计算刻度的距离

#ifdef __cplusplus
}
#endif

//typedef std::function<void (const QString &)> ShowTextFunc;


#endif // GPSPUBLIC_H
