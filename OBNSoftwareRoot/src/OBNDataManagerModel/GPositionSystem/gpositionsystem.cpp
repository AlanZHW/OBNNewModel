#include "gpositionsystem.h"
#include "ui_gpositionsystem.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTextBrowser>

#include <QDebug>

#include "gserialport.h"
#include "datamanager.h"
#include "deckunit.h"
#include "positionchart.h"
#include "postioncontrols.h"

GPositionSystem::GPositionSystem(QWidget *parent) :
    QDialog(parent),flag(0),
    ui(new Ui::GPositionSystem)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("定位系统"));

    createWg();
    connect(m_gSerialPort,&GSerialPort::recvGpsCord,this,&GPositionSystem::slotRecvGpsCord);
    connect(m_gSerialPort,&GSerialPort::recvReadGPSInformation, this, &GPositionSystem::showText);
    connect(m_gSerialPort, SIGNAL(signal_recv_sendsignal()), this, SLOT(slotRecvSendSignal()));

    connect(m_deckUnit, &DeckUnit::signal_recv_Delaytime,       this, &GPositionSystem::slotRecvDelaytime);
    connect(m_deckUnit, &DeckUnit::signal_Sondary_recv_range,   this, &GPositionSystem::slotRecvSondaryrange);
    connect(m_deckUnit, &DeckUnit::signal_recv_sendsignal,      this, &GPositionSystem::slotRecvSendSignal);
    connect(m_deckUnit, &DeckUnit::signal_recv_clicked_start,   this, &GPositionSystem::slotRecvClickedStart);
    connect(m_deckUnit, &DeckUnit::signal_recv_coordsystem,     this, &GPositionSystem::slot_recv_coordsystem);
    connect(m_deckUnit, &DeckUnit::signal_recv_coordAfterCalculator,this, &GPositionSystem::slot_recv_coordAfterCalculator);
    connect(m_deckUnit, &DeckUnit::signal_send_OBS_info,        this, &GPositionSystem::slot_OBS_info);
    connect(m_deckUnit, &DeckUnit::signal_stop_information,     this, &GPositionSystem::slot_stop_deckUnit);
    testData();
    irecindex=0;
    sondaryflag=-1;
}

GPositionSystem::~GPositionSystem()
{
    delete ui;
}

void GPositionSystem::showText(const QString &text)
{
//    if(m_textBrowser->isBackwardAvailable())
//    {
//        m_textBrowser->clear();
//    }
//    m_textBrowser->append(text);
//    m_TextEditGPS->clear();
    m_TextEditGPS->append(text);
}

void GPositionSystem::slot_OBS_info(const QString& pOBSMin, const QString& pOBSMax)
{
    mOBSInfo = pOBSMin+pOBSMax;
}

void GPositionSystem::slot_stop_deckUnit()
{
    irecindex = 0;
    m_systemDis->initWindows();
}

/// 接收到坐标系原点坐标和船轨迹的圆的半径
void GPositionSystem::slot_recv_coordsystem(const double& pX0, const double& pY0, const double& pZ0)
{
    m_systemDis->setCoordSystemInfo(pX0, pY0, pZ0);

//    double XGPS = 3000;
//    double YGPS = 5000;
//    double ZGPS = 10;
//    m_systemDis->setGOBSCoord(XGPS, YGPS, ZGPS);

//    double XGPS0 = 5000;
//    double YGPS0 = 3000;
//    m_systemDis->setGOBSCoord(XGPS0, YGPS0, ZGPS);

//    double XGPS1 = 3000;
//    double YGPS1 = 3000;
//    m_systemDis->setGOBSCoord(XGPS1, YGPS1, ZGPS);

//    double XGPS2 = 5000;
//    double YGPS2 = 5000;
//    m_systemDis->setGOBSCoord(XGPS2, YGPS2, ZGPS);
}

void GPositionSystem::slot_recv_coordAfterCalculator(const double& pX, const double& pY, const double& pZ)
{
    QString strposX,strposY,strposZ;
    m_systemDis->setCoordAfterCalculator(pX, pY, pZ);
    FILE *fp = fopen("./SoundcommReceive.txt", "a+");
//    strposX=QString::number(pX,'f',2);
//    strposY=QString::number(pY,'f',2);
//    strposZ=QString::number(pZ,'f',2);
    fprintf(fp,"SoundComm receive Pos:X = %f \t Y = %f \t z = %f\n",pX,pY,pZ);
    fclose(fp);
}

void GPositionSystem::slot_recv_loadinfo(QString loadinfo)
{
    m_TextEditDuck->append(loadinfo);
}

void GPositionSystem::startPostion()
{
    //打开串口
    if(!m_gSerialPort->open())
    {
        QMessageBox::critical(this,QStringLiteral("打开串口"),QStringLiteral("打开串口%1失败！")
                              .arg( m_gSerialPort->serialPort()->portName()));
    }
    else
    {
        QMessageBox::information(this, QStringLiteral("打开串口"), QStringLiteral("打开串口成功."));
    }
}

void GPositionSystem::stopPostion()
{
    m_gSerialPort->close();
}

