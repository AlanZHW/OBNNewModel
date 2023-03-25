#include "deckunit.h"
#include  "ui_deckunit.h"
//#include <QtCore>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QIntValidator>
#include <QCheckBox>
#include <QComboBox>
#include <QTime>

#include "publicwidgets.h"


DeckUnit::DeckUnit(QWidget *parent)
    :QWidget(parent),ui(new Ui::DeckUnit)
    ,m_socket(new QTcpSocket(this)),m_SerialPort(NULL)
{
    ui->setupUi(this);
    this->setMinimumSize(20,60);
    creatWg();
    m_SerialPort    = new QSerialPort();
    getPortNameList(m_portNameList);    ///< 获取当前系统可用的串口名列表
    m_SerialPortComboBox->addItems(m_portNameList);///< 将可用串口列表添加到下拉菜单中

//    connect(m_socket,&QTcpSocket::stateChanged,this,&DeckUnit::socketStateChanged);
//    connect(m_socket,&QTcpSocket::readyRead,this,&DeckUnit::slotReadyRead);

    connect(m_SerialPort,&QSerialPort::readyRead,this,&DeckUnit::slotReadyRead);
    sondaryflag=0;
}

/// 获取当前系统可用的串口号
void DeckUnit::getPortNameList(QStringList& p_portNameList)
{
    p_portNameList.clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        p_portNameList << info.portName();
    }
}

void DeckUnit::convertStringToHex(const QString &str, QByteArray &byteData)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    byteData.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata    = convertCharToHex(hstr);
        lowhexdata = convertCharToHex(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        byteData[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    byteData.resize(hexdatalen);
}

char DeckUnit::convertCharToHex(char ch)
{
    if((ch >= '0') && (ch <= '9'))
         return ch-0x30;
     else if((ch >= 'A') && (ch <= 'F'))
         return ch-'A'+10;
     else if((ch >= 'a') && (ch <= 'f'))
         return ch-'a'+10;
    else return (-1);
}

//void DeckUnit::setShowTxtFunc(ShowTextFunc func)
//{
//    m_showTxtFunc = func;
//}

void DeckUnit::slotConnect(bool connect)
{
#if 0
    /// 测试
    double nX0 = lineEditX0->text().toDouble();
    double nY0 = lineEditY0->text().toDouble();
    double nZ0 = lineEditZ0Value->text().toDouble();
    emit signal_recv_coordsystem(nX0, nY0, nZ0);
    return ;
#else
        if(lineEditRangeWaterMin->text().isEmpty() || lineEditRangeWaterMax->text().isEmpty())
        {
            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请输入水深范围."));
            return;
        }
        float RangeWaterMin = lineEditRangeWaterMin->text().toFloat();
        float RangeWaterMax = lineEditRangeWaterMax->text().toFloat();
        if(RangeWaterMin > RangeWaterMax)
        {
            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("范围输入不正确."));
            return;
        }
        if(lineEditOBSMin->text().isEmpty() || lineEditOBSMax->text().isEmpty())
        {
            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请输入OBS信息."));
            return;
        }
//        float OBSMin = lineEditOBSMin->text().toFloat();
//        float OBSMax = lineEditOBSMax->text().toFloat();
//        if(OBSMin > OBSMax)
//        {
//            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("OBS信息不正确."));
//            return;
//        }
        if(lineEditX0->text().isEmpty() || lineEditY0->text().isEmpty())
        {
            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请输入原点坐标."));
            return;
        }
        if(lineEditZValue->text().isEmpty())
        {
            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请输入Z值."));
            return;
        }
        if(lineEditZ0Value->text().isEmpty())
        {
            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请输入Z0值."));
            return;
        }
        double nX0 = lineEditX0->text().toDouble();
        double nY0 = lineEditY0->text().toDouble();
        double nZ0 = lineEditZ0Value->text().toDouble();
        emit signal_recv_coordsystem(nX0, nY0, nZ0);

        /// 如果串口已经打开,先将其关闭
        if(m_SerialPort->isOpen())
        {
            m_SerialPort->clear();
            m_SerialPort->close();
        }
        /// 打开串口
        m_SerialPort->setPortName(m_SerialPortComboBox->currentText());///<设置串口名
        if(m_BaudRateComboBox->currentText() == "4800")
        {
            m_SerialPort->setBaudRate(QSerialPort::Baud4800, QSerialPort::AllDirections);
        }

        else if(m_BaudRateComboBox->currentText() == "9600")
        {
            m_SerialPort->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
        }
        else if(m_BaudRateComboBox->currentText() == "115200")
        {
            m_SerialPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
        }
        else if(m_BaudRateComboBox->currentText() == "256000")
        {
            m_SerialPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
        }

        m_SerialPort->setDataBits(QSerialPort::Data8);
        m_SerialPort->setStopBits(QSerialPort::OneStop);
        m_SerialPort->setParity(QSerialPort::NoParity);
        m_SerialPort->setFlowControl(QSerialPort::NoFlowControl);
        if(!m_SerialPort->open(QIODevice::ReadWrite))///<以ReadWrite模式打开串口
        {
            emit signal_send_loadinfo(QStringLiteral("打开串口失败."));
            return;
        }
        else
        {
            emit signal_send_loadinfo(QStringLiteral("打开串口成功."));
        }

        /// 发送最小深度
        int nMinDepth = lineEditRangeWaterMin->text().toInt();
        QString hex = QString("%1").arg(nMinDepth, 4, 16, QLatin1Char('0'));
        QString minInfo = "3A0303"+hex.left(2)+hex.right(2);
        QByteArray dataMin;
        convertStringToHex(minInfo, dataMin);
        m_SerialPort->write(dataMin);
        emit signal_send_loadinfo("Set DMin OK.");
#endif
}

