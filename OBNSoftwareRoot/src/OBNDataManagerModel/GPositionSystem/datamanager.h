#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVector>
#include "gpspublic.h"

//数据管理-单例模式
class DataManager
{
public:
    static DataManager *instance();

    //添加GPS坐标点
    void addGpsCoord(const GpsCoord& cord);
    QVector<GpsCoord> m_gpsCord;
protected:
    DataManager();

private:
};

#endif // DATAMANAGER_H
