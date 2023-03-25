#include "gserialport.h"
#include "ui_gserialport.h"
#include <QDebug>
#include "geo2xy_utm.h"

#define GPGGA_STRING "$GPGGA,"
//#define GPGGA_STRING "$GNGGA,"
#define GPRMC_STRING "$GPRMC,"

#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QDateTime>

//#define Test

QMap<int,QSerialPort::BaudRate> GSerialPort::mpBaudRate= {{0,QSerialPort::Baud9600},{1,QSerialPort::Baud115200},{2,QSerialPort::Baud4800}};
QMap<int,QSerialPort::DataBits> GSerialPort::mpDatabit = {{0,QSerialPort::Data5},{1,QSerialPort::Data6},{2,QSerialPort::Data7},{3,QSerialPort::Data8}};
QMap<int,QSerialPort::Parity>   GSerialPort::mpParity  = {{0,QSerialPort::NoParity},{1,QSerialPort::OddParity},{2,QSerialPort::EvenParity},\
                                                                                        {3,QSerialPort::MarkParity},{4,QSerialPort::SpaceParity}};
QMap<int,QSerialPort::StopBits> GSerialPort::mpStopBit = {{0,QSerialPort::OneStop},{1,QSerialPort::OneAndHalfStop},{2,QSerialPort::TwoStop}};
QMap<int,QSerialPort::FlowControl> GSerialPort::mpFlowControl = {{0,QSerialPort::NoFlowControl},{1,QSerialPort::HardwareControl},\
                                                                                                    {2,QSerialPort::SoftwareControl}};

GSerialPort::GSerialPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GSerialPort)
  ,m_serialPort(new QSerialPort(this))
{
    ui->setupUi(this);
    initWg();
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->stopBitCbx->setVisible(false);
    ui->parityCbx->setVisible(false);
    ui->flowControlCbx->setVisible(false);
    connect(m_serialPort,&QSerialPort::readyRead,this,&GSerialPort::slotReadyRead);
}

GSerialPort::~GSerialPort()
{
    delete ui;
}

bool GSerialPort::open()
{
//    qDebug() << mpDatabit.value(ui->dataBitCbx->currentIndex()) << "\t"
//         << mpStopBit.value(ui->stopBitCbx->currentIndex()) << "\t"
//         << mpParity.value(ui->parityCbx->currentIndex()) << "\t"
//         << mpParity.value(ui->flowControlCbx->currentIndex());

    m_serialPort->setPortName(ui->SerialNumCbx->currentText());
    if(!m_serialPort->setBaudRate(mpBaudRate.value(ui->baudRateCbx->currentIndex())))
    {
        emit recvReadGPSInformation("setBaudRate");
        return false;
    }
    if(!m_serialPort->setDataBits(mpDatabit.value(ui->dataBitCbx->currentIndex())))
    {
        emit recvReadGPSInformation("setDataBits");
        return false;
    }
    if(!m_serialPort->setStopBits(mpStopBit.value(ui->stopBitCbx->currentIndex())))
    {
        emit recvReadGPSInformation("setStopBits");
        return false;
    }
    emit recvReadGPSInformation(QString::number(ui->stopBitCbx->currentIndex()));
    if(!m_serialPort->setParity(mpParity.value(ui->parityCbx->currentIndex())))
    {
        emit recvReadGPSInformation("setParity");
        return false;
    }
    if(!m_serialPort->setFlowControl(mpFlowControl.value(ui->flowControlCbx->currentIndex())))
    {
        emit recvReadGPSInformation("setFlowControl");
        return false;
    }

    if(!m_serialPort->open(QIODevice::ReadWrite))
    {
        return false;
    }

    //模拟---begin-----
//    if(!m_timer)
//    {
//        m_timer = new QTimer(this);
//        connect(m_timer,&QTimer::timeout,this,&GSerialPort::slotReadyRead);
//    }
//    m_timer->start(1000);
    return true;
    //模拟---end-----
}
void GSerialPort::close()
{
    m_serialPort->flush();
    m_serialPort->close();
    QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("关闭串口成功."));
}

//void GSerialPort::setShowTxtFunc(ShowTextFunc func)
//{
//    m_showTxtFunc = func;
//}