void DeckUnit::slotStop()
{
    m_SerialPort->clear();
    m_SerialPort->close();

    /// 将端口号和波特率设置部分修改为不可编辑状态
    m_SerialPortComboBox->setEditable(true);
    m_BaudRateComboBox->setEditable(true);

    /// 初始化界面参数
    lineEditX0->setText("");
    lineEditY0->setText("");
    lineEditZ0Value->setText("");


    emit signal_stop_information();
    QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("关闭串口成功."));
}

void DeckUnit::TxVisit(bool flag)
{
//    if(flag)
//    {

    startTx();
//    }
//    else
//    {
//        stopTx();
//    }
}



void DeckUnit::startTx()
{
   QByteArray Txdata,dataOBS;
   QString command;
    //发送命令
    if(sondaryflag==1)
    {
        QString OBSNo1 = lineEditOBSMin->text();
        QString OBSNo2 = lineEditOBSMax->text();
        command="$T"+OBSNo1+":"+OBSNo2+"%";
        dataOBS=command.toLatin1();
        m_SerialPort->write(dataOBS);
        emit signal_send_loadinfo("Set Sonardyne Tx command !");
        emit signal_recv_sendsignal();  //发送的时候记录一个坐标

    }
    else
    {
        command="3A0105";
        convertStringToHex(command,Txdata);
        m_SerialPort->write(Txdata);
        emit signal_send_loadinfo("Set Tx command !");
    }
}

void DeckUnit::slotClickedStart()
{
    emit signal_recv_clicked_start();
}

void DeckUnit::stopTx()
{
    //发送命令
    char cmdTx[] = {0x3A,0x01,0x06};
    m_socket->write(cmdTx,3);

    m_SerialPort->write(cmdTx, 3);
}

