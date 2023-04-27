#include "obnwaveformtcpsocket.h"

OBNWaveformTcpSocket::OBNWaveformTcpSocket(const QString& _ip, const int& _prot):
    m_ip(_ip), m_port(_prot)
{
    /// ====== 链接成功信号
    connect(this,&OBNWaveformTcpSocket::connected, this, [=](){
        qDebug()<< __LINE__ << "\t" <<__FUNCTION__<<QThread::currentThreadId();
    });

    /// ====== 断开链接信号
    connect(this,&OBNWaveformTcpSocket::disconnected,this, [=](){
        emit sig_connect(3000);
    });

    /// ====== 获取数据信号
    connect(this,&OBNWaveformTcpSocket::readyRead,this, [=](){
#if 1
        m_dataInform += this->readAll();
#else
        m_dataInform += "3A0D5BFFDCA0000D890012BDFCB2D0";
#endif
//        qDebug() << "m_dataInform = " << m_dataInform;
    });
    connectHost(m_ip, m_port);

    m_timer.setInterval(5);
    connect(&m_timer, &QTimer::timeout, this, [=](){

        QString textInform = QString::fromLatin1(m_dataInform.toHex());

        QByteArray XByteArray, YByteArray, ZByteArray, HByteArray;
        int index = textInform.indexOf(WAVEFORM_HEAD);
        int XNum = 0, YNum = 0, ZNum = 0, HNum = 0;
        if(-1 != index)
        {
            textInform = textInform.mid(index, 30);
            /// ====== 删除已经处理过的数据
            m_dataInform.replace(0, index + 30, "");

            XByteArray = textInform.mid(6,  6).toLatin1();
            XNum = calculateMeasureInform(XByteArray);

            YByteArray = textInform.mid(12, 6).toLatin1();
            YNum = calculateMeasureInform(YByteArray);

            ZByteArray = textInform.mid(18, 6).toLatin1();
            ZNum = calculateMeasureInform(ZByteArray);

            HByteArray = textInform.mid(24, 6).toLatin1();
            HNum = calculateMeasureInform(HByteArray);
            /// ====== 增加点信号
            emit sig_curent_data(XNum, YNum, ZNum, HNum);
        }
    });
    m_timer.start();
}

int OBNWaveformTcpSocket::calculateMeasureInform(QByteArray batArray)
{
//    QByteArray batArrayDatum = "01000000";
//    bool OK = false;
//    int nDataDatum = batArrayDatum.toInt(&OK, 16);
//    int nData      = batArray.toInt(&OK, 16);
//    int n_dataFinal;
//    if(batArray[0]&0xF)
//    {
//        n_dataFinal= nData-nDataDatum;
//    }
//    else
//    {
//        n_dataFinal = nData;
//    }
//    qDebug() << "nDataDatum = " << nDataDatum << "\t nData = " << nData << "\t batArray = " << batArray << "\t n_dataFinal = " << n_dataFinal;

    QByteArray batArrayDatum = "01000000";
    bool OK = false;
    int n_dataFinal;
    int byte2 = batArray.mid(4, 2).toInt(&OK,16);
    int byte1 = batArray.mid(2, 2).toInt(&OK,16);
    int byte0 = batArray.mid(0, 2).toInt(&OK,16);
    qint32 value = byte2 << 16 | byte1 << 8 | byte0;

    if (value & 0x00800000) // MSB is set, indicating negative value
        value -= 0x01000000; // Adjust value to the correct negative value
    n_dataFinal = value;
    return n_dataFinal;
}

/// ======
void OBNWaveformTcpSocket::startCollection()
{
    qDebug() << "开始采集";
    if(this->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        this->write(realTimeWaveStartCollectionCmd, sizeof(realTimeWaveStartCollectionCmd));
    }
}

void OBNWaveformTcpSocket::exitCollection()
{
    qDebug() << "退出采集";
    if(this->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        this->write(realTimeWaveEndCollectionCmd, sizeof(realTimeWaveEndCollectionCmd));
    }
}

void OBNWaveformTcpSocket::startDisplayWaveform()
{
    qDebug() << "打开实时波形";
    if(this->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        this->write(realTimeWaveStartCmd, sizeof(realTimeWaveStartCmd));
    }
}

void OBNWaveformTcpSocket::exitDisplayWaveform()
{
    qDebug() << "关闭实时波形";
    if(this->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        this->write(realTimeWaveEndCmd, sizeof(realTimeWaveEndCmd));
    }
}

/// ======
void OBNWaveformTcpSocket::connectHost(const QString& ip, int port)
{
    this->connectToHost(ip, port);
    this->waitForConnected();
}

void OBNWaveformTcpSocket::slot_startConnect()   ///<
{
    this->abort();
    this->connectToHost(m_ip, m_port);
    emit sig_connect(3000);
    qDebug()<<__FUNCTION__<<QThread::currentThreadId();
}