void GSerialPort::slotReadyRead()
{
//    //模拟---begin-----080944.00  === GPGGA
//    m_byteArray = QString("$GNGGA,085106.00,3732.49550,N,12205.48300,E,5,12,0.87,5.4,M,8.3,M,1.0,0000*56\r\n$GNGGA,085107.00,3732.49487,N,12205.48286,E,5,12,0.91,5.3,M,8.3,M,1.0,0000*53\r\n$GNGGA,085108.00,3732.49419,N,12205.48269,E,5,12,0.87,5.4,M,8.3,M,1.0,0000*5A\r\n")
//            .arg(QDateTime::currentDateTimeUtc().time().toString("HH:mm:ss")).toLocal8Bit();
//    //模拟---end-----

//    //模拟---begin-----080944.00  === GPGGA
//    m_byteArray = QString("$GPGGA,072924.00,3958.56731,N,11622.62050,E,2,09,1.16,64.6,M,-8.6,M,,0000*7B\r\n")
//            .arg(QDateTime::currentDateTimeUtc().time().toString("HH:mm:ss")).toLocal8Bit();
//    //模拟---end-----


//    m_byteArray = QString("NMEA unknown msg*46\
//                          $GNTXT,01,01,01,NMEA unknown msg*46\
//                          $GNTXT,01,01,01,NMEA unknown msg*46\
//                          $GNTXT,01,01,01,NMEA unknown msg*46\
//                          $GNTXT,01,01,01,NMEA unknown msg*46\
//                          Ã¿oî $GNVTG,,T,,M,0.015,N,0.029,K,D*37\
//                          $GNGGA,033505.00,3732.82441,N,12206.37388,E,4,12,0.74,2.8,M,8.3,M,1.0,0000*57\r\n\
//                          $GNGGA,011233.00,3732.49839,N,12205.47146,E,1,05,2.63,-12.3,M,8.3,M,,*6A
//                          $GNGSA,A,3,05,13,15,24,20,18,,,,,,,1.49,0.74,1.29,1*0A\
//                          $GNGSA,A,3,01,03,30,06,13,16,25,27,09,08,02,23,1.49,0.74,1.29,4*03\
//                          $GPGSV,4,1,13,05,24,106,38,10,07,299,,11,,,15,13,40,047,43,0*5F\
//                          $GNGLL,3732.82441,N,12206.37388,E,033505.00,A,D*7C")\
//            .arg(QDateTime::currentDateTimeUtc().time().toString("HH:mm:ss")).toLocal8Bit();


//    //==测试---begin---GPRMC
//    m_byteArray = QString("$GPRMC,023543.00,A,2308.28715,N,11322.09875,E,0.195,,240213,,,A*78")
//                  .arg(QDateTime::currentDateTimeUtc().time().toString("HH:mm:ss")).toLocal8Bit();
//    //==测试---end----



    m_byteArray += m_serialPort->readAll();
    QString text = QString(m_byteArray);


    int index = text.indexOf(GPGGA_STRING);
    if(index >= 0)
    {
        //找到“$GPGGA”，去头
        text = QString(m_byteArray).replace(GPGGA_STRING, "");
        //回车换行符-消息
        index = text.indexOf("\r\n");
        // index = text.indexOf("\r");
        // index = text.indexOf("\n");
        if(index >= 0)
        {
            QString gpgga_string = text.left(index+1);
            qDebug() << "gpgga_string:" << gpgga_string;
            //获取地球坐标
            GpsCoord cord = GPGGAStr2Cord(gpgga_string);
            //计算物理坐标
            emit recvGpsCord(cord.toXy());

            //移除该段
           m_byteArray =  m_byteArray.mid(index+1);
        }

    }
}

GpsCoord GSerialPort::GPGGAStr2Cord(const QString& in_str)
{
    GpsCoord gpsCord;
    QString ret_str = in_str.mid(7);
    int idx = 0;
    do{
        int index = ret_str.indexOf(",");
        if(index<1)
        {
            return  GpsCoord();
            break;
        }
        QString text = ret_str.left(index);
        ret_str = ret_str.mid(index+1);
        qDebug() << "ret_str :" << ret_str;

        //utc
        if(idx == 0)
        {
            QDateTime dateTime =QDateTime::currentDateTimeUtc();
            dateTime.setTimeSpec(Qt::UTC);
            QTime utcTime= QTime::fromString(text.left(text.size()-3),"hh:mm:ss");
            dateTime.setTime(utcTime);
            gpsCord.utc_sec = dateTime.toTime_t();
        }
        //纬度
        if(idx == 1)
        {
            int DecpointLocat = text.indexOf(".");
            int RightLenth    = text.length()-DecpointLocat+2;
            gpsCord.y  = text.left(2).toInt() + text.right(RightLenth).toDouble()/60.f;
        }
        else if(idx == 2)
        {
            if(text == "S") //南半球
            {
                gpsCord.y = -gpsCord.y;
            }
        }
        //经度
        else if(idx == 3)
        {
            int DecpointLocat = text.indexOf(".");
            int RightLenth    = text.length()-DecpointLocat+2;
            gpsCord.x  = text.left(3).toInt() + text.right(RightLenth).toDouble()/60.f;
        }
        else if(idx == 4)
        {
            if(text == "W") //西经
            {
                gpsCord.x = -gpsCord.x;
            }
        }
        idx++;
    }while(idx<=4);
    return gpsCord;
}

void GSerialPort::initWg()
{
    //串口号列表
    QList<QSerialPortInfo> portInfos =  QSerialPortInfo::availablePorts();
    int defaultIdx = -1;
    if(portInfos.size()>0) defaultIdx = 0;
    for(int i=0;i<portInfos.size();i++)
    {
        ui->SerialNumCbx->addItem(portInfos[i].portName());
        if("USB Serial Port" == portInfos[i].description())
            defaultIdx = i;
    }

    //设置参数默认值
    ui->SerialNumCbx->setCurrentIndex(defaultIdx);
    ui->dataBitCbx->setCurrentIndex(3);
    ui->stopBitCbx->setCurrentIndex(0);
}