void DeckUnit::socketStateChanged(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::ConnectedState)
    {
//        m_showTxtFunc(QStringLiteral("设置甲板机参数..."));
//        m_optWidget->setEnabled(true);
        //链接上之后设置参数
        //Repeat Interval 30seconds
        char cmdInterval[] = {0x3A,0x02,0x01,0x1E};
        m_socket->write(cmdInterval,3);

        //Repeat Times 30Times
        char cmdTimes[] = {0x3A,0x02,0x02,0x1E};
        m_socket->write(cmdTimes,3);
    }
    else if(state == QAbstractSocket::UnconnectedState)
    {
//        m_showTxtFunc(QStringLiteral("甲板机断开链接!"));
//        m_optWidget->setEnabled(false);
    }
}


void DeckUnit::slotReadyRead()
{
#if 0
    QByteArray  buf = m_socket->readAll();
    if(!buf.isEmpty())
    {
        bool bsetcommd = false;
        QString Commandcode;
        QString recestr = buf.toHex().toUpper();
        QString packstr=recestr.mid(0,6);
        if( packstr=="3A0103")
        {
//            bpackage=true;
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="03")
            {
//                setDmaxcommand();
            }
        }
        else if(packstr=="3A0104")
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="04")
            {
//                setReleaseCode();
            }
        }
        else if(packstr=="3A0108")
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="08")
            {
            }
        }
        else if(packstr=="3A0105")
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="05")
            {
                bsetcommd=true;
            }
        }
        else if(packstr=="3A010A")
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="0A")
            {
                bsetcommd=false;
            }
        }
        else if(packstr=="3A0307")
        {
            Commandcode=packstr.mid(4,2);
            QString Delaytime=recestr.mid(7,2);
            int value=Delaytime.toInt(NULL,16);
            emit signal_recv_Delaytime(value);
        }
    }
#endif

    /// 串口读取
    QByteArray buf;
    QString packstr,datastr,Commandcode,str1;
    QString comstrX,comstrY,comstrZ,strposX,strposY,strposZ;
    QString Xtime,Ytime,Ztime;
    int idxms,idyms,idzms;
    double fdx,fdy,fdz,fposX,fposY,fposZ;
    buf = m_SerialPort->readAll();

    sonardynestr += QString(buf);
    soundbuf = sonardynestr;
