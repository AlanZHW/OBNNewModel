#ifndef SPSFILES_H
#define SPSFILES_H

#include <QtCore>
#include <QString>
#include <QStringList>
#define  Unit_Name_Maxlen   36

#include "core_global.h"
#include "publicHostInform.h"

class SPSFiles
{
public:
    SPSFiles();
};

/// ======---------------------------------------
#define   SPS_READ_DATA_PTR_EMPTY     1
#define   SPS_READ_FILE_OPEN_FAILED   2
/// ======functions ,读取SR 文件，格式相同-------------------------------
CORESHARED_EXPORT int read_sps_r_file(const QString &fileName,StationInfo *stationInfo);
CORESHARED_EXPORT int read_sps_s_file(const QString &fileName,StationInfo *stationInfo);
CORESHARED_EXPORT int gobs_sps_file_SR_read(const QString &fileName,StationInfo *stationInfo);
/// ======读取X文件-------------------------
CORESHARED_EXPORT int gobs_sps_file_X_read(const QString &fileName,RelationInfo *relationInfo);
/// ======只读取SR 文件
CORESHARED_EXPORT int gobs_sps_files_SR_read(QStringList spsFileNames,AreaDataInfo *areaDataInfo,QString *errorStr = 0);
/// ======
CORESHARED_EXPORT int gobs_sps_files_read(QStringList spsFileNames,AreaDataInfo *areaDataInfo,QString *errorStr = 0);

#endif /// ====== SPSFILES_H