void GPositionSystem::slotRecvDelaytime(const int& pDelaytime, const double& pZValue, const double& pX0, const double& pY0)
{
    qDebug()<<__FILE__<<"\t"<<__LINE__;
    FILE *fp = fopen("./log.txt", "a+");
    //==当前函数通过GPS坐标和时差信息计算最新的坐标
    mDelaytimes.append(pDelaytime);

//    if(0 == mGpsCords.count())
//    {
//        return ;
//    }
//    mGobsCords.clear();
//    for(int iCord = 0; iCord < mGpsCords.count(); iCord ++)
//    {
//        if(iCord%4 ==0)
//        {
//            GobsCoord gobs_cord;
//            gobs_cord.x = mGpsCords.at(0).x+iCord*100;
//            gobs_cord.y = mGpsCords.at(0).y+rand()%10000;
//            mGobsCords.append(gobs_cord);
//        }
//    }
//    m_positionChart->setData(mGpsCords, mGobsCords);
    qDebug() << "count is:" << mGpsCords.count() << "\t m_velocityFName = " << m_velocityFName;

//     if(m_velocityFName.isEmpty())
//     {
//         GpsCoord nGPSCoordMid;
//         nGPSCoordMid.x = (mGPSCoord.x+mGpsCords[mGpsCords.length()-1].x)*0.5f;
//         nGPSCoordMid.y = (mGPSCoord.y+mGpsCords[mGpsCords.length()-1].y)*0.5f;

            GPSInfo nGPSCoordInfo;
            qDebug() << "1>>>x = " <<  QString("%1").arg(mGPSCoord.x, 0, 'f', 4)<< "\t y = " << QString("%1").arg(mGPSCoord.y, 0, 'f', 4);
            qDebug() << "2>>>x = " << QString("%1").arg(mGpsCords[mGpsCords.length()-1].x, 0, 'f', 4) << "\t y = " << QString("%1").arg(mGpsCords[mGpsCords.length()-1].y, 0, 'f', 4);
            nGPSCoordInfo.x = (mGPSCoord.x+mGpsCords[mGpsCords.length()-1].x)*0.5f;
            nGPSCoordInfo.y = (mGPSCoord.y+mGpsCords[mGpsCords.length()-1].y)*0.5f;
            nGPSCoordInfo.z = pZValue;
            nGPSCoordInfo.t = pDelaytime/10.0;
            irecindex++;
            /// 写log文件
            fprintf(fp, "OBS:%s \t No= %d \t x = %f \t y = %f \t z = %f \t Delaytime = %f\n", mOBSInfo.toStdString().c_str(), irecindex,nGPSCoordInfo.x, nGPSCoordInfo.y, nGPSCoordInfo.z,nGPSCoordInfo.t);

            QString CoordInfo = "X:"+QString("%1").arg(nGPSCoordInfo.x, 0, 'f', 4)+"\t Y:"+QString("%1").arg(nGPSCoordInfo.y, 0, 'f', 4);
            showText(CoordInfo);

            double XGPS = nGPSCoordInfo.x;
            double YGPS = nGPSCoordInfo.y;
            m_systemDis->setCoordforGPS(XGPS, YGPS);

//         mGPSCoordVector.append(nGPSCoordMid);
//        if(fabs(nGPSCoordInfo.x-pX0)<=pZValue*1.7 && fabs(nGPSCoordInfo.y-pY0)<=pZValue*1.7)
//        {
           qDebug() << "x,y coord>dh*1.7";
            if(nGPSCoordInfo.x < pX0 && nGPSCoordInfo.y >= pY0)
            {
                mGPSCoordVectorLeftUp.append(nGPSCoordInfo);
            }
            else if(nGPSCoordInfo.x >= pX0 && nGPSCoordInfo.y >= pY0)
            {
                mGPSCoordVectorRightUp.append(nGPSCoordInfo);
            }
            else if(nGPSCoordInfo.x < pX0 && nGPSCoordInfo.y < pY0)
            {
                mGPSCoordVectorLeftDown.append(nGPSCoordInfo);
            }
            else if(nGPSCoordInfo.x >= pX0 && nGPSCoordInfo.y < pY0)
            {
                mGPSCoordVectorRightDown.append(nGPSCoordInfo);
            }
//        }
//     }
//     else
//     {
//         GpsCoord nGPSCoordMid1;
//         nGPSCoordMid1.x =447731.39 ;
//         nGPSCoordMid1.y =4426040.71 ;
//         mGPSCoordVector.append(nGPSCoordMid1);

//         GpsCoord nGPSCoordMid2;
//         nGPSCoordMid2.x =448830.03 ;
//         nGPSCoordMid2.y =4426076.21 ;
//         mGPSCoordVector.append(nGPSCoordMid2);

//         GpsCoord nGPSCoordMid3;
//         nGPSCoordMid3.x =448817.68 ;
//         nGPSCoordMid3.y =4425152.69 ;
//         mGPSCoordVector.append(nGPSCoordMid3);
//    }
qDebug()<<__FILE__<<"\t"<<__LINE__;


    fclose(fp);

#if 0
    if(mGPSCoordVector.count() == 3)
    {
        QString logFName = "./out.log";
        FILE *fpLog = fopen(logFName.toStdString().c_str(), "a+");

        /// 此处调用解方程
        double** n_pointXYZT = new double*[3];
        for(int iDt = 0; iDt < 3; iDt ++)
        {
            n_pointXYZT[iDt] = new double[4];
        }

        for(int iCoord = 0; iCoord < mGPSCoordVector.count(); iCoord ++)
        {
            n_pointXYZT[iCoord][0] = mGPSCoordVector[iCoord].x;
            n_pointXYZT[iCoord][1] = mGPSCoordVector[iCoord].y;
            n_pointXYZT[iCoord][2] = pZValue;

            fprintf(fpLog, "%f\t%f\t%f\t%f\n", n_pointXYZT[iCoord][0], n_pointXYZT[iCoord][1], n_pointXYZT[iCoord][2], (double)(mDelaytimes[iCoord]/1000.0f));
//            n_pointXYZT[iCoord][3] = (double)(mDelaytimes[iCoord]/1000.0f);
        }


        if(m_velocityFName.isEmpty())
        {
            for(int iDelayTime = 0; iDelayTime <mDelaytimes.count(); iDelayTime ++)
            {
                n_pointXYZT[iDelayTime][3] = (double)(mDelaytimes[iDelayTime]/1000.0f);
            }
        }
        else
        {

            n_pointXYZT[0][3] = 1.98745323275349;
            n_pointXYZT[1][3] = 1.97941038366552;
            n_pointXYZT[2][3] = 1.97375083248932;
        }


qDebug()<<__FILE__<<"\t"<<__LINE__;

        double x=1.1;
        double y=1.1;
        double h=0.0;
        if(m_velocityFName.isEmpty())
        {

            testPostion_AB(n_pointXYZT, &x, &y, &h);
        }
        else
        {
            QVector <double> tdata{n_pointXYZT[0][3],n_pointXYZT[1][3],n_pointXYZT[2][3]};
            auto min=std::min_element(std::begin(tdata),std::end(tdata));
            double tmin=*min;

            h_low=MinDepth(tmin, soundspeed);
            if(0.0 == h_low)
            {
                return ;
            }
            h_high=20;
            Postion_AB(soundspeed, n_pointXYZT, h_high, h_low, &x, &y, &h);
        }
        fprintf(fpLog, "%f\t%f\t%f\n", x, y, h);

        GobsCoord nGOBSCoord;
        nGOBSCoord.x = x;
        nGOBSCoord.y = y;
        nGOBSCoord.z = h;
        mGobsCords.append(nGOBSCoord);
qDebug()<<"flag"<<flag;
        m_positionChart->setData(mGPSCoordVector,mGobsCords);

qDebug()<<__FILE__<<"\t"<<"x"<<QString("%1").arg(x, 0, 'f', 4)<<"y"<<QString("%1").arg(y, 0, 'f', 4)<<"h"<<h;
        for(int iDt = 0; iDt < 3; iDt ++)
        {
            delete [] n_pointXYZT[iDt];
        }
        delete [] n_pointXYZT;
        mDelaytimes.clear();
        mGPSCoordVector.clear();
        fclose(fpLog);
    }
#endif
}
void GPositionSystem::slotRecvSondaryrange(const float& pRange, const double& pZValue, const double& pX0, const double& pY0)
{
    qDebug()<<__FILE__<<"\t"<<__LINE__;
    FILE *fp = fopen("./Sonardynelog.txt", "a+");
    //==当前函数通过GPS坐标和时差信息计算最新的坐标
    mRange.append(pRange);
    sondaryflag=1;
    qDebug() << "count is:" << mGpsCords.count() << "\t m_velocityFName = " << m_velocityFName;

    GPSInfo nGPSCoordInfo;
    qDebug() << "1>>>x = " <<  QString("%1").arg(mGPSCoord.x, 0, 'f', 4)<< "\t y = " << QString("%1").arg(mGPSCoord.y, 0, 'f', 4);
    qDebug() << "2>>>x = " << QString("%1").arg(mGpsCords[mGpsCords.length()-1].x, 0, 'f', 4) << "\t y = " << QString("%1").arg(mGpsCords[mGpsCords.length()-1].y, 0, 'f', 4);
    nGPSCoordInfo.x = (mGPSCoord.x+mGpsCords[mGpsCords.length()-1].x)*0.5f;
    nGPSCoordInfo.y = (mGPSCoord.y+mGpsCords[mGpsCords.length()-1].y)*0.5f;
    nGPSCoordInfo.z = pZValue;
    nGPSCoordInfo.t = pRange;
    irecindex++;
    /// 写log文件
    fprintf(fp, "Sonardyne:%s \t No= %d \t x = %f \t y = %f \t z = %f \t Range = %f\n", mOBSInfo.toStdString().c_str(), irecindex,nGPSCoordInfo.x, nGPSCoordInfo.y, nGPSCoordInfo.z,nGPSCoordInfo.t);

    QString CoordInfo = "X:"+QString("%1").arg(nGPSCoordInfo.x, 0, 'f', 4)+"\t Y:"+QString("%1").arg(nGPSCoordInfo.y, 0, 'f', 4);
    showText(CoordInfo);

    double XGPS = nGPSCoordInfo.x;
    double YGPS = nGPSCoordInfo.y;
    m_systemDis->setCoordforGPS(XGPS, YGPS);

    qDebug() << "x,y coord>dh*1.7";
    if(nGPSCoordInfo.x < pX0 && nGPSCoordInfo.y >= pY0)
    {
        mGPSCoordVectorLeftUp.append(nGPSCoordInfo);
    }
    else if(nGPSCoordInfo.x >= pX0 && nGPSCoordInfo.y >= pY0)
    {
        mGPSCoordVectorRightUp.append(nGPSCoordInfo);
    }
    else if(nGPSCoordInfo.x < pX0 && nGPSCoordInfo.y < pY0)
    {
        mGPSCoordVectorLeftDown.append(nGPSCoordInfo);
    }
    else if(nGPSCoordInfo.x >= pX0 && nGPSCoordInfo.y < pY0)
    {
        mGPSCoordVectorRightDown.append(nGPSCoordInfo);
    }
    fclose(fp);
}
double GPositionSystem::MinDepth(double t,QVector<QVector<float> > V_speed)
{
    double h_low = 0.0;
    int ileng=V_speed.length();
    for(int i=0;i<ileng;i++)
    {
        t=t-V_speed[i][1]/V_speed[i][0];
        if (t<=0)
        {
            h_low=V_speed[i][2];
            return h_low;
        }
    }
    return h_low;
}

void GPositionSystem::slotRecvSendSignal()
{
    qDebug() << __FILE__ << "\t" << __LINE__ << "\t count is:" << mGpsCords.count();
    if(0 == mGpsCords.count())
        return;
    mGPSCoord.x        = mGpsCords[mGpsCords.length()-1].x;
    mGPSCoord.y        = mGpsCords[mGpsCords.length()-1].y;
    mGPSCoord.gpsX     = mGpsCords[mGpsCords.length()-1].gpsX;
    mGPSCoord.gpsY     = mGpsCords[mGpsCords.length()-1].gpsY;
    mGPSCoord.utc_sec  = mGpsCords[mGpsCords.length()-1].utc_sec;
}

