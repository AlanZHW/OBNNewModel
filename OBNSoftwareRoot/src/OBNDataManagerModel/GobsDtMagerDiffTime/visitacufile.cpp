#include "visitacufile.h"

VisitACUFile::VisitACUFile():m_areaDataInfo(NULL)
{

}

VisitACUFile::~VisitACUFile()
{
    if(NULL != m_areaDataInfo)
    {
        delete m_areaDataInfo;
    }
}

//====获取ACU文件信息,方便在
void VisitACUFile::setAcufileInfo(QList<AcufileInfo> &pAcufileInfoList)
{
    mAcufileInfoList = pAcufileInfoList;
}

void VisitACUFile::setOrigInfo(const double& pOrgX, const double& pOrgY)
{
    mOrgX = pOrgX;
    mOrgY = pOrgY;
}

void VisitACUFile::setConfigfile(const QString& pCfgFile)
{
    ConfigFile = pCfgFile;
}

void VisitACUFile::setProgremInfo(int pN1, double pfs, int pfsdev, double pdistance, double pB, int pf0, int ptimedef)
{
    mN1[0]       = (double)pN1;
    mfsdev[0]    = (double)pfsdev;
    mf0[0]       = (double)pf0;
    mtimeDefcp[0]  = (double)ptimedef;
    mfs[0]       = pfs;
    mdistance[0] = pdistance;
    mB[0]        = pB;
}

