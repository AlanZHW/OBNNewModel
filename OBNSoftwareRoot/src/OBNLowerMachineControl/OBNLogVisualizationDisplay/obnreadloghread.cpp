#include "obnreadloghread.h"

#include <QMetaType>

/// ====== 构造函数
OBNReadLoghread::OBNReadLoghread(QObject *parent) : QThread(parent)
{
    qRegisterMetaType<QList<SuctLOGDrawInform>>("QList<SuctLOGDrawInform>");//注册diskInformation类型
}

void OBNReadLoghread::setCurrentLogFileList(const QStringList& _logfNameList)
{
    m_logfNameList = _logfNameList;
}

/// ====== 读取Log日志文件线程
void OBNReadLoghread::run()
{
    /// ======
    if(0 == m_logfNameList.count())
    {
        return;
    }
    QList<SuctLOGDrawInform> nLogInformList;
    /// ======
    for(int iFileNO = 0; iFileNO < m_logfNameList.count(); iFileNO ++)
    {
        SuctLOGDrawInform nALogFileInformList;
        nALogFileInformList.nLineColor = QColor::fromRgb(rand()%256,rand()%256,rand()%256);
        QFileInfo fileInform(m_logfNameList[iFileNO]);
        nALogFileInformList.nNodeName  = fileInform.fileName().replace("."+fileInform.suffix(), "");


        QFile openFile(m_logfNameList[iFileNO]);
        if(!openFile.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug() << "open file error";
            return ;
        }

        /// ======
        QTextStream in(&openFile);
        /// ======
        QString ReadLine = in.readLine();

        QStringList nReadLineList;
        QStringList nScreenDataList;
        while(!in.atEnd())
        {
            /// ======读取一行数据
            ReadLine = in.readLine().trimmed().replace(QRegExp("\\s+"), "");
            if(-1 == ReadLine.indexOf("#"))
            {
                continue;
            }
            /// ======
            SuctLOGInform n_suctLOGInform;

            /// ======通过","进行截取数据
            nReadLineList = ReadLine.split(",");
            /// ======筛选当前数据
            for(int iLst = 0; iLst < nReadLineList.count(); iLst ++)
            {
                if(-1 != nReadLineList[iLst].indexOf("#"))
                {
                    n_suctLOGInform.timeInform = nReadLineList[iLst].mid(1, 5);
                }
                if(-1 != nReadLineList[iLst].indexOf("BAT_V="))
                {
                    nScreenDataList = nReadLineList[iLst].split("=");
                    n_suctLOGInform.batF = nScreenDataList[1].toDouble();
                }
                if(-1 != nReadLineList[iLst].indexOf("T="))
                {
                    nScreenDataList = nReadLineList[iLst].split("=");
                    n_suctLOGInform.TNum = nScreenDataList[1].toDouble();
                }
                if(-1 != nReadLineList[iLst].indexOf("P="))
                {
                    nScreenDataList = nReadLineList[iLst].split("=");
                    n_suctLOGInform.PNum = nScreenDataList[1].toDouble();
                }
                if(-1 != nReadLineList[iLst].indexOf("Theta="))
                {
                    nScreenDataList = nReadLineList[iLst].split("=");
                    n_suctLOGInform.ThetaNum = nScreenDataList[1].toDouble();
                }
                if(-1 != nReadLineList[iLst].indexOf("Gamma="))
                {
                    nScreenDataList = nReadLineList[iLst].split("=");
                    n_suctLOGInform.GammaNum = nScreenDataList[1].toDouble();
                }
                if(-1 != nReadLineList[iLst].indexOf("Az="))
                {
                    nScreenDataList = nReadLineList[iLst].split("=");
                    n_suctLOGInform.AzNum = nScreenDataList[1].toDouble();
                }
            }
            nALogFileInformList.nSuctLogInformList.append(n_suctLOGInform);
        }

        /// ====== 关闭打开的文件
        openFile.close();

        /// ======
        nLogInformList.append(nALogFileInformList);

        emit signalCurrentReadProgress(iFileNO+1);
    }

    /// ====== 发送读取的数据信息信号
    emit signalCurrentVisualizationInforms(nLogInformList);
#if 0
    for(int iList = 0; iList < nLogInformList.count(); iList ++)
    {
        for(int jList = 0; jList < nLogInformList.at(iList).nSuctLogInformList.count(); jList ++)
        {
            qDebug() << "iList = "   << iList << "\t jList = " << jList
                     << "\t batF = " << nLogInformList.at(iList).nSuctLogInformList.at(jList).batF
                     << "\t TNum = " << nLogInformList.at(iList).nSuctLogInformList.at(jList).TNum
                     << "\t PNum = " << nLogInformList.at(iList).nSuctLogInformList.at(jList).PNum
                     << "\t ThetaNum = " << nLogInformList.at(iList).nSuctLogInformList.at(jList).ThetaNum
                     << "\t GammaNum = " << nLogInformList.at(iList).nSuctLogInformList.at(jList).GammaNum
                     << "\t AzNum = " << nLogInformList.at(iList).nSuctLogInformList.at(jList).AzNum
                     << "\t timeInform = " << nLogInformList.at(iList).nSuctLogInformList.at(jList).timeInform;
        }
    }
#endif
}