void GPositionSystem::slotRecvClickedStart()
{
    qDebug() << "mGPSCoordVectorLeftUp ... " << mGPSCoordVectorLeftUp.count();
    qDebug() << "mGPSCoordVectorRightUp ... " << mGPSCoordVectorRightUp.count();
    qDebug() << "mGPSCoordVectorLeftDown ... " << mGPSCoordVectorLeftDown.count();
    qDebug() << "mGPSCoordVectorRightDown ... " << mGPSCoordVectorRightDown.count();

    FILE *fp;
//    mGPSCoordVectorLeftUp.clear();
//    GPSInfo nCoord1,nCoord2,nCoord3,nCoord4;
//    nCoord1.x =422348.533601 ;
//    nCoord1.y = 4161451.444501;
//    nCoord1.z = 2;
//    nCoord1.t =237.1 ;
//    mGPSCoordVectorLeftUp.append(nCoord1);
//    nCoord2.x =422587.019800 ;
//    nCoord2.y = 4161601.716930 ;
//    nCoord2.z = 2;
//    nCoord2.t =423.3;
//    mGPSCoordVectorRightUp.append(nCoord2);
//    nCoord3.x =422194.058736;
//    nCoord3.y = 4161051.742684;
//    nCoord3.z = 2;
//    nCoord3.t =522.5;
//    mGPSCoordVectorLeftDown.append(nCoord3);
//    nCoord4.x =422796.766745;
//    nCoord4.y = 4161131.255747 ;
//    nCoord4.z = 2;
//    nCoord4.t =543.4;
//    mGPSCoordVectorRightDown.append(nCoord4);
//    GPSInfo nCoord11,nCoord12,nCoord13,nCoord14;
//    nCoord11.x =422352.9562 ;
//    nCoord11.y = 4161448.305;
//    nCoord11.z = 2;
//    nCoord11.t =228.7 ;
//    mGPSCoordVectorLeftUp.append(nCoord11);
//    nCoord12.x =422592.6404 ;
//    nCoord12.y = 4161601.503 ;
//    nCoord12.z = 2;
//    nCoord12.t =425;
//    mGPSCoordVectorRightUp.append(nCoord12);
//    nCoord13.x =422198.6569;
//    nCoord13.y = 4161058.874;
//    nCoord13.z = 2.2;
//    nCoord13.t =512.4;
//    mGPSCoordVectorLeftDown.append(nCoord13);
//    nCoord14.x =422822.773;
//    nCoord14.y = 4161128.722 ;
//    nCoord14.z = 2.3;
//    nCoord14.t =574.1;
//    mGPSCoordVectorRightDown.append(nCoord14);

    /// 开辟内存
    double** n_pointXYZT = new double*[4];
    for(int iDt = 0; iDt < 4; iDt ++)
    {
        n_pointXYZT[iDt] = new double[4];
    }
    if(sondaryflag==1)
    {
        fp = fopen("./Sonardynelog.txt", "a+");
    }
    else{
        fp = fopen("./log.txt", "a+");
    }


    /// 获取数据后开始解算,并将解算的结果保存下来
    /// 三个象限数值计算
    if(mGPSCoordVectorLeftUp.count() != 0 && mGPSCoordVectorRightUp.count() != 0 && mGPSCoordVectorLeftDown.count() != 0)
    {
        int countMin = mGPSCoordVectorLeftUp.count();
        countMin = MINI(countMin, mGPSCoordVectorRightUp.count());
        countMin = MINI(countMin, mGPSCoordVectorLeftDown.count());
        qDebug()<<"LeftUp-RightUp-LeftDown,countMin:"<<countMin;
        ///
        for(int iVector = 0; iVector < countMin; ++ iVector)
        {
            QVector<GpsCoord>  nGPSCoordVector;
            QVector<GobsCoord> nGobsCoordVector;
            calculat3Coord(iVector, n_pointXYZT, mGPSCoordVectorLeftUp, mGPSCoordVectorRightUp, mGPSCoordVectorLeftDown, nGPSCoordVector, nGobsCoordVector);
            m_GPSCoordList.append(nGPSCoordVector);
            m_GOBSCoordList.append(nGobsCoordVector);
        }
    }
    if(mGPSCoordVectorLeftUp.count() != 0 && mGPSCoordVectorRightUp.count() != 0 && mGPSCoordVectorRightDown.count() != 0)
    {
        int countMin = mGPSCoordVectorLeftUp.count();
        countMin = MINI(countMin, mGPSCoordVectorRightUp.count());
        countMin = MINI(countMin, mGPSCoordVectorRightDown.count());
        qDebug()<<"LeftUp-RightUp-RightDown,countMin:"<<countMin;
        ///
        for(int iVector = 0; iVector < countMin; ++ iVector)
        {
            QVector<GpsCoord>  nGPSCoordVector;
            QVector<GobsCoord> nGobsCoordVector;
            calculat3Coord(iVector, n_pointXYZT, mGPSCoordVectorLeftUp, mGPSCoordVectorRightUp, mGPSCoordVectorRightDown, nGPSCoordVector, nGobsCoordVector);
            m_GPSCoordList.append(nGPSCoordVector);
            m_GOBSCoordList.append(nGobsCoordVector);
        }
    }
    if(mGPSCoordVectorRightUp.count() != 0 && mGPSCoordVectorLeftDown.count() != 0 && mGPSCoordVectorRightDown.count() != 0)
    {
        int countMin = mGPSCoordVectorRightUp.count();
        countMin = MINI(countMin, mGPSCoordVectorLeftDown.count());
        countMin = MINI(countMin, mGPSCoordVectorRightDown.count());
        qDebug()<<"RightUp-LeftDown-RightDown,countMin:"<<countMin;
        ///
        for(int iVector = 0; iVector < countMin; ++ iVector)
        {
            QVector<GpsCoord>  nGPSCoordVector;
            QVector<GobsCoord> nGobsCoordVector;
            calculat3Coord(iVector, n_pointXYZT, mGPSCoordVectorRightUp, mGPSCoordVectorLeftDown, mGPSCoordVectorRightDown, nGPSCoordVector, nGobsCoordVector);
            m_GPSCoordList.append(nGPSCoordVector);
            m_GOBSCoordList.append(nGobsCoordVector);
        }
    }
    if(mGPSCoordVectorLeftUp.count() != 0 && mGPSCoordVectorLeftDown.count() != 0 && mGPSCoordVectorRightDown.count() != 0)
    {
        int countMin = mGPSCoordVectorLeftUp.count();
        countMin = MINI(countMin, mGPSCoordVectorLeftDown.count());
        countMin = MINI(countMin, mGPSCoordVectorRightDown.count());
        qDebug()<<"LeftUp-LeftDown-RightDown,countMin:"<<countMin;
        ///
        for(int iVector = 0; iVector < countMin; ++ iVector)
        {
            QVector<GpsCoord>  nGPSCoordVector;
            QVector<GobsCoord> nGobsCoordVector;
            calculat3Coord(iVector, n_pointXYZT, mGPSCoordVectorLeftUp, mGPSCoordVectorLeftDown, mGPSCoordVectorRightDown, nGPSCoordVector, nGobsCoordVector);
            m_GPSCoordList.append(nGPSCoordVector);
            m_GOBSCoordList.append(nGobsCoordVector);
        }
    }

    /// 四个象限数值计算
    int nCountMin = mGPSCoordVectorLeftUp.count();
    nCountMin = MINI(mGPSCoordVectorRightUp.count(), nCountMin);
    nCountMin = MINI(mGPSCoordVectorLeftDown.count(), nCountMin);
    nCountMin = MINI(mGPSCoordVectorRightDown.count(), nCountMin);
    for(int iCount = 0; iCount < nCountMin; iCount ++)
    {
        QVector<GpsCoord>  nGPSCoordVector;
        QVector<GobsCoord> nGobsCoordVector;
        calculat4Coord(iCount, n_pointXYZT, mGPSCoordVectorLeftUp, mGPSCoordVectorRightUp, mGPSCoordVectorLeftDown, mGPSCoordVectorRightDown, nGPSCoordVector, nGobsCoordVector);
//        m_GPSCoordList.append(nGPSCoordVector);
//        m_GOBSCoordList.append(nGobsCoordVector);
        m_GPSCoordList4.append(nGPSCoordVector);
        m_GOBSCoordList4.append(nGobsCoordVector);
    }
    /// 释放空间
    for(int iDt = 0; iDt < 4; iDt ++)
    {
        delete [] n_pointXYZT[iDt];
    }
    delete [] n_pointXYZT;


    if(0 == m_GOBSCoordList.count())
    {
        QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("条件不满足。"));
        return;
    }
    qDebug()<<__FILE__ << "\t" <<" m_GPSCoordList.count():"<< m_GPSCoordList.count() << "\t" << m_GPSCoordList[0].count() << "\t"<< m_GOBSCoordList[0].count();

    /// 打印结果
//    qDebug()<<QStringLiteral("三个象限解算结果\n");
//    fprintf(fp, QStringLiteral("三个象限解算结果\n"));
    for(int lVec = 0; lVec < m_GPSCoordList.count(); ++ lVec)
    {
        QString CoordInfo = "debug ";
        for(int iLst = 0; iLst < m_GPSCoordList[lVec].count(); iLst ++)
        {
            CoordInfo += QString("%1").arg(m_GPSCoordList[lVec].at(iLst).x, 0, 'f', 4) +"\t" +\
                         QString("%1").arg(m_GPSCoordList[lVec].at(iLst).y, 0, 'f', 4)+"\t";

        }
        for(int iLst = 0; iLst < m_GOBSCoordList[lVec].count(); ++ iLst)
        {
            CoordInfo += QString("%1").arg(m_GOBSCoordList[lVec].at(iLst).x, 0, 'f', 4) +"\t"+ \
                         QString("%1").arg(m_GOBSCoordList[lVec].at(iLst).y, 0, 'f', 4) +"\t"+\
                         QString("%1").arg(m_GOBSCoordList[lVec].at(iLst).z, 0, 'f', 4);
        }
        qDebug() << "CoordInfo === " << CoordInfo;
        fprintf(fp, "%s\n", CoordInfo.toStdString().c_str());
        showText(CoordInfo);
    }
//    fprintf(fp, "四个象限解算结果\n");
    for(int lVec = 0; lVec < m_GPSCoordList4.count(); ++ lVec)
    {
        QString CoordInfo = "debug ";
        for(int iLst = 0; iLst < m_GPSCoordList4[lVec].count(); iLst ++)
        {
            CoordInfo += QString("%1").arg(m_GPSCoordList4[lVec].at(iLst).x, 0, 'f', 4) +"\t" +\
                         QString("%1").arg(m_GPSCoordList4[lVec].at(iLst).y, 0, 'f', 4)+"\t";

        }
        for(int iLst = 0; iLst < m_GOBSCoordList4[lVec].count(); ++ iLst)
        {
            CoordInfo += QString("%1").arg(m_GOBSCoordList4[lVec].at(iLst).x, 0, 'f', 4) +"\t"+ \
                         QString("%1").arg(m_GOBSCoordList4[lVec].at(iLst).y, 0, 'f', 4) +"\t"+\
                         QString("%1").arg(m_GOBSCoordList4[lVec].at(iLst).z, 0, 'f', 4);
        }
        qDebug() << "CoordInfo === " << CoordInfo;
        fprintf(fp, "%s\n", CoordInfo.toStdString().c_str());
        showText(CoordInfo);
    }
