#ifndef OBNREADLOGHREAD_H
#define OBNREADLOGHREAD_H

#include <QFile>
#include <QColor>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>

typedef struct suct_log_inform{

    suct_log_inform()
    {
        batF      = 0.0;
        TNum      = 0.0;
        PNum      = 0.0;
        ThetaNum  = 0.0;
        GammaNum  = 0.0;
        AzNum     = 0.0;
        timeInform= "";
    }
    double batF;
    double TNum;
    double PNum;
    double ThetaNum;
    double GammaNum;
    double AzNum;
    QString timeInform;
}SuctLOGInform;

typedef struct {
    QString nNodeName;
    QColor  nLineColor;
    QList<SuctLOGInform> nSuctLogInformList;
}SuctLOGDrawInform;

class OBNReadLoghread : public QThread
{
    Q_OBJECT
public:
    explicit OBNReadLoghread(QObject *parent = nullptr);
    void setCurrentLogFileList(const QStringList& _logfNameList);
signals:
    void signalCurrentReadProgress(const int& _progressValue);
    void signalCurrentVisualizationInforms(const QList<SuctLOGDrawInform>& _logDataInformList);
protected:
    void run();
private:
    QStringList m_logfNameList;
};

#endif // OBNREADLOGHREAD_H