//    sonardynestr=QString(soundbuf);
//    qDebug() << "buf:" << str1;
    qDebug() << "sonardynestr:" << sonardynestr;
    if((sonardynestr.contains("Sonardyne Ltd Ver")))
    {

        emit signal_send_loadinfo(sonardynestr);
        sondaryflag=1;
        buf.clear();
        sonardynestr.clear();

    }

    else if((sonardynestr.contains("Range"))&(sonardynestr.contains("m")))
    {
        emit signal_send_loadinfo(sonardynestr);
        sondaryflag=1;
        int indexbegin=sonardynestr.indexOf("=")+1;
        int indexend=sonardynestr.indexOf("m");
        QString rangeinfo=(sonardynestr.mid(indexbegin,indexend-indexbegin));
        float range=(sonardynestr.mid(indexbegin,indexend-indexbegin)).toFloat();

        double ZValue = lineEditZValue->text().toDouble();
        double X0     = lineEditX0->text().toDouble();
        double Y0     = lineEditY0->text().toDouble();
        emit signal_recv_recvsignal();
        emit signal_Sondary_recv_range(range,ZValue,X0,Y0); //接收到的时候记录一个坐标

        sonardynestr.clear();

        buf.clear();

    }
    else if((sonardynestr.contains("TPDR")))
    {
        buf.clear();
    }
    else if((!buf.isEmpty())&(sondaryflag==0))
    {

        if ((buf.contains("#"))&(!buf.contains("=")))
        {
            soundbuf.clear();
            soundbuf.append(buf);
        }
        //第二种：无头无尾且变量已有内容，数据中段部分，继续附加即可
        if ((!buf.contains("#"))&(!buf.contains("="))&(!soundbuf.isNull()))
        {
            soundbuf.append(buf);
        }

        //第四种：有头有尾（一段完整的内容），先清空原有内容，再附加，然后输出，最后清空变量
        if ((buf.contains("#"))&(buf.contains("=")))
            //    if(!buf.isEmpty())
        {
            emit signal_send_loadinfo("SoundComm receive:"+soundbuf);
            oriposX=lineEditX0->text().toDouble();
            oriposY=lineEditY0->text().toDouble();
            oriposZ=lineEditZ0Value->text().toDouble();
            QStringList list = soundbuf.split("\n");
//            QStringList list = ui->Recetext->toPlainText().split("\n");
            int ilistcount=list.count();
            if(ilistcount>3)
            {
                for(int i=0;i<ilistcount;i++)
                {
                    if(((i+1)%3)==1)
                    {
                        comstrX=list[i];
                        if (comstrX.contains("#"))
                        {
                            int index=comstrX.indexOf("=");
                            if(index>0)
                            {
                                Xtime=comstrX.mid(12,8);
                                QTime Xbegin_time =QTime::fromString(Xtime, "hh:mm:ss");
                                QTime Ybegin_time=Xbegin_time.addSecs(2);
                                nextpagetime = Ybegin_time.toString("hh:mm:ss");

                                QString dx=comstrX.mid(index+1,8);
                                idxms=dx.toInt();
                                //                        if(300<idxms<600)
                                if((idxms>300)&(idxms<600))
                                {
                                    fdx=idxms/(300.0/(-100.0));
                                }
                                //                        else if(600<idxms<900)
                                else if((idxms>600)&(idxms<900))
                                {
                                    fdx=idxms/(300.0/100.0);
                                }

                            }

                            else
                            {
                                fdx=-oriposX;
                            }
                            //                    i=i+1;
                        }}
                    if(((i+1)%3)==2)
                    {
                        comstrY=list[i];
                        if (comstrY.contains("#"))
                        {
                            int index=comstrY.indexOf("=");
                            if(index>0)
                            {
                                Ytime=comstrY.mid(12,8);
                                QTime Ybegin_time =QTime::fromString(Ytime, "hh:mm:ss");
                                if(Ytime==nextpagetime)
                                {

                                    QTime Zbegin_time=Ybegin_time.addSecs(2);
                                    nextpagetime = Zbegin_time.toString("hh:mm:ss");
                                    QString dy=comstrY.mid(index+1,8);
                                    idyms=dy.toInt();
                                    if((idyms>300)&(idyms<600))
                                    {
                                        fdy=idyms/(300.0/(-100.0));
                                    }
                                    else if((idyms>600)&(idyms<900))
                                    {
                                        fdy=idyms/(300.0/100.0);
                                    }

                                }
                                else
                                {
                                    fdy=-oriposY;

                                }

                            }
                        }
                    }
                    if(((i+1)%3==0))
                    {
                        comstrZ=list[i];
                        if (comstrZ.contains("#"))
                        {
                            int index=comstrZ.indexOf("=");
                            if(index>0)
                            {
                                Ztime=comstrZ.mid(12,8);
                                QTime Zbegin_time =QTime::fromString(Ztime, "hh:mm:ss");
                                if(Ztime==nextpagetime)
                                {
                                    QString dz=comstrZ.mid(index+1,8);

                                    idzms=dz.toInt();
                                    if((idzms>300)&(idzms<600))
                                    {
                                        fdz=idzms/(300.0/(-100.0));
                                    }
                                    else if((idzms>600)&(idzms<900))
                                    {
                                        fdz=idzms/(300.0/100.0);
                                    }

                                }
                                else
                                {
                                    fdz=-oriposZ;
                                }

                            }
                        }
                        else
                        {
                            fdz=-oriposZ;
                        }

                        fposX=oriposX+fdx;
                        fposY=oriposY+fdy;
                        fposZ=oriposZ+fdz;
                        strposX=QString::number(fposX,'f',2);
                        strposY=QString::number(fposY,'f',2);
                        strposZ=QString::number(fposZ,'f',2);
                        emit signal_recv_coordAfterCalculator(fposX, fposY, fposZ);
                        emit signal_send_loadinfo("SoundComm receive Pos:"+strposX+","+strposY+","+strposZ);
                    }
                }
            }
            buf.clear();
            soundbuf.clear();
            list.clear();

        }
        bool bsetcommd = false;
        QString Commandcode;
        QString recestr = buf.toHex().toUpper();
        QString packstr=recestr.mid(0,6);
//        qDebug() << "recestr:" << recestr;
        if( packstr=="3A0103")
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="03")
            {
                /// 发送最大深度
                int nMaxDepth = lineEditRangeWaterMax->text().toInt();
                QString hexMax = QString("%1").arg(nMaxDepth, 4, 16, QLatin1Char('0'));
                QString maxInfo = "3A0304"+hexMax.left(2)+hexMax.right(2);
                QByteArray dataMax;
                convertStringToHex(maxInfo, dataMax);
                m_SerialPort->write(dataMax);

                emit signal_send_loadinfo("set Dmin ok!3A0103");
            }
        }
        else if(packstr=="3A0104")
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="04")
            {
                /// 发送OBS水深信号
                setReleaseCode();
                QString OBSMin = lineEditOBSMin->text();
                QString OBSMax = lineEditOBSMax->text();
                emit signal_send_OBS_info(OBSMin, OBSMax);
                emit signal_send_loadinfo("Set Dmax ok!3A0104");
            }
        }
        else if(packstr=="3A0108")
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="08")

            {

                if(restflag==1)
                {
                    startTx();
                    restflag=0;
                    emit signal_send_loadinfo("Set Release code ok!3A0108");

                }
                else if(restflag==2)
                {
                    startTx();
                    restflag=0;
                    emit signal_send_loadinfo("Set Reset code ok!3A0108");

                }
                else{
                    emit signal_send_loadinfo("Set Release code ok!3A0108");
                    emit signal_send_loadinfo("Set duck param ok!");
                }
            }
        }
        else if(packstr=="3A0105")  ///发的时候记录一个坐标
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="05")
            {
                bsetcommd=true;
                flag = 0;
                emit signal_recv_sendsignal();
                emit signal_send_loadinfo("set Tx Command ok!3A0105");

            }
        }
        else if(packstr=="3A010A")
        {
            Commandcode=packstr.mid(4,2);
            if(Commandcode=="0A")
            {
                double ZValue = lineEditZValue->text().toDouble();
//                double X0     = lineEditX0->text().toDouble();
//                double Y0     = lineEditY0->text().toDouble();
               qDebug() << "Z:" << ZValue;
                bsetcommd=false;
                emit signal_send_loadinfo("No Response Received!3A010A");
//                if(flag == 0)
//                {
//                    int value = 10;
//                	emit signal_recv_Delaytime(value, ZValue, X0, Y0);
//                	flag = 1;
//				}
            }
        }
        else if(packstr=="3A0407")  ///收的时候记录一个坐标
        {
            Commandcode=packstr.mid(4,2);
            QString Delaytime=recestr.mid(6,8);
            int value=Delaytime.toInt(NULL,16);

            float num=value/10.0;
            QString s = QString("%1").arg(num);
            qDebug() << "delT:" << value;
//            flag = 0;
            emit signal_send_loadinfo("Received Time!"+s+"ms");
//            GpsCoord nGPSCoord;
//            nGPSCoord.x         = DataManager::m_gpsCord.at(DataManager::m_gpsCord.length()-1).x;
//            nGPSCoord.y         = DataManager::m_gpsCord.at(DataManager::m_gpsCord.length()-1).y;
//            nGPSCoord.utc_sec   = DataManager::m_gpsCord.at(DataManager::m_gpsCord.length()-1).utc_sec;
//            m_cpsCoord.append(nGPSCoord);
            if(flag == 0)
            {
            	double ZValue = lineEditZValue->text().toDouble();
                double X0     = lineEditX0->text().toDouble();
           	 	double Y0     = lineEditY0->text().toDouble();

                emit signal_recv_recvsignal();
                emit signal_recv_Delaytime(value, ZValue, X0, Y0);
				flag=1;
			}
         }

        buf.clear();
