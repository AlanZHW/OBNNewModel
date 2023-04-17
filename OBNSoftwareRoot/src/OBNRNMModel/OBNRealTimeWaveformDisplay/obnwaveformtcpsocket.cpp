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
    QByteArray batArrayDatum = "01000000";
    bool OK = false;
    int nDataDatum = batArrayDatum.toInt(&OK, 16);
    int nData      = batArray.toInt(&OK, 16);
    int n_dataFinal;
    if(batArray[0]&0xF)
    {
        n_dataFinal= nData-nDataDatum;
    }
    else
    {
        n_dataFinal = nData;
    }
    qDebug() << "nDataDatum = " << nDataDatum << "\t nData = " << nData << "\t batArray = " << batArray << "\t n_dataFinal = " << n_dataFinal;
    return n_dataFinal;
}

/// ======
void OBNWaveformTcpSocket::startCollection()
{
    if(this->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        this->write(realTimeWaveStartCollectionCmd, sizeof(realTimeWaveStartCollectionCmd));
    }
}

void OBNWaveformTcpSocket::exitCollection()
{
    if(this->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        this->write(realTimeWaveEndCollectionCmd, sizeof(realTimeWaveEndCollectionCmd));
    }
}

void OBNWaveformTcpSocket::startDisplayWaveform()
{
    if(this->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        this->write(realTimeWaveStartCmd, sizeof(realTimeWaveStartCmd));
    }
}

void OBNWaveformTcpSocket::exitDisplayWaveform()
{
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