//====在线程中读取acu文件后调用matlab函数输出中间文件
void VisitACUFile::run()
{
    FILE* fp = fopen("./01.dat", "wb");
    fprintf(fp, "ConfigFile is%s\n", ConfigFile.toStdString().c_str());
    fflush(fp);
    //====读取config文件获取必要的信息
    if(ConfigFile.isEmpty())
    {
        emit signalError("Config file does not exist.");
        fprintf(fp, "Config file does not exist.");
        fflush(fp);
        return ;
    }

    //====确定震源点的个数
    int OriginLineNum = 0;
    QFile fConfig(ConfigFile);
    if(!fConfig.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        emit signalError("Open config file error.");
        fprintf(fp, "Open config file error.");
        fflush(fp);
        return;
    }
    QTextStream inRd(&fConfig);
    while(!inRd.atEnd())
    {
        QString lineData = inRd.readLine();
        fprintf(fp, "lineData is%s\n", lineData.toStdString().c_str());
        fflush(fp);
        OriginLineNum ++;
    }

    fConfig.close();
    OriginLineNum = OriginLineNum -1;

    fprintf(fp, "OriginLineNum is%d\n", OriginLineNum);
    fflush(fp);

    OriginInfo *nOriginInfo = new OriginInfo[OriginLineNum];
    if(NULL == nOriginInfo)
    {
        emit signalError("Failed to read config file.");
        fprintf(fp, "Failed to read config file");
        fflush(fp);
        return;
    }
    //====读取数据
    QFile fConfigRd(ConfigFile);
    if(!fConfigRd.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        delete [] nOriginInfo;
        nOriginInfo = NULL;
        emit signalError("Failed to read config file.");
        return;
    }
    QTextStream inConfig(&fConfigRd);
    QString lineDataA = inConfig.readLine().trimmed();
    qDebug()<<"lineDataA is:" <<lineDataA;
    int iLineNO = 0;
    while(!inConfig.atEnd())
    {
        QString lineData = inConfig.readLine().trimmed();
        QStringList lineInfoList = lineData.split(" ");

        qDebug()<<"count is:" <<lineInfoList.count();

        nOriginInfo[iLineNO].OriginName = lineInfoList.at(0);
        nOriginInfo[iLineNO].OriginX    = lineInfoList.at(1).toDouble();
        nOriginInfo[iLineNO].OriginY    = lineInfoList.at(2).toDouble();
        nOriginInfo[iLineNO].OriginZ    = lineInfoList.at(3).toDouble();
        nOriginInfo[iLineNO].TimeBegin  = lineInfoList.at(4).toDouble();

        fprintf(fp, "5 is %s\n", lineInfoList[5].toStdString().c_str());
        fflush(fp);

        QStringList timeDefList = lineInfoList[5].split(",");
        nOriginInfo[iLineNO].timeDefNum = timeDefList.count();
        nOriginInfo[iLineNO].TimeDef    = new double[nOriginInfo[iLineNO].timeDefNum];
        for(int iTimeDev = 0; iTimeDev < nOriginInfo[iLineNO].timeDefNum; iTimeDev ++)
            nOriginInfo[iLineNO].TimeDef[iTimeDev] = timeDefList.at(iTimeDev).toDouble();

        lineInfoList.clear();
    }
    fConfigRd.close();

    qDebug()<<__FILE__ <<"\t" <<__LINE__;

    //====读取SPS文件获取设备节点的坐标信息
    //获取sps文件
    QStringList spsFiles = Area::spsFiles1(m_projInfo->ProjectPath, m_AreaName);
    fprintf(fp, "spsFiles.count is %d\n", spsFiles.count());
    fflush(fp);
    if(spsFiles.count() < 1)
    {
        for(int iList = 0; iList < OriginLineNum; iList ++)
        {
            if(NULL != nOriginInfo[iList].TimeDef)
                delete [] nOriginInfo[iList].TimeDef;
        }
        delete [] nOriginInfo;

        emit signalError("Failed to read sps file.");
        return;
    }
    //读取所有的sps文件
    if(NULL != m_areaDataInfo)
        m_areaDataInfo->clearData();
    else
        m_areaDataInfo = new AreaDataInfo;

    fprintf(fp, "read sps in" );
    fflush(fp);

    qDebug() << "read sps in";
    QString errString;
    int ok = gobs_sps_files_read(spsFiles, m_areaDataInfo, &errString);
    if(ok != 0)
    {
        for(int iList = 0; iList < OriginLineNum; iList ++)
        {
            if(NULL != nOriginInfo[iList].TimeDef)
                delete [] nOriginInfo[iList].TimeDef;
        }
        delete [] nOriginInfo;
        delete m_areaDataInfo; m_areaDataInfo = NULL;

        fprintf(fp, "Failed to read sps file" );
        fflush(fp);

        emit signalError("Failed to read sps file.");
        return;
    }
     fprintf(fp, "lineNO < m_areaDataInfo->recvStationInfo->lineNum is %d\n", m_areaDataInfo->recvStationInfo->lineNum);
    fflush(fp);
    QList<UnitInfo> nUnitInfoList;
    for(int lineNO = 0; lineNO < m_areaDataInfo->recvStationInfo->lineNum; ++ lineNO)
    {
        for(int staNO = 0; staNO < m_areaDataInfo->recvStationInfo->staLines[lineNO].staNum; ++ staNO)
        {
            UnitInfo tmpUnitInfo;
            tmpUnitInfo.unitName = QString(QLatin1String(m_areaDataInfo->recvStationInfo->staLines[lineNO].stations[staNO].unit));
            tmpUnitInfo.X        = m_areaDataInfo->recvStationInfo->staLines[lineNO].stations[staNO].x;
            tmpUnitInfo.Y        = m_areaDataInfo->recvStationInfo->staLines[lineNO].stations[staNO].y;
            nUnitInfoList.append(tmpUnitInfo);
        }
    }
    OutfileNameList.clear();

    fprintf(fp, "读取sps文件完成。\n");
    fprintf(fp, "mAcufileInfoList.count is:%d\n", mAcufileInfoList.count());
    fflush(fp);

    //====
    for(int iFile = 0; iFile < mAcufileInfoList.count(); iFile ++)
    {
//        //====读取ACU文件
//        QFile fileACU(mAcufileInfoList.at(iFile).AcufileName);
//        if(!fileACU.exists())
//        {
//            qDebug() << "acu file not existe.";
//            return;
//        }

//        long long fileSize = fileACU.size();
//        long long dataCont = fileSize/sizeof(short);

//        char *arrayData  = new char[fileSize];
//        if(NULL == arrayData)
//        {
//            qDebug() << "create array error.";
//            return;
//        }
//        memset(arrayData, 0, fileSize);

//        FILE *fpACU = fopen(mAcufileInfoList.at(iFile).AcufileName.toStdString().c_str(), "r");
//        if(NULL == fpACU)
//        {
//            qDebug() << "open acu file error.";
//            return;
//        }
//        long long retcong = 0;
//        retcong = fread(arrayData, sizeof(char), fileSize, fpACU);
//        fclose(fpACU);

//        qDebug() << "retcong = " << retcong;

//        short *tmpArrayData = (short*)arrayData;
//        for(long long iDt = 0; iDt < dataCont; iDt ++)
//        {
//            short tmpData  = tmpArrayData[iDt];
//            tmpArrayData[iDt] = ((tmpData & 0x00FF) << 8 ) | ((tmpData & 0xFF00) >> 8);
//        }

//        //====zhw debug
//        FILE *fp = fopen("./test_data", "wb");
//        for(long long itr = 0; itr < dataCont; itr ++)
//            fprintf(fp, "%hd\n", arrayData[dataCont]);
//        fclose(fp); fp = NULL;
//        //====调用matlab程序进行计算
//        CallMatlabFunction(arrayData, dataCont, mAcufileInfoList.at(iFile).AcufileName);
//        delete [] arrayData;

        //====新的实现方式
        if(!CallMatlabFunction(mAcufileInfoList, OriginLineNum, nOriginInfo, nUnitInfoList, iFile, m_areaDataInfo))
        {
            fprintf(fp, "程序运行失败\n");
            fflush(fp);

            for(int iList = 0; iList < OriginLineNum; iList ++)
            {
                if(NULL != nOriginInfo[iList].TimeDef)
                    delete [] nOriginInfo[iList].TimeDef;
            }
            delete [] nOriginInfo;
            delete m_areaDataInfo; m_areaDataInfo = NULL;
            emit signalError("Calculation error.");
        }
    }
    fprintf(fp, "完成且正常结束\n");
    fflush(fp);
    nUnitInfoList.clear();
    fprintf(fp, "完成且正常结束2\n");
    fflush(fp);
    if(NULL != m_areaDataInfo)
    {
        m_areaDataInfo->clearData();
        delete m_areaDataInfo;
    }
    fprintf(fp, "完成且正常结束3\n");
    fflush(fp);
    for(int iList = 0; iList < OriginLineNum; iList ++)
    {
        if(NULL != nOriginInfo[iList].TimeDef)
            delete [] nOriginInfo[iList].TimeDef;
    }
    delete [] nOriginInfo;

    fprintf(fp, "完成且正常结束\n");
    fflush(fp);
    fclose(fp);
    emit signalSuccess(OutfileNameList);
}