//        sonardynestr.clear();
//        soundbuf.clear();
    }
}

void DeckUnit::setReleaseCode()
{
    QString command;
    QByteArray dataOBS;
    QString OBSMin = lineEditOBSMin->text();
    QString OBSMax = lineEditOBSMax->text();
    if(OBSMin.length() == 1)
        OBSMin = "0"+OBSMin;
    if(OBSMax.length() == 1)
        OBSMax = "0" + OBSMax;
    command="3A0308"+OBSMin+OBSMax;
    convertStringToHex(command,dataOBS);
    qDebug() << "releaseNo:"<<dataOBS;
    m_SerialPort->write(dataOBS);
}

void DeckUnit::slotSondaryFunction()
{
    QString command;
    QByteArray dataOBS;

    if(m_SerialPort->isOpen())
    {
        m_SerialPort->clear();
        m_SerialPort->close();
    }
    /// 打开串口
    m_SerialPort->setPortName(m_SerialPortComboBox->currentText());///<设置串口名
    if(m_BaudRateComboBox->currentText() == "4800")
    {
        m_SerialPort->setBaudRate(QSerialPort::Baud4800, QSerialPort::AllDirections);
    }

    m_SerialPort->setDataBits(QSerialPort::Data8);
    m_SerialPort->setStopBits(QSerialPort::OneStop);
    m_SerialPort->setParity(QSerialPort::NoParity);
    m_SerialPort->setFlowControl(QSerialPort::NoFlowControl);
    if(!m_SerialPort->open(QIODevice::ReadWrite))///<以ReadWrite模式打开串口
    {
        emit signal_send_loadinfo(QStringLiteral("打开Sonardyne串口失败."));
        return;
    }
    else
    {
        emit signal_send_loadinfo(QStringLiteral("打开Sonardyne串口成功."));

        double nX0 = lineEditX0->text().toDouble();
        double nY0 = lineEditY0->text().toDouble();
        double nZ0 = lineEditZ0Value->text().toDouble();
        emit signal_recv_coordsystem(nX0, nY0, nZ0);
        QString OBSNo1 = lineEditOBSMin->text();
        QString OBSNo2 = lineEditOBSMax->text();

        //    qDebug() << "OBSMax:"<<OBSMax;
        command="$T"+OBSNo1+":"+OBSNo2+"%";
        dataOBS=command.toLatin1();

        m_SerialPort->write(dataOBS);
         emit signal_send_OBS_info(OBSNo1, OBSNo2);
        emit signal_send_loadinfo("Set Sonardyne OK.");
        sondaryflag=1;
    }
}

