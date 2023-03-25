#ifndef VISITACUFILE_H
#define VISITACUFILE_H

//=====读取ACU文件,并生成ACU中间文件,方便在显示图像时使用
#include <QFile>
#include <QList>
#include <QThread>
#include <QIODevice>
#include <QTextStream>
#include <QStringList>

#include "displayacudata.h"
//#include "FrftProcess.h"
//#include "testmatlab.h"
//#include "mclmcr.h"

#include "projectarea.h"
#include "spsfiles.h"
#include "projectarea.h"

typedef struct unitinfo
{
    QString unitName;
    float   X;
    float   Y;
}UnitInfo;

typedef struct origininfo
{
    origininfo()
    {
        TimeDef = NULL;
    }
    QString OriginName;
    double  OriginX;
    double  OriginY;
    double  OriginZ;
    double  TimeBegin;
    int     timeDefNum;
    double* TimeDef;
}OriginInfo;


class VisitACUFile : public QThread
{
    Q_OBJECT

public:
    VisitACUFile();
    ~VisitACUFile();
    QStringList OutfileNameList;

    void setAcufileInfo(QList<AcufileInfo>&);
    void setOrigInfo(const double& pOrgX, const double& pOrgY);
    void setConfigfile(const QString& pCfgFile);
//    void CallMatlabFunction(short *pArrayData, int pdataCont, QString pNodeName);

    void setProjInfo(ProjectInfo*);
    void setAreaName(const QString& pAreaName){m_AreaName = pAreaName;}

 //   void CallMatlabFunction(QString pNodeName);
//    void CallMatlabFunction(QList<AcufileInfo>&, QList<UnitInfo>&, int& listNo, AreaDataInfo*);
    bool CallMatlabFunction(QList<AcufileInfo>& pAcufNamelist, int& pOriginNum, OriginInfo* pOriginInfo, QList<UnitInfo>& pUnitInfoList, int& listNo, AreaDataInfo *areaDataInfo);
    void setProgremInfo(int pN1, double pfs, int pfsdev, double pdistance, double pB, int pf0, int ptimedef);
protected:
    void run();

signals:
    void signalSuccess(QStringList);
    void signalError(const QString&);

private:
    QList<AcufileInfo> mAcufileInfoList;
    double mN1[1];
    double mfsdev[1];
    double mf0[1];
    double* mtimedef;
    double mtimeDefcp[1];
    double nTimeBegin[1];
    double nDistance[1];
    double mfs[1], mdistance[1], mB[1];
    double mOrgX, mOrgY;
    QString ConfigFile;
    AreaDataInfo       *m_areaDataInfo;
    ProjectInfo        *m_projInfo;
    QString m_AreaName;
};

#endif // VISITACUFILE_H