void VisitACUFile::setProjInfo(ProjectInfo* p_projInfo)
{
    m_projInfo = p_projInfo;
}


bool VisitACUFile::CallMatlabFunction(QList<AcufileInfo>& pAcufNamelist, int& pOriginNum, OriginInfo* pOriginInfo, QList<UnitInfo>& pUnitInfoList, int& listNo, AreaDataInfo *areaDataInfo)
{
#if 0
    FILE* fp = fopen("./12.dat", "wb");

    QString pAcufName = pAcufNamelist.at(listNo).AcufileName;

    fprintf(fp,"pOriginNum is %d\n",pOriginNum);
    fprintf(fp,"pAcufName is %s\n",pAcufName.toStdString().c_str());
    fflush(fp);

    for(int iOrigNo = 0; iOrigNo < pOriginNum; ++ iOrigNo)
    {
//        if(!testmatlabInitialize())
//        {
//            fprintf(fp,"testmatlabInitialize can not initialize\n");
//            fflush(fp);
//            fclose(fp);
//        }

        if(!FrftProcessInitialize())
        {
            qDebug() << "cant initialize"; 
            fprintf(fp,"FrftProcessInitialize cant initialize");
            fflush(fp);
            fclose(fp);
            return false;
        }

        mtimedef = new double[pOriginInfo[iOrigNo].timeDefNum];
        for(int idef = 0; idef < pOriginInfo[iOrigNo].timeDefNum; idef ++)
            mtimedef[idef] = pOriginInfo[iOrigNo].TimeDef[idef];

        nTimeBegin[0]= pOriginInfo[iOrigNo].TimeBegin;

        if(0 == mdistance[0])
        {
            QString UnitName = pUnitInfoList.at(listNo).unitName;
            int  iList= UnitName.replace("R","").toInt();

            fprintf(fp,"iList is :%d\n",iList);
            fflush(fp);

            if(iList >= pUnitInfoList.count())
            {
                fclose(fp);
                return false;
            }
            nDistance[0] = sqrt(pow(pOriginInfo[iOrigNo].OriginX-pUnitInfoList.at(iList).X, 2)+pow(pOriginInfo[iOrigNo].OriginY-pUnitInfoList.at(iList).Y, 2));

        }
        else
        {
            nDistance[0] = mdistance[0];
        }
//        //====zhw debug
//        nDistance[0] = mdistance[0];

        //====参数
        mwArray arrayN1(1, 1, mxDOUBLE_CLASS);
        arrayN1.SetData(mN1, 1);

        mwArray arrayFS(1, 1, mxDOUBLE_CLASS);
        arrayFS.SetData(mfs, 1);

        mwArray arrayFSDEV(1, 1, mxDOUBLE_CLASS);
        arrayFSDEV.SetData(mfsdev, 1);

        mwArray arrayDistance(1, 1, mxDOUBLE_CLASS);
        arrayDistance.SetData(nDistance, 1);

        mwArray arrayB(1, 1, mxDOUBLE_CLASS);
        arrayB.SetData(mB, 1);

        mwArray arrayF0(1, 1, mxDOUBLE_CLASS);
        arrayF0.SetData(mf0, 1);

        mwArray arrayTimeDef(1, pOriginInfo[iOrigNo].timeDefNum, mxDOUBLE_CLASS);
        arrayTimeDef.SetData(mtimedef, pOriginInfo[iOrigNo].timeDefNum);

        mwArray arrayTimeBegin(1, 1, mxDOUBLE_CLASS);
        arrayTimeBegin.SetData(nTimeBegin, 1);

        QString frftfileName = pAcufName + "_" + pOriginInfo[iOrigNo].OriginName;
        OutfileNameList.append(frftfileName);

        QString frftOnefName = frftfileName+ ".TimeAmp";
        QString frftDatafName= frftfileName+ ".TimeErr";

        mwArray mwOnefName(frftOnefName.toStdString().c_str());
        mwArray mwDatafname(frftDatafName.toStdString().c_str());
        mwArray mwAcufName(pAcufName.toStdString().c_str());

        fprintf(fp, "mf0 is %f\n",mf0);
        fprintf(fp, "mtimedef is %f\n",mtimedef);
        fprintf(fp, "nTimeBegin is %f\n",nTimeBegin);
//        fprintf(fp, "mwOnefName is %s\n",frftOnefName.c_str());
//        fprintf(fp, "mwDatafname is %s\n",frftDatafName.c_str());
//        fprintf(fp, "mwAcufName is %s\n",pAcufName.c_str());

        //====返回值AAAAAA
		mwArray arrayRet(1, 1, mxDOUBLE_CLASS); 

//        FrftProcess(0, arrayRet, arrayN1, arrayFS, arrayFSDEV,arrayDistance, arrayB, arrayF0, arrayTimeDef, arrayTimeBegin,
//                    mwAcufName, mwOnefName, mwDatafname);

//        FrftProcess(arrayN1, arrayFS, arrayFSDEV, arrayDistance, arrayB, arrayF0, arrayTimeDef, arrayTime,
//                  mwAcufName, mwOnefName, mwDatafname);
        /// 20220731
        frftProcess(arrayN1, arrayFS, arrayDistance, arrayB, arrayTimeDef,mwAcufName);
    }
#endif
    return true;
}