void DeckUnit::slotSoundcommFunction()
{
//    QString command;

    if(m_SerialPort->isOpen())
    {
        m_SerialPort->clear();
        m_SerialPort->close();
    }
    /// 打开串口
    m_SerialPort->setPortName(m_SerialPortComboBox->currentText());///<设置串口名
    if(m_BaudRateComboBox->currentText() == "9600")
    {
        m_SerialPort->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
    }
    else if(m_BaudRateComboBox->currentText() == "115200")
    {
        m_SerialPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    }
//    else if(m_BaudRateComboBox->currentText() == "256000")
//    {
//        m_SerialPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
//    }

    m_SerialPort->setDataBits(QSerialPort::Data8);
    m_SerialPort->setStopBits(QSerialPort::OneStop);
    m_SerialPort->setParity(QSerialPort::NoParity);
    m_SerialPort->setFlowControl(QSerialPort::NoFlowControl);
    if(lineEditX0->text().isEmpty() || lineEditY0->text().isEmpty())
    {
        QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请输入参考点坐标."));
        return;
    }
    double nX0 = lineEditX0->text().toDouble();
    double nY0 = lineEditY0->text().toDouble();
    double nZ0 = lineEditZ0Value->text().toDouble();
    emit signal_recv_coordsystem(nX0, nY0, nZ0);
    if(!m_SerialPort->open(QIODevice::ReadWrite))///<以ReadWrite模式打开串口
    {
        emit signal_send_loadinfo(QStringLiteral("打开声通讯串口失败."));
        return;
    }
    else
    {
        /// 将端口号和波特率设置部分修改为不可编辑状态
        m_SerialPortComboBox->setEditable(false);
        m_BaudRateComboBox->setEditable(false);
        emit signal_send_loadinfo(QStringLiteral("打开声通讯串口成功."));
    }
//    restflag=2;
}