//    double 4pointoptimalCoordx,4pointoptimalCoordy,4pointoptimalCoordz;
//    4pointoptimalCoordx=MedianFilter(m_GOBSCoordList, m_GOBSCoordList.count());

    /// 三个象限获取最优结果
    double nX, nY, nZ;
    getOptimalValue(m_GOBSCoordList, nX, nY, nZ);
    m_systemDis->setGOBSCoord(nX, nY, nZ);
    QString nOptimalCoord = QStringLiteral("最优结果:") + QString("%1").arg(nX, 0, 'f', 4) + QString("%1").arg(nY, 0, 'f', 4) + QString("%1").arg(nZ, 0, 'f', 4);
    showText(nOptimalCoord);

    fprintf(fp, "three point option solve:\n");
    QString logInfo = QString("%1").arg(nX, 0, 'f', 4) + "\t" + QString("%1").arg(nY, 0, 'f', 4) + QString("%1").arg(nZ, 0, 'f', 4);
    fprintf(fp, "%s\n", logInfo.toStdString().c_str());


    /// 四个象限获取最优结果
    double nX4, nY4, nZ4;
    MedianFilter(m_GOBSCoordList4, nX4, nY4, nZ4);

    fprintf(fp, "four point option solve:\n");
    logInfo = QString("%1").arg(nX4, 0, 'f', 4) + "\t" + QString("%1").arg(nY4, 0, 'f', 4) + "\t"+QString("%1").arg(nZ4, 0, 'f', 4);
    fprintf(fp, "%s\n", logInfo.toStdString().c_str());

    m_TableGPSInfo->clearContents();
    /// 设置表格行数,并填写相关信息
    int rowCount = m_GPSCoordList4.count();
    m_TableGPSInfo->setRowCount(rowCount);
    int nRowNO = 0;
    for(int iList = 0; iList < m_GPSCoordList4.count(); ++ iList)
    {
        m_TableGPSInfo->setItem(nRowNO, 0, new QTableWidgetItem(QString::number(nRowNO)));
        m_TableGPSInfo->setItem(nRowNO, 1, new QTableWidgetItem(QString("%1").arg(m_GPSCoordList4[iList][0].x, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 2, new QTableWidgetItem(QString("%1").arg(m_GPSCoordList4[iList][0].y, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 3, new QTableWidgetItem(QString("%1").arg(m_GPSCoordList4[iList][1].x, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 4, new QTableWidgetItem(QString("%1").arg(m_GPSCoordList4[iList][1].y, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 5, new QTableWidgetItem(QString("%1").arg(m_GPSCoordList4[iList][2].x, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 6, new QTableWidgetItem(QString("%1").arg(m_GPSCoordList4[iList][2].y, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 7, new QTableWidgetItem(QString("%1").arg(m_GPSCoordList4[iList][3].x, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 8, new QTableWidgetItem(QString("%1").arg(m_GPSCoordList4[iList][3].y, 0, 'f', 4)));

        m_TableGPSInfo->setItem(nRowNO, 9, new QTableWidgetItem(QString("%1").arg(m_GOBSCoordList4[iList][0].x, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 10, new QTableWidgetItem(QString("%1").arg(m_GOBSCoordList4[iList][0].y, 0, 'f', 4)));
        m_TableGPSInfo->setItem(nRowNO, 11, new QTableWidgetItem(QString("%1").arg(m_GOBSCoordList4[iList][0].z, 0, 'f', 4)));
        ++ nRowNO;
    }

    /// 释放内存
    mGPSCoordVectorLeftUp.clear();
    mGPSCoordVectorRightUp.clear();
    mGPSCoordVectorLeftDown.clear();
    mGPSCoordVectorRightDown.clear();
    for(int iListGOBS = 0; iListGOBS < m_GOBSCoordList.count(); iListGOBS ++)
    {
        m_GOBSCoordList[iListGOBS].clear();
    }
    m_GOBSCoordList.clear();
    for(int iListGPS = 0; iListGPS < m_GPSCoordList.count(); iListGPS ++)
    {
        m_GPSCoordList[iListGPS].clear();
    }
    m_GPSCoordList.clear();
    for(int iListGOBS = 0; iListGOBS < m_GPSCoordList4.count(); iListGOBS ++)
    {
        m_GPSCoordList4[iListGOBS].clear();
    }
    m_GPSCoordList4.clear();
    for(int iListGPS = 0; iListGPS < m_GOBSCoordList4.count(); iListGPS ++)
    {
        m_GOBSCoordList4[iListGPS].clear();
    }
    m_GOBSCoordList4.clear();

    fclose(fp);
    QMessageBox::information(this, QStringLiteral("最优结果"), QStringLiteral("最优结果为: X = ")+QString("%1").arg(nX4, 0, 'f', 4) + " Y = " +
                             QString("%1").arg(nY4, 0, 'f', 4) + " Z = " + QString("%1").arg(nZ4, 0, 'f', 4));
}

void GPositionSystem::MedianFilter(QVector<QVector<GobsCoord> >& data, double& pX, double& pY, double& pZ)
{
    for(int iList1 = 0; iList1 < data.count(); iList1 ++)
    {
        for(int iList2 = 0; iList2 < data[iList1].count(); iList2 ++)
        {
            qDebug() << "x = " << QString("%1").arg(data[iList1][iList2].x, 0, 'f', 4)
                     << "\t y = " << QString("%1").arg(data[iList1][iList2].y, 0, 'f', 4)
                     << "\t z = " << QString("%1").arg(data[iList1][iList2].z, 0, 'f', 4);
        }
    }

    int iGOBSNum = 0;
    for(int iList = 0; iList < data.count(); iList ++)
    {
        iGOBSNum += data[iList].count();
    }
    /// 当只有一个数值情况
    if(1 == iGOBSNum)
    {
        pX = data[0][0].x;
        pY = data[0][0].y;
        return;
    }
    /// 求X和Y的数值之和,且获取到最大值和最小值
    double XSumNum = 0.0f, YSumNum = 0.0f, ZSumNum = 0.0f;
    double XMinNum = data[0][0].x, YMinNum = data[0][0].y, ZMinNum = data[0][0].z;
    double XMaxNum = data[0][0].x, YMaxNum = data[0][0].y, ZMaxNum = data[0][0].z;
    int   dataNum = 0;
    for(int iList1 = 0; iList1 < data.count(); iList1 ++)
    {
        for(int iList2 = 0; iList2 < data[iList1].count(); iList2 ++)
        {
            dataNum += 1;
            XMinNum = MINI(XMinNum, data[iList1][iList2].x);
            YMinNum = MINI(YMinNum, data[iList1][iList2].y);
            ZMinNum = MINI(XMinNum, data[iList1][iList2].z);

            XMaxNum = MAXI(XMaxNum, data[iList1][iList2].x);
            YMaxNum = MAXI(YMaxNum, data[iList1][iList2].y);
            ZMaxNum = MAXI(ZMaxNum, data[iList1][iList2].z);

            XSumNum += data[iList1][iList2].x;
            YSumNum += data[iList1][iList2].y;
            ZSumNum += data[iList1][iList2].z;
        }
    }
    if(2 == dataNum)
    {
        pX = XSumNum/dataNum;
        pY = YSumNum/dataNum;
        pZ = ZSumNum/dataNum;
    }
    else
    {
        /// X和Y之和减去最大和最小值
        XSumNum -= (XMinNum + XMaxNum);
        YSumNum -= (YMinNum + YMaxNum);
        ZSumNum -= (ZMinNum + ZMaxNum);
        double dbDataNum = (double)(dataNum-2);
        pX = XSumNum/dbDataNum;
        pY = YSumNum/dbDataNum;
        pZ = ZSumNum/dbDataNum;
    }


#if 0
    double max1,min1;
    int sum;
    if(size>2)
    {
        max1=data[0];
        min1=max1;
        sum=0;
        for(int i=0;i<size;i++)
        {
            sum += data[i];
            if(data[i]>max1)
            {
                max1 = data[i];   //一个循环之后max就是最大的值
            }

            if(data[i]<min1)
            {
                min1 = data[i];   //一个循环之后min就是最小的值
            }
        }

        sum = sum-max1-min1;       //去掉最大的值和最小的值
        return sum/(size-2); //对N-2个数求平均值
    }
#endif
}

void GPositionSystem::getOptimalValue(QVector<QVector<GobsCoord> >& pGOBSCoordList, double& pX, double& pY, double& pH)
{
    FILE *fp ;
    if(sondaryflag==1)
    {
        fp = fopen("./Sonardynelog.txt", "a+");
    }
    else{
        fp = fopen("./log.txt", "a+");
    }

    int iGobsNum = 0;
    for(int iList = 0; iList < pGOBSCoordList.count(); ++ iList)
    {
        iGobsNum += pGOBSCoordList[iList].count();
    }
    if(1 == iGobsNum)
    {
        pX = pGOBSCoordList[0][0].x;
        pY = pGOBSCoordList[0][0].y;
        pH = 0;
        return;
    }
    GobsCoord* nCobsCoords = new GobsCoord[4];

    QList<double> nSDList;
    QList<double> nSDListx;
    QList<double> nSDListy;
    int nGOBSNUM = pGOBSCoordList.count()/4;
    for(int iNo = 0; iNo < nGOBSNUM; ++ iNo)
    {
        int NGobsNO = iNo*4;

        nCobsCoords[0].x = pGOBSCoordList[NGobsNO].at(0).x;
        nCobsCoords[0].y = pGOBSCoordList[NGobsNO].at(0).y;
        nCobsCoords[0].z = pGOBSCoordList[NGobsNO].at(0).z;

        nCobsCoords[1].x = pGOBSCoordList[NGobsNO+1].at(0).x;
        nCobsCoords[1].y = pGOBSCoordList[NGobsNO+1].at(0).y;
        nCobsCoords[1].z = pGOBSCoordList[NGobsNO+1].at(0).z;

        nCobsCoords[2].x = pGOBSCoordList[NGobsNO+2].at(0).x;
        nCobsCoords[2].y = pGOBSCoordList[NGobsNO+2].at(0).y;
        nCobsCoords[2].z = pGOBSCoordList[NGobsNO+2].at(0).z;

        nCobsCoords[3].x = pGOBSCoordList[NGobsNO+3].at(0).x;
        nCobsCoords[3].y = pGOBSCoordList[NGobsNO+3].at(0).y;
        nCobsCoords[3].z = pGOBSCoordList[NGobsNO+3].at(0).z;

        double nRMSInfoX = (nCobsCoords[0].x+nCobsCoords[1].x+nCobsCoords[2].x+nCobsCoords[3].x)/4.0f;

        double nRMSInfo = (nCobsCoords[0].x+nCobsCoords[1].x+nCobsCoords[2].x+nCobsCoords[3].x)/4.0f;
        double nRMSInfoY = (nCobsCoords[0].y+nCobsCoords[1].y+nCobsCoords[2].y+nCobsCoords[3].y)/4.0f;
        double nSDInfo  = sqrt((pow((nCobsCoords[0].x-nRMSInfo),2) + pow((nCobsCoords[1].x-nRMSInfo),2) + pow((nCobsCoords[2].x-nRMSInfo),2) + pow((nCobsCoords[3].x-nRMSInfo),2))/3);

        double nSDInfoX  = sqrt((pow((nCobsCoords[0].x-nRMSInfoX),2) + pow((nCobsCoords[1].x-nRMSInfoX),2) + pow((nCobsCoords[2].x-nRMSInfoX),2) + pow((nCobsCoords[3].x-nRMSInfoX),2))/3);
        double nSDInfoY  = sqrt((pow((nCobsCoords[0].y-nRMSInfoY),2) + pow((nCobsCoords[1].y-nRMSInfoY),2) + pow((nCobsCoords[2].y-nRMSInfoY),2) + pow((nCobsCoords[3].y-nRMSInfoY),2))/3);

        fprintf(fp, "x0 = %s \t y0 = %s\n", QString("%1").arg(nCobsCoords[0].x, 0, 'f', 4).toStdString().c_str(), QString("%1").arg(nCobsCoords[0].y, 0, 'f', 4).toStdString().c_str());
        fprintf(fp, "x1 = %s \t y1 = %s\n", QString("%1").arg(nCobsCoords[1].x, 0, 'f', 4).toStdString().c_str(), QString("%1").arg(nCobsCoords[1].y, 0, 'f', 4).toStdString().c_str());
        fprintf(fp, "x2 = %s \t y2 = %s\n", QString("%1").arg(nCobsCoords[2].x, 0, 'f', 4).toStdString().c_str(), QString("%1").arg(nCobsCoords[2].y, 0, 'f', 4).toStdString().c_str());
        fprintf(fp, "x3 = %s \t y3 = %s\n", QString("%1").arg(nCobsCoords[3].x, 0, 'f', 4).toStdString().c_str(), QString("%1").arg(nCobsCoords[3].y, 0, 'f', 4).toStdString().c_str());
        fprintf(fp, "SDx = %s \t SDy = %s\n", QString("%1").arg(nSDInfoX, 0, 'f', 4).toStdString().c_str(),QString("%1").arg(nSDInfoY, 0, 'f', 4).toStdString().c_str());

        nSDList.append(nSDInfo);
        nSDListx.append(nSDInfoX);
        nSDListy.append(nSDInfoY);
    }
    delete [] nCobsCoords;

    /// 获取最小标准差在哪几个数据中
    int nMinSDNO = 0;
    double nMinSd = nSDList.at(0);
    for(int iList = 1; iList < nSDList.count(); ++ iList)
    {
        if(nMinSd > nSDList[iList])
        {
            nMinSd  = nSDList[iList];
            nMinSDNO= iList;
        }
    }
//    int nCurrSDNo = nMinSDNO*4;
//    pX = (pGOBSCoordList[nCurrSDNo][0].x + pGOBSCoordList[nCurrSDNo+1][0].x + pGOBSCoordList[nCurrSDNo+2][0].x + pGOBSCoordList[nCurrSDNo+3][0].x)/4;
//    pY = (pGOBSCoordList[nCurrSDNo][0].y + pGOBSCoordList[nCurrSDNo+1][0].y + pGOBSCoordList[nCurrSDNo+2][0].y + pGOBSCoordList[nCurrSDNo+3][0].y)/4;
    pH = nSDList[nMinSDNO];
//    fprintf(fp, "X = %f \t Y = %f \t SD = %f\n", pX, pY, pH);

    int nMinSDxNO = 0;
    double nMinSdx = nSDListx.at(0);
    for(int iList = 1; iList < nSDListx.count(); ++ iList)
    {
        if(nMinSdx > nSDListx[iList])
        {
            nMinSdx  = nSDListx[iList];
            nMinSDxNO= iList;
        }
    }

    int nCurrSDxNo = nMinSDxNO*4;
    pX = (pGOBSCoordList[nCurrSDxNo][0].x + pGOBSCoordList[nCurrSDxNo+1][0].x + pGOBSCoordList[nCurrSDxNo+2][0].x + pGOBSCoordList[nCurrSDxNo+3][0].x)/4;

    int nMinSDyNO = 0;
    double nMinSdy = nSDListy.at(0);
    for(int iList = 1; iList < nSDListy.count(); ++ iList)
    {
        if(nMinSdy > nSDListy[iList])
        {
            nMinSdy  = nSDListy[iList];
            nMinSDyNO= iList;
        }
    }

    int nCurrSDyNo = nMinSDyNO*4;
    pY = (pGOBSCoordList[nCurrSDyNo][0].y + pGOBSCoordList[nCurrSDyNo+1][0].y + pGOBSCoordList[nCurrSDyNo+2][0].y + pGOBSCoordList[nCurrSDyNo+3][0].y)/4;
    fprintf(fp, "X = %f \t Y = %f \t SD = %f\n", pX, pY, pH);
    if(sondaryflag==1)
       sondaryflag=0;
   fclose(fp);
#if 0
    int iGOBSNO = 0;
    for(int iVector = 0; iVector < pGOBSCoordList.count(); ++ iVector)
    {
        for(int jVector = 0; jVector < pGOBSCoordList[iVector].count(); ++ jVector)
        {
            nCobsCoords[iGOBSNO].x = pGOBSCoordList[iVector].at(jVector).x;
            nCobsCoords[iGOBSNO].y = pGOBSCoordList[iVector].at(jVector).y;
            nCobsCoords[iGOBSNO].z = pGOBSCoordList[iVector].at(jVector).z;
            ++ iGOBSNO;
        }
    }
    sortGOBSCoordX(nCobsCoords, 0, iGobsNum-1);
    double nYNum = nCobsCoords[0].y;
    int    nYLeft = 0, nYRight = 0;
    for(int jList = 1; jList < iGobsNum; ++ jList)
    {
        if(nYNum != nCobsCoords[jList].y)
        {
            nYRight = jList-1;
            sortGOBSCoordY(nCobsCoords, nYLeft, nYRight);
            nYLeft = jList;
            nYNum  = nCobsCoords[jList].y;
        }
    }
    if(nYRight != iGobsNum-1)
    {
        sortGOBSCoordY(nCobsCoords, nYLeft, iGobsNum-1);
    }
    int OptimalNO = iGobsNum/2;
    pX = nCobsCoords[OptimalNO].x;
    pY = nCobsCoords[OptimalNO].y;
    pH = nCobsCoords[OptimalNO].z;
    delete [] nCobsCoords;
#endif
}

//void GPositionSystem::sortGOBSCoordX(GobsCoord* pGOBSCoords, int left, int right)
//{
//    int i, j;
//    GobsCoord temp;
//    i = left;
//    j = right;
//    double x = pGOBSCoords[(i+j)/2].x;
//    do
//    {
//        while((pGOBSCoords[i].x < x) && (i < right)) i++;
//        while((pGOBSCoords[i].x > x) && (j < left))  j--;
//        if(i <= j)
//        {
//            temp = pGOBSCoords[i];
//            pGOBSCoords[i] = pGOBSCoords[j];
//            pGOBSCoords[j] = temp;
//            i++; j--;
//        }
//    }while(i<=j);
//    if(left < j) sortGOBSCoordX(pGOBSCoords, left, j);
//    if(i < right) sortGOBSCoordX(pGOBSCoords, i, right);
//}
//void GPositionSystem::sortGOBSCoordY(GobsCoord* pGOBSCoords, int left, int right)
//{
//    int i, j;
//    GobsCoord temp;
//    i = left;
//    j = right;
//    double x = pGOBSCoords[(i+j)/2].y;
//    do
//    {
//        while((pGOBSCoords[i].y < x) && (i < right)) i++;
//        while((pGOBSCoords[i].y > x) && (j < left))  j--;
//        if(i <= j)
//        {
//            temp = pGOBSCoords[i];
//            pGOBSCoords[i] = pGOBSCoords[j];
//            pGOBSCoords[j] = temp;
//            i++; j--;
//        }
//    }while(i<=j);
//    if(left < j) sortGOBSCoordY(pGOBSCoords, left, j);
//    if(i < right) sortGOBSCoordY(pGOBSCoords, i, right);
//}

void GPositionSystem::calculat3Coord(int pNO, double** n_pointXYZT,
                                    QVector<GPSInfo>& pAGPSInfo,
                                    QVector<GPSInfo>& pBGPSInfo,
                                    QVector<GPSInfo>& pCGPSInfo,
                                    QVector<GpsCoord>& pGPSCoordVector,
                                    QVector<GobsCoord>& pGobsCoordVector)
{
    n_pointXYZT[0][0] = pAGPSInfo[pNO].x;
    n_pointXYZT[0][1] = pAGPSInfo[pNO].y;
    n_pointXYZT[0][2] = pAGPSInfo[pNO].z;
    n_pointXYZT[0][3] = pAGPSInfo[pNO].t;

    n_pointXYZT[1][0] = pBGPSInfo[pNO].x;
    n_pointXYZT[1][1] = pBGPSInfo[pNO].y;
    n_pointXYZT[1][2] = pBGPSInfo[pNO].z;
    n_pointXYZT[1][3] = pBGPSInfo[pNO].t;

    n_pointXYZT[2][0] = pCGPSInfo[pNO].x;
    n_pointXYZT[2][1] = pCGPSInfo[pNO].y;
    n_pointXYZT[2][2] = pCGPSInfo[pNO].z;
    n_pointXYZT[2][3] = pCGPSInfo[pNO].t;

    /// 将坐标值保留下来
    GpsCoord nGPSCoordA;
    nGPSCoordA.x = pAGPSInfo[pNO].x;
    nGPSCoordA.y = pAGPSInfo[pNO].y;
    pGPSCoordVector.append(nGPSCoordA);

    GpsCoord nGPSCoordB;
    nGPSCoordB.x = pBGPSInfo[pNO].x;
    nGPSCoordB.y = pBGPSInfo[pNO].y;
    pGPSCoordVector.append(nGPSCoordB);

    GpsCoord nGPSCoordC;
    nGPSCoordC.x = pCGPSInfo[pNO].x;
    nGPSCoordC.y = pCGPSInfo[pNO].y;
    pGPSCoordVector.append(nGPSCoordC);
    double x=1.1;
    double y=1.1;
    double h=0.0;
    if(m_velocityFName.isEmpty())
    {
        qDebug()<<"=========================================================";
        qDebug()<<n_pointXYZT[0][0]<<","<<n_pointXYZT[0][1]<<","<<n_pointXYZT[0][2]<<","<<n_pointXYZT[0][3]<<"\t";
        qDebug()<<n_pointXYZT[1][0]<<","<<n_pointXYZT[1][1]<<","<<n_pointXYZT[1][2]<<","<<n_pointXYZT[1][3]<<"\t";
        qDebug()<<n_pointXYZT[2][0]<<","<<n_pointXYZT[2][1]<<","<<n_pointXYZT[2][2]<<","<<n_pointXYZT[2][3]<<"\t";
        testPostion_AB(n_pointXYZT, &x, &y, &h);
        GobsCoord GobsCoord;
        GobsCoord.x = x;
        GobsCoord.y = y;
        GobsCoord.z = h;

        pGobsCoordVector.append(GobsCoord);
        qDebug()<<"solve ok flag";
    }
    else
    {

        QVector <double> tdata{n_pointXYZT[0][3],n_pointXYZT[1][3],n_pointXYZT[2][3]};
        auto min=std::min_element(std::begin(tdata),std::end(tdata));
        double tmin=*min;

        h_low=MinDepth(tmin, soundspeed);
        if(0.0 == h_low)
        {
            return ;
        }
        h_high=soundspeed[soundspeed.length()][2];
        double x=1.1;
        double y=1.1;
        double h=0.0;
        Postion_AB(soundspeed, n_pointXYZT, h_high, h_low, &x, &y, &h);

        GobsCoord GobsCoord;
        GobsCoord.x = x;
        GobsCoord.y = y;
        GobsCoord.z = h;
        pGobsCoordVector.append(GobsCoord);
    }
}

void GPositionSystem::calculat4Coord(int pNO, double** n_pointXYZT,
                                    QVector<GPSInfo>& pAGPSInfo,
                                    QVector<GPSInfo>& pBGPSInfo,
                                    QVector<GPSInfo>& pCGPSInfo,
                                    QVector<GPSInfo>& pDGPSInfo,
                                    QVector<GpsCoord>& pGPSCoordVector,
                                    QVector<GobsCoord>& pGobsCoordVector)
{
    FILE *fp;
    if(sondaryflag==1)
    {
        fp = fopen("./Sonardynelog.txt", "a+");
    }
    else{
        fp = fopen("./log.txt", "a+");
    }

    n_pointXYZT[0][0] = pAGPSInfo[pNO].x;
    n_pointXYZT[0][1] = pAGPSInfo[pNO].y;
    n_pointXYZT[0][2] = pAGPSInfo[pNO].z;
    n_pointXYZT[0][3] = pAGPSInfo[pNO].t;

    n_pointXYZT[1][0] = pBGPSInfo[pNO].x;
    n_pointXYZT[1][1] = pBGPSInfo[pNO].y;
    n_pointXYZT[1][2] = pBGPSInfo[pNO].z+0.1;
    n_pointXYZT[1][3] = pBGPSInfo[pNO].t;

    n_pointXYZT[2][0] = pCGPSInfo[pNO].x;
    n_pointXYZT[2][1] = pCGPSInfo[pNO].y;
    n_pointXYZT[2][2] = pCGPSInfo[pNO].z+0.2;
    n_pointXYZT[2][3] = pCGPSInfo[pNO].t;

    n_pointXYZT[3][0] = pDGPSInfo[pNO].x;
    n_pointXYZT[3][1] = pDGPSInfo[pNO].y;
    n_pointXYZT[3][2] = pDGPSInfo[pNO].z+0.3;
    n_pointXYZT[3][3] = pDGPSInfo[pNO].t;

    /// 将坐标值保留下来
    GpsCoord nGPSCoordA;
    nGPSCoordA.x = pAGPSInfo[pNO].x;
    nGPSCoordA.y = pAGPSInfo[pNO].y;
    pGPSCoordVector.append(nGPSCoordA);

    GpsCoord nGPSCoordB;
    nGPSCoordB.x = pBGPSInfo[pNO].x;
    nGPSCoordB.y = pBGPSInfo[pNO].y;
    pGPSCoordVector.append(nGPSCoordB);

    GpsCoord nGPSCoordC;
    nGPSCoordC.x = pCGPSInfo[pNO].x;
    nGPSCoordC.y = pCGPSInfo[pNO].y;
    pGPSCoordVector.append(nGPSCoordC);

    GpsCoord nGPSCoordD;
    nGPSCoordD.x = pDGPSInfo[pNO].x;
    nGPSCoordD.y = pDGPSInfo[pNO].y;
    pGPSCoordVector.append(nGPSCoordD);

    double x=1.1;
    double y=1.1;
    double h=0.0;
    if(m_velocityFName.isEmpty())
    {


        fprintf(fp,"=========================================================\n");
        fprintf(fp,"X1 = %f \t Y1 = %f \t z1 = %f\n",n_pointXYZT[0][0],n_pointXYZT[0][1],n_pointXYZT[0][2],n_pointXYZT[0][3]);
        fprintf(fp,"X2 = %f \t Y2 = %f \t z2 = %f\n",n_pointXYZT[1][0],n_pointXYZT[1][1],n_pointXYZT[1][2],n_pointXYZT[1][3]);
        fprintf(fp,"X3 = %f \t Y3 = %f \t z3 = %f\n",n_pointXYZT[2][0],n_pointXYZT[2][1],n_pointXYZT[2][2],n_pointXYZT[2][3]);
        fprintf(fp,"X4 = %f \t Y4 = %f \t z4= %f\n",n_pointXYZT[3][0],n_pointXYZT[3][1],n_pointXYZT[3][2],n_pointXYZT[3][3]);
//        qDebug()<<n_pointXYZT[1][0]<<","<<n_pointXYZT[1][1]<<","<<n_pointXYZT[1][2]<<","<<n_pointXYZT[1][3]<<"\t";
//        qDebug()<<n_pointXYZT[2][0]<<","<<n_pointXYZT[2][1]<<","<<n_pointXYZT[2][2]<<","<<n_pointXYZT[2][3]<<"\t";
//        qDebug()<<n_pointXYZT[3][0]<<","<<n_pointXYZT[3][1]<<","<<n_pointXYZT[3][2]<<","<<n_pointXYZT[3][3]<<"\t";
        Solve4postion_AB(n_pointXYZT, &x, &y, &h);
        GobsCoord GobsCoord;
        GobsCoord.x = x;
        GobsCoord.y = y;
        GobsCoord.z = h;
        fprintf(fp, "4point X = %f \t Y = %f \t h = %f\n", x, y, h);
        pGobsCoordVector.append(GobsCoord);
        qDebug()<<"solve ok flag";

    }
    else
    {

        QVector <double> tdata{n_pointXYZT[0][3],n_pointXYZT[1][3],n_pointXYZT[2][3]};
        auto min=std::min_element(std::begin(tdata),std::end(tdata));
        double tmin=*min;

        h_low=MinDepth(tmin, soundspeed);
        if(0.0 == h_low)
        {
            return ;
        }
        h_high=soundspeed[soundspeed.length()][2];
        double x=1.1;
        double y=1.1;
        double h=0.0;
        Postion_AB(soundspeed, n_pointXYZT, h_high, h_low, &x, &y, &h);

        GobsCoord GobsCoord;
        GobsCoord.x = x;
        GobsCoord.y = y;
        GobsCoord.z = h;
        pGobsCoordVector.append(GobsCoord);
    }
    fclose(fp);
}


void GPositionSystem::testPostion_AB(double **pointxyt,double *x,double *y,double *h)
{
    double *r=new double[3];
    double* pointtime;
    pointtime=(double *)malloc((3)*sizeof(double));
    memset(pointtime,0,sizeof(double)*3);
    for(int i=0;i<3;i++)
    {
        pointtime[i]= pointxyt[i][3];
    }
    for(int i=0;i<3;i++)
    {

//        double a1=1.5*pointtime[i]/2.0;
        double a1=1.5*(pointtime[i]-16.5)/2.0;
        r[i]=a1;
//        r[i]=(a1-15.061)/1.062;

    }

    double d1=(pointxyt[0][0]*pointxyt[0][0]+pointxyt[0][1]*pointxyt[0][1]+pointxyt[0][2]*pointxyt[0][2]);
    double d2=(pointxyt[1][0]*pointxyt[1][0]+pointxyt[1][1]*pointxyt[1][1]+pointxyt[1][2]*pointxyt[1][2]);
    double d3=(pointxyt[2][0]*pointxyt[2][0]+pointxyt[2][1]*pointxyt[2][1]+pointxyt[2][2]*pointxyt[2][2]);

    double d1_r1=(d1-r[0]*r[0]);

    // qDebug() << "d1_r1 = " << d1_r1 ;
    double A[4]={2*(pointxyt[1][0]-pointxyt[0][0]), 2*(pointxyt[2][0]-pointxyt[0][0]),
               2*(pointxyt[1][1]-pointxyt[0][1]), 2*(pointxyt[2][1]-pointxyt[0][1])};

    double B[2]={d2-r[1]*r[1]-d1_r1, d3-r[2]*r[2]-d1_r1};
    //   qDebug() << "A = " << A[1],A[2],A[3];
    //   qDebug() << "B = " << B[1];

    int N = 2;
    int ipiv[2];
    int n = N;
    int nrhs = 1;
    int lda = N;
    int ldb = N;

    int info;
//    dgesv_(&n,&nrhs,A,&lda,ipiv,B,&ldb,&info);  ///< zhw-update
    if(info==0)
    {
      *x=B[0];
      *y=B[1];
    }

}
void GPositionSystem::Solve4postion_AB(double **pointxyt, double *x, double *y, double *h)
{
    double *r=new double[4];
    double* pointtime;
    pointtime=(double *)malloc((4)*sizeof(double));
    memset(pointtime,0,sizeof(double)*4);
    for(int i=0;i<4;i++)
    {
        pointtime[i]= pointxyt[i][3];
    }
    for(int i=0;i<4;i++)
    {

        double a1=1.5*(pointtime[i]-16.5)/2.0;//根据系统时延为16.5ms对时延进行修正
        r[i]=a1;
//        r[i]=(a1-15.061)/1.062;

    }
//    qDebug() << "d1_r1 = " << r[0] <<r[1]<<r[2]<<r[3];
    double d1=(pointxyt[0][0]*pointxyt[0][0]+pointxyt[0][1]*pointxyt[0][1]+pointxyt[0][2]*pointxyt[0][2]);
    double d2=(pointxyt[1][0]*pointxyt[1][0]+pointxyt[1][1]*pointxyt[1][1]+pointxyt[1][2]*pointxyt[1][2]);
    double d3=(pointxyt[2][0]*pointxyt[2][0]+pointxyt[2][1]*pointxyt[2][1]+pointxyt[2][2]*pointxyt[2][2]);
    double d4=(pointxyt[3][0]*pointxyt[3][0]+pointxyt[3][1]*pointxyt[3][1]+pointxyt[3][2]*pointxyt[3][2]);
//    qDebug() << "point1 = " << pointxyt[0][0] <<pointxyt[0][1]<<pointxyt[0][2];
//    qDebug() << "point2 = " << pointxyt[1][0] <<pointxyt[1][1]<<pointxyt[1][2];
//    qDebug() << "point3 = " << pointxyt[2][0] <<pointxyt[2][1]<<pointxyt[2][2];
//    qDebug() << "point4 = " << pointxyt[3][0] <<pointxyt[3][1]<<pointxyt[3][2];

    // qDebug() << "d1_r1 = " << d1_r1 ;
//    double A[4]={2*(pointxyt[1][0]-pointxyt[0][0]), 2*(pointxyt[2][0]-pointxyt[0][0]),
//               2*(pointxyt[1][1]-pointxyt[0][1]), 2*(pointxyt[2][1]-pointxyt[0][1])};

    double A[9]={2*(pointxyt[1][0]-pointxyt[0][0]),2*(pointxyt[2][0]-pointxyt[0][0]),2*(pointxyt[3][0]-pointxyt[0][0]),
                 2*(pointxyt[1][1]-pointxyt[0][1]),2*(pointxyt[2][1]-pointxyt[0][1]),2*(pointxyt[3][1]-pointxyt[0][1]),
                 2*(pointxyt[1][2]-pointxyt[0][2]),2*(pointxyt[2][2]-pointxyt[0][2]),2*(pointxyt[3][2]-pointxyt[0][2])};


    double B[3]={d2-d1+r[0]*r[0]-r[1]*r[1],d3-d1+r[0]*r[0]-r[2]*r[2],d4-d1+r[0]*r[0]-r[3]*r[3]};
//       qDebug() << "A1 = " << A[0]<<"A2 = "<<A[1]<<"A3 = "<<A[2]<<"A4 = "<<A[3]<<"A5 = "<<A[4]<<"A6 = "<<A[5]<<"A7 = "<<A[6]<<"A8 = "<<A[7]<<"A9 = "<<A[8];
//       qDebug() << "B = " << B[0]<<B[1]<<B[2];

    int N = 3;
    int ipiv[3];
    int n = N;
    int nrhs = 1;
    int lda = N;
    int ldb = N;

    int info;
//    dgesv_(&n,&nrhs,A,&lda,ipiv,B,&ldb,&info);  ///< zhw-update
    if(info==0)
    {
      *x=B[0];
      *y=B[1];
      *h=B[2];
    }
}
void GPositionSystem::Postion_AB(QVector<QVector<float> > V_speed, double **pointxyt, double h_high,double h_low,double *x,double *y,double *h)
{
    double *r=new double[3];
    *h=(h_high+h_low)/2.0;
    double* pointtime;
    pointtime=(double *)malloc((3)*sizeof(double));
    memset(pointtime,0,sizeof(double)*3);

    for(int i=0;i<3;i++)
    {
        pointtime[i]= pointxyt[i][3];
    }

    for(int i=0;i<3;i++)
    {

        r[i]=Postion_R(*h,pointxyt[i][3],V_speed);
        //qDebug() << "i = " << i << "\t" << r[i];
    }
    double d1=(pointxyt[0][0]*pointxyt[0][0]+pointxyt[0][1]*pointxyt[0][1]+pointxyt[0][2]*pointxyt[0][2]);
    double d2=(pointxyt[1][0]*pointxyt[1][0]+pointxyt[1][1]*pointxyt[1][1]+pointxyt[1][2]*pointxyt[1][2]);
    double d3=(pointxyt[2][0]*pointxyt[2][0]+pointxyt[2][1]*pointxyt[2][1]+pointxyt[2][2]*pointxyt[2][2]);

    double d1_r1=(d1-r[0]*r[0]);

    // qDebug() << "d1_r1 = " << d1_r1 ;
    double A[4]={2*(pointxyt[1][0]-pointxyt[0][0]), 2*(pointxyt[2][0]-pointxyt[0][0]),
               2*(pointxyt[1][1]-pointxyt[0][1]), 2*(pointxyt[2][1]-pointxyt[0][1])};

    double B[2]={d2-r[1]*r[1]-d1_r1, d3-r[2]*r[2]-d1_r1};
    //   qDebug() << "A = " << A[1],A[2],A[3];
    //   qDebug() << "B = " << B[1];

    int N = 2;
    int ipiv[2];
    int n = N;
    int nrhs = 1;
    int lda = N;
    int ldb = N;

    int info;
//    dgesv_(&n,&nrhs,A,&lda,ipiv,B,&ldb,&info);  ///< zhw-update

    if(info==0)
    {
      *x=B[0];
      *y=B[1];
    }

    double E=0;
    double R=0;
    double P=0;
    double error[3]={0};
    double p[3]={0};
    for (int i=0;i<3;i++)
    {
        R=R+r[i];
        error[i]=abs(r[i]-sqrt(pow(*x-pointxyt[i][0],2)+pow(*y-pointxyt[i][1],2)));
        E=E+error[i];
        p[i]=sqrt(pow(*x-pointxyt[i][0],2)+pow(*y-pointxyt[i][1],2));
        P=P+p[i];
    }
    double MAE=E/3;
    if (MAE<4)
    {
          return;
    }
    else
    {
      if(R<P)
      {
          h_low=*h;
          Postion_AB(soundspeed,pointxyt,h_high,h_low,x,y,h);
          return;
      }
      else
      {
          h_high=*h;
          Postion_AB(soundspeed,pointxyt,h_high,h_low,x,y,h);
          return;
      }
    }
}

double GPositionSystem::Postion_R(double h,double t,QVector<QVector<float> > V_speed)
{

    double H=0;
    double number_goal;

    for (int i=0;i<V_speed.length();i++)
    {
        H=V_speed[i][1]+H;
        if (h<=H)
        {
            number_goal=i;
            break;
        }
    }
//    number_goal=number_goal-1;
    int inom=int(number_goal)-1;
    angle_low=0;
    angle_high=M_PI/2;
    angle=new double[inom];

    PostionAngle(t,V_speed,number_goal,angle_low,angle_high);
    double r=0;
    for(int i=0;i<int(number_goal);i++)//int(number_goal)
    {
//        qDebug() << "i = " << i << "\t" << angle[i];
        r=r+V_speed[i][1]*tan(angle[i]);

    }
    return r;
}

void GPositionSystem::PostionAngle(double t,QVector<QVector<float> > V_speed,double number_goal,double angle_h,double angle_l )
{
    double oritime=t;
    double Q=0.00001;
    double nowtime=0;
    double a,b,dlt;
//    double *angle=new double[int(number_goal)];

    angle[0]=(angle_h+angle_l)/2;

    double *t_layer=new double[int(number_goal)];
    for(int i=0;i<number_goal;i++)
    {
        if(i<number_goal-1)
        {
            a=sin(angle[i]*V_speed[i+1][0]/V_speed[i][0]);
            angle[i+1]=asin(a);
            b=asin(a);
            t_layer[i]=V_speed[i+1][1]/(V_speed[i][0]*cos(angle[i]));
//            qDebug() << "i = " << i << "\t" <<angle[i]<<","<< t_layer[i];
            t=t-t_layer[i];
            nowtime=nowtime+t_layer[i];
            if(t<0)
            {
                dlt=nowtime-oritime;
                angle_high=angle[0];
                t=oritime;
                PostionAngle(t,V_speed,number_goal,angle_low,angle_high);
                return ;

            }
        }
        else
        {
            dlt=nowtime-oritime;
//          qDebug()<<"anger(number_goal-1)="<<number_goal-1<< "\t"<<angle[int(number_goal)-1]<<","<<cos(angle[int(number_goal)-1]);
            double diff=abs(t*V_speed[i][0]*cos(angle[i])-V_speed[i][1]);
            if(diff<=Q)
            {
                return ;
            }
            else
            {
                if(t*V_speed[i][0]*cos(angle[i])>V_speed[i][1])
                {
                    angle_low=angle[0];
                    t=oritime;
                    PostionAngle(t,V_speed,number_goal,angle_low,angle_high);
                    return ;
                }
                else{
                    angle_high=angle[0];
                    t=oritime;
                    PostionAngle(t,V_speed,number_goal,angle_low,angle_high);
                    return ;
                }
            }
        }
    }
}

void GPositionSystem::slotRecvGpsCord(const GpsCoord& cord)
{
//    qDebug() << "recv gps cord: x :" << QString("%1").arg(cord.x, 0, 'f', 2) << "\t y :" << QString("%1").arg(cord.y, 0, 'f', 2)
//             << "\t utc_sec = " << cord.utc_sec;
    if(cord.utc_sec == 0)
    {
        return;
    }

//    QString info = "recv gps cord: x :" + QString("%1").arg(cord.x, 0, 'f', 2) + "\t y :" + QString("%1").arg(cord.y, 0, 'f', 2);
//    showText(info);

    labelGPSX->setText(QString("%1").arg(cord.x, 0, 'f', 2));
    labelGPSY->setText(QString("%1").arg(cord.y, 0, 'f', 2));

//    //坐标传递给数据中心
    DataManager::instance()->addGpsCoord(cord);

    mGpsCords.clear();
    mGpsCords.append(cord);

    m_systemDis->dispCoordCurrent(cord.x, cord.y, cord.gpsX, cord.gpsY);
}

void GPositionSystem::slotBrowseVelocity(bool)
{
    m_velocityFName = QFileDialog::getOpenFileName(this, QStringLiteral("选择声波速度文件"), "./");
    if(!m_velocityFName.isEmpty())
    {
        lineEditVelocityFile->setText(m_velocityFName);

        ///读取声波速度文件
        QFile file(m_velocityFName);
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug()<<"Can't open the file!"<<endl;
        }
        QTextStream stream(&file);
        QString line_in;
        int icount=0;
        stream.seek(file.size());
        stream.seek(0);
        while(!stream.atEnd())
        {
        line_in = stream.readLine();
        icount=icount+1;
        }
        stream.seek(0);
        icount=0;
        while(!stream.atEnd())
        {
            line_in = stream.readLine();
            QStringList list=line_in.split('\t');
            float s1=list[0].toFloat();
            float s2=list[1].toFloat();
            float s3=list[2].toFloat();

            QVector<float> vec;
            vec.append(s1);
            vec.append(s2);
            vec.append(s3);
            soundspeed.append(vec);
            icount=icount+1;
        }
        file.close();
    }
}

void GPositionSystem::createWg()
{
    QHBoxLayout *mainLayout = new QHBoxLayout;

//    mainLayout->setSpacing(0);
    //左侧边栏--------------------------------
    QWidget  *leftWidget = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    //serialPort
    m_gSerialPort = new  GSerialPort(this);
    leftLayout->addWidget(m_gSerialPort);

    //start stop  button
    m_startBtn = new QPushButton(QStringLiteral("开始GPS定位"),this);
    m_stopBtn = new QPushButton(QStringLiteral("停止"),this);
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_startBtn);
    btnLayout->addWidget(m_stopBtn);
    leftLayout->addLayout(btnLayout);

    //Deck Unit
    m_deckUnit = new DeckUnit(this);
    connect(m_deckUnit, SIGNAL(signal_send_loadinfo(QString)), this, SLOT(slot_recv_loadinfo(QString)));
    leftLayout->addWidget(m_deckUnit);

    leftWidget->setLayout(leftLayout);

//    leftWidget->setMaximumWidth(280);

    QLabel* VelocityLabel = new QLabel(QStringLiteral("声波速度文件:"));
    lineEditVelocityFile  = new QLineEdit;

    QPushButton* pushVelocity = new QPushButton(QStringLiteral("浏览"));
    connect(pushVelocity, SIGNAL(clicked(bool)), this, SLOT(slotBrowseVelocity(bool)));
    QHBoxLayout* VeolcityLayout = new QHBoxLayout;
    VeolcityLayout->addWidget(lineEditVelocityFile);
    VeolcityLayout->addWidget(pushVelocity);

    QLabel* labelLocat = new QLabel(QStringLiteral("当前位置:"));

    QLabel* labelX = new QLabel(QStringLiteral("X:"));
    labelGPSX = new QLabel("000000");
    QLabel* labelY = new QLabel("Y:");
    labelGPSY = new QLabel("0000000");
    QHBoxLayout* HGPSCoordXBoxLayout = new QHBoxLayout;
    HGPSCoordXBoxLayout->addWidget(labelX);
    HGPSCoordXBoxLayout->addWidget(labelGPSX);
    HGPSCoordXBoxLayout->addWidget(labelY);
    HGPSCoordXBoxLayout->addWidget(labelGPSY);

    QVBoxLayout* mGOSCoordLayout = new QVBoxLayout;
    mGOSCoordLayout->addWidget(labelLocat);
    mGOSCoordLayout->addLayout(HGPSCoordXBoxLayout);

    QVBoxLayout* VelocityVLayout = new QVBoxLayout;
    VelocityVLayout->addWidget(VelocityLabel);
    VelocityVLayout->addLayout(VeolcityLayout);
    VelocityVLayout->addLayout(mGOSCoordLayout);
    leftLayout->addLayout(VelocityVLayout);

    mainLayout->addWidget(leftWidget,0);

    //右侧绘图布局
    QVBoxLayout *rightLayout = new QVBoxLayout;
    TitleBar *titleBar = new TitleBar(this);
    rightLayout->addWidget(titleBar);

    m_systemDis = new systemdisplay(this);
    rightLayout->addWidget(m_systemDis,1);

    mainLayout->addLayout(rightLayout,1);

    mainLayout->setStretchFactor(leftWidget, 2);
    mainLayout->setStretchFactor(rightLayout, 6);

    m_TableGPSInfo = new QTableWidget;
    m_TableGPSInfo->setColumnCount(12);
    QStringList nHeadInfo;
    nHeadInfo << "NO"<< "GPSX1" << "GPSY1" << "GPSX2" << "GPSY2" << "GPSX3" << "GPSY3" << "GPSX4" << "GPSY4" << "SolutionX" << "SolitionY" << "SolitionH" ;
    m_TableGPSInfo->setHorizontalHeaderLabels(nHeadInfo);
    m_TableGPSInfo->horizontalHeader()->setStretchLastSection(true);
    m_TableGPSInfo->setColumnWidth(0, m_TableGPSInfo->width()/5-50);
    m_TableGPSInfo->setColumnWidth(1, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(2, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(3, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(4, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(5, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(6, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(7, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(8, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(9, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(10, m_TableGPSInfo->width()/3);
    m_TableGPSInfo->setColumnWidth(11, m_TableGPSInfo->width()/3);

    QHBoxLayout* nTableWidgetLayout = new QHBoxLayout;
    nTableWidgetLayout->addWidget(m_TableGPSInfo);

    m_TextEditGPS = new QTextEdit;
    m_TextEditDuck= new QTextEdit;
    m_TextEditDuck->setMaximumHeight(100);
    m_TextEditGPS->setMaximumHeight(100);
    QHBoxLayout* nTextEditLayout = new QHBoxLayout;
    nTextEditLayout->addWidget(m_TextEditGPS);
    nTextEditLayout->addWidget(m_TextEditDuck);

    QVBoxLayout* mainVLayout = new QVBoxLayout;
    mainVLayout->addLayout(mainLayout, 0);
    mainVLayout->addLayout(nTableWidgetLayout, 1);
    mainVLayout->addLayout(nTextEditLayout, 2);

    this->setLayout(mainVLayout);
//    this->setLayout(mainLayout);
//    m_gSerialPort->setShowTxtFunc(m_showTxtFunc);
//    m_deckUnit->setShowTxtFunc(m_showTxtFunc);

    connect(m_startBtn,&QPushButton::clicked,this,&GPositionSystem::startPostion);
    connect(m_stopBtn,&QPushButton::clicked,this,&GPositionSystem::stopPostion);
    connect(titleBar,&TitleBar::sideBarHide,leftWidget,&QWidget::setHidden);
}

void GPositionSystem::testData()
{
 #if 0
    double A[9]={-23870,158	,168,
                -13900,-24658,214,
                5000,-23394,74};
    double B[3]={-94713552950.6634,-1084567413292.31,-951757426122.445};
    int N = 3;
    int ipiv[3];
    int n = N;
    int nrhs = 1;
    int lda = N;
    int ldb = N;

    int info;
    dgesv_(&n,&nrhs,A,&lda,ipiv,B,&ldb,&info);



    //模拟数据传递给画图控件绘制
    int N = 100;
    QVector<GpsCoord>   gpsCords;
    QVector<GobsCoord> gobsCords;
    float x0 = 100000;
    float y0 = 2000000;
    float x,y;
    for(int i=0;i<N;i++)
    {
        GpsCoord cord;
        cord.x = x0+i*100;
        cord.y = y0+rand()%10000;
        gpsCords.append(cord);

        if(i%4 ==0)
        {
            GobsCoord gobs_cord;
            gobs_cord.x = x0+i*100;
            gobs_cord.y = y0+rand()%10000;
            gobsCords.append(gobs_cord);
        }
    }
    m_positionChart->setData(gpsCords,gobsCords);
#endif
}
