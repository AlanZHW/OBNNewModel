#include "abstractsegyproducer.h"



QFile *AbstractSegyProducer::m_logFile  = 0;

AbstractSegyProducer::AbstractSegyProducer()
{
    m_areaDataInfo = 0;
}

AbstractSegyProducer::~AbstractSegyProducer()
{
    if(m_logFile)
    {
        delete m_logFile;
    }

    if(m_areaDataInfo)
    {
        m_areaDataInfo->clearData();
        delete m_areaDataInfo;
        m_areaDataInfo = 0;
    }
}

//初始化参数和环境
bool AbstractSegyProducer::init()
{
    //1 初始化日志
    //qDebug() << initLog(m_Parameter.projectPath,m_Parameter.jobName);
    qDebug() <<"init args...";//log

//    //2 打开数据库
//    SqlFunctions *sqlFunc = SqlFunctions::instance();
//    bool ok = sqlFunc->openDataBase(m_Parameter.projectPath, m_Parameter.projectName);
//    if(!ok)
//    {
//        qDebug() << "open database error";
//        m_errString = "Open Database Error.";
//        return false;
//    }
    return true;
}

//开始运行
void AbstractSegyProducer::start()
{
    try{
        if(!init())
        {
            throw "Init ERROR";
        }
        if(!preProcesss())
        {
            throw "PreProcess ERROR";
        }
        if(!run())
        {
            throw "Run ERROR";
        }

    }
    catch(const char *exp)
    {
        qDebug()<<QString(exp)+",errString:"<<m_errString;
        finalize();
        exit(1);
    }

    //结束工作，关闭文件等---
    finalize();
    qDebug()<<"Finished success.";
}
bool AbstractSegyProducer::finalize()
{
//    //关闭数据库
//    SqlFunctions *sqlFunc = SqlFunctions::instance();
//    sqlFunc->closeDataBase();

    //2 日志记录完成
    qDebug()<<"finalize----"; //log
    return true;
}

bool AbstractSegyProducer::initLog(const QString &projPath,const QString &jobName)
{
    QString logPath = projPath+Dir_Separator+"work/";
    QString logFile = logPath+jobName+".log";
    //日志文件
    qDebug()<<"......log file:"<<logFile;
    m_logFile = new QFile(logFile);
    qDebug() << "调用qInstallMessageHandler函数";
    qInstallMessageHandler(AbstractSegyProducer::myMsgHandler);
    qDebug() << "创建log文件成功.";
    return true;
}

void AbstractSegyProducer::myMsgHandler(QtMsgType /*qtMsgType*/
                                        ,const QMessageLogContext &
                                        , const QString &context)
{
    m_logFile->open(QIODevice::WriteOnly|QIODevice::Append);
    qDebug() << "context = " << context;
    m_logFile->write(context.toLatin1().data(),context.size());
    m_logFile->write("\n",1);
    m_logFile->close();
}

bool AbstractSegyProducer::readSpsFiles()
{
    /// ====== 获取sps文件
    QStringList spsFiles = Area::spsFiles1(m_Parameter.projectPath,m_Parameter.areaName);
    if(spsFiles.size()<1)
    {
        m_errString = "SPS Files are not right";
        return false;
    }
    /// ====== 读取所有的sps文件
    if(m_areaDataInfo)
    {
        m_areaDataInfo->clearData();
    }
    else
    {
        m_areaDataInfo = new AreaDataInfo;
    }

    QString errString;
    int ok = gobs_sps_files_read(spsFiles,m_areaDataInfo,&errString);
    if(ok != 0)
    {
        m_errString = "read sps files failed";
        return false;
    }
    qDebug() << "gobs_sps_files_read success";
#if 0
        /// ====== 结果查看
        qDebug() << "recv lineNum = " << m_areaDataInfo->recvStationInfo->lineNum;
        for(int iLine = 0; iLine < m_areaDataInfo->recvStationInfo->lineNum; iLine ++)
        {
            qDebug() << "type = " << m_areaDataInfo->recvStationInfo->staLines[iLine].type
                     << " line = " << m_areaDataInfo->recvStationInfo->staLines[iLine].line
                     << " staNum = " << m_areaDataInfo->recvStationInfo->staLines[iLine].staNum;
            for(int iStaNum = 0; iStaNum < m_areaDataInfo->recvStationInfo->staLines[iLine].staNum; iStaNum ++)
            {
                qDebug() << "line = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].line
                         << " sp = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].sp
                         << " sidx = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].sidx
                         << " stat = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].stat
                         << " sdepth = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].sdepth
                         << " elev = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].elev
                         << " wtime = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].wtime
                         << " swdep = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].swdep
                         << " x = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].x
                         << " y = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].y
                         << " del = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].del
                         << " year = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].year
                         << " month = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].month
                         << " day = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].day
                         << " hour = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].hour
                         << " minute = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].minute
                         << " sec = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].sec
                         << " millisecond = " << m_areaDataInfo->recvStationInfo->staLines[iLine].stations[iStaNum].millisecond;
            }
        }

        qDebug() << "shot lineNum = " << m_areaDataInfo->shotStationInfo->lineNum;
        for(int iShot = 0; iShot < m_areaDataInfo->shotStationInfo->lineNum; iShot ++)
        {
            qDebug() << "type = " << m_areaDataInfo->shotStationInfo->staLines[iShot].type
                     << " line = " << m_areaDataInfo->shotStationInfo->staLines[iShot].line
                     << " staNum = " << m_areaDataInfo->shotStationInfo->staLines[iShot].staNum;
            for(int iStaNum = 0; iStaNum < m_areaDataInfo->shotStationInfo->staLines[iShot].staNum; iStaNum ++)
            {
                qDebug() << "line = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].line
                         << " sp = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].sp
                         << " sidx = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].sidx
                         << " stat = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].stat
                         << " sdepth = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].sdepth
                         << " elev = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].elev
                         << " wtime = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].wtime
                         << " swdep = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].swdep
                         << " x = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].x
                         << " y = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].y
                         << " del = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].del
                         << " year = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].year
                         << " month = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].month
                         << " day = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].day
                         << " hour = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].hour
                         << " minute = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].minute
                         << " sec = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].sec
                         << " millisecond = " << m_areaDataInfo->shotStationInfo->staLines[iShot].stations[iStaNum].millisecond;
            }
        }
#endif

    //    //结果查看
    //    RelationInfo *relationInfo = m_areaDataInfo->relationInfo;
    //    Relation *realtions        = relationInfo->relations;
    //    for(int i = 0; i < relationInfo->relationNum; i ++)
    //    {
    //        qDebug()<<"shot line:"      << realtions[i].shotLine
    //                <<"shot no:"        << realtions[i].ep
    //                <<"first trace:"    << realtions[i].firstTrace
    //                <<"last trace:"     << realtions[i].lastTrace
    //                <<"recv line:"      << realtions[i].recvLine
    //                <<"first station:"  << realtions[i].firstRecv
    //                <<"last station:"   << realtions[i].lastRecv;
    //    }
    return true;
}