void DeckUnit::creatWg()
{
    QStringList nBaudRateList;
    nBaudRateList << "115200" << "4800"<<"9600" ;

    QVBoxLayout* mainLayout = new QVBoxLayout();

    QGroupBox* groupBox = new QGroupBox(QStringLiteral("甲板机通信"));

    QLabel* labelSerialPort = new QLabel(QStringLiteral("串口号"));
    m_SerialPortComboBox = new QComboBox;
    connect(m_SerialPortComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(slotCurrTextChange(QString)));
    QLabel* labelBaudRate   = new QLabel(QStringLiteral("波特率"));
    m_BaudRateComboBox = new QComboBox;
    connect(m_BaudRateComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(slotRateCurrTextChange(QString)));
    m_BaudRateComboBox->addItems(nBaudRateList);

    QHBoxLayout* partNameLayout = new QHBoxLayout;
    partNameLayout->addWidget(labelSerialPort);
    partNameLayout->addWidget(m_SerialPortComboBox);

    QHBoxLayout* BaudRateLayout = new QHBoxLayout;
    BaudRateLayout->addWidget(labelBaudRate);
    BaudRateLayout->addWidget(m_BaudRateComboBox);

    QLabel* labelRangeWater = new QLabel(QStringLiteral("水深范围(m)"));
    lineEditRangeWaterMin = new QLineEdit;
    QLabel* labelRangeInfo = new QLabel("-");
    lineEditRangeWaterMax = new QLineEdit;

    QHBoxLayout* RangeWaterLayout = new QHBoxLayout;
    RangeWaterLayout->addWidget(labelRangeWater);
    RangeWaterLayout->addWidget(lineEditRangeWaterMin);
    RangeWaterLayout->addWidget(labelRangeInfo);
    RangeWaterLayout->addWidget(lineEditRangeWaterMax);

    QLabel* labelOBS = new QLabel(QStringLiteral("OBS编码:"));
    lineEditOBSMin = new QLineEdit();
    QLabel* LabelOBSRange =  new QLabel("-");
    lineEditOBSMax = new QLineEdit();

    QHBoxLayout* OBSLayout = new QHBoxLayout;
    OBSLayout->addWidget(labelOBS);
    OBSLayout->addWidget(lineEditOBSMin);
    OBSLayout->addWidget(LabelOBSRange);
    OBSLayout->addWidget(lineEditOBSMax);

    QLabel* labelZValue = new QLabel(QStringLiteral("甲板单元探头水深(m):"));
    lineEditZValue      = new QLineEdit;
    QHBoxLayout* nZValueLayout = new QHBoxLayout;
    nZValueLayout->addWidget(labelZValue);
    nZValueLayout->addWidget(lineEditZValue);

    QLabel* labelZ0Value= new QLabel(QStringLiteral("定位目标投放点位(m):"));

    QLabel* labelX0 = new QLabel(QStringLiteral("X0:"));
    lineEditX0 = new QLineEdit;
    QLabel* labelY0 = new QLabel(QStringLiteral("Y0:"));
    lineEditY0 = new QLineEdit;
    QHBoxLayout* nX0ValueLayout = new QHBoxLayout;
    nX0ValueLayout->addWidget(labelX0);
    nX0ValueLayout->addWidget(lineEditX0);
    nX0ValueLayout->addWidget(labelY0);
    nX0ValueLayout->addWidget(lineEditY0);

    QHBoxLayout* nY0ValueLayout = new QHBoxLayout;
    nY0ValueLayout->addWidget(labelY0);
    nY0ValueLayout->addWidget(lineEditY0);

    QLabel* labelH0 = new QLabel(QStringLiteral("H0:"));
    lineEditZ0Value     = new QLineEdit;
    QHBoxLayout* nH0ValueLayout = new QHBoxLayout;
    nH0ValueLayout->addWidget(labelH0);
    nH0ValueLayout->addWidget(lineEditZ0Value);

    QGridLayout* pointLayout = new QGridLayout;
    pointLayout->addWidget(labelZ0Value, 0, 0);
    pointLayout->addLayout(nX0ValueLayout, 1, 0);
    pointLayout->addLayout(nH0ValueLayout, 2, 0);

    m_optWidget = new QWidget();
    checkBoxSetup   = new QPushButton(QStringLiteral("参数设定"));
    checkBoxStop    = new QPushButton(QStringLiteral("停止"));
    checkBoxStartTX = new QPushButton(QStringLiteral("开始TX"));
    pushButtonStart = new QPushButton(QStringLiteral("开始解算"));
    SondaryButton  = new QPushButton(QStringLiteral("设置黄棒子"));
    SoundcommButton = new QPushButton(QStringLiteral("设置声通讯"));
    connect(checkBoxSetup,&QPushButton::clicked, this,&DeckUnit::slotConnect);
    connect(checkBoxStop, &QPushButton::clicked, this, &DeckUnit::slotStop);
    connect(checkBoxStartTX,&QPushButton::clicked, this,&DeckUnit::TxVisit);
    connect(pushButtonStart,&QPushButton::clicked, this, &DeckUnit::slotClickedStart);
    connect(SondaryButton, &QPushButton::clicked, this, &DeckUnit::slotSondaryFunction);
    connect(SoundcommButton,&QPushButton::clicked, this, &DeckUnit::slotSoundcommFunction);

    QHBoxLayout* nHBoxLayout = new QHBoxLayout;
    nHBoxLayout->addWidget(checkBoxSetup);
    nHBoxLayout->addWidget(checkBoxStop);

    QHBoxLayout* nHBoxLayoutTx = new QHBoxLayout;
    nHBoxLayoutTx->addWidget(checkBoxStartTX);
    nHBoxLayoutTx->addWidget(pushButtonStart);

    QHBoxLayout* nAddLayout = new QHBoxLayout;
    nAddLayout->addWidget(SoundcommButton);
    nAddLayout->addWidget(SondaryButton);

    QVBoxLayout* VBoxLayout = new QVBoxLayout;
    VBoxLayout->addLayout(partNameLayout);
    VBoxLayout->addLayout(BaudRateLayout);
    VBoxLayout->addLayout(RangeWaterLayout);
    VBoxLayout->addLayout(OBSLayout);
    VBoxLayout->addLayout(nZValueLayout);
    VBoxLayout->addLayout(pointLayout);
    VBoxLayout->addLayout(nHBoxLayout);
    VBoxLayout->addLayout(nHBoxLayoutTx);
    VBoxLayout->addLayout(nAddLayout);


    QWidget* nDeckUnitWidget = new QWidget;
    nDeckUnitWidget->setMaximumWidth(260);
    nDeckUnitWidget->setLayout(VBoxLayout);

    QScrollArea* nScrollArea = new QScrollArea;
    nScrollArea->setWidget(nDeckUnitWidget);

    QVBoxLayout* nVboxLayout = new QVBoxLayout;
    nVboxLayout->addWidget(nScrollArea);

    groupBox->setLayout(nVboxLayout);
    mainLayout->addWidget(groupBox);
    this->setLayout(mainLayout);
}

void DeckUnit::slotCurrTextChange(QString)
{
    m_SerialPortComboBox->setEditable(false);
}

void DeckUnit::slotRateCurrTextChange(QString)
{
    m_BaudRateComboBox->setEditable(false);
}
