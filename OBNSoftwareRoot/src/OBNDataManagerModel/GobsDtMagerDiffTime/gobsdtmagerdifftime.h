#ifndef GOBSDTMAGERDIFFTIME_H
#define GOBSDTMAGERDIFFTIME_H

#include <QDir>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

//#include "FrftProcess.h"
//#include "mclmcr.h"
#include "macro.h"
#include "projectarea.h"
#include <QComboBox>
#include <QDateTime>
#include <QFileDialog>
#include "displayacudata.h"
#include "visitacufile.h"
#include "displayfrftdat.h"
#include "gobsdtmagerdifftime_global.h"

//====路径分割符号
#define PATH_SPLITER "\\"
#define  DataFileList       "DataFile.lst"
#define  DataFileFilter     "[0-9A-F]+\\.[0-9A-F]+"
#define DateTime_Format_    "yyyy-MM-dd HH:mm:ss.zzz"

namespace Ui {
class GobsDtMagerDiffTime;
}

class GOBSDTMAGERDIFFTIME_EXPORT GobsDtMagerDiffTime : public QDialog
{
    Q_OBJECT

public:
    explicit GobsDtMagerDiffTime(QWidget *parent = 0);
    ~GobsDtMagerDiffTime();
    void setInputfPath(const QString&);
    void setProjInfo(ProjectInfo*);
//    void setProjInfo(const QString&, const QString&);
    void CallMatlabFunction(QString &pWorkPathName, QString &pACUFileName);
public slots:
    void slotReadACUSuccess(QStringList);

private slots:
    void on_PushBrowse_clicked();
    void on_PushImplement_clicked();

    void on_buttonConfig_clicked();

private:
    Ui::GobsDtMagerDiffTime *ui;
    QString m_InputfPath;
    QString m_errString;
    QString m_ACUFileName;
    ProjectInfo *mProjectInfo;
    int     m_Row, m_Column;
    QStringList m_ErrorTimes;
    int     TotalAcufileCont;
    VisitACUFile *tmpVistAcuFile;
    QList<AcufileInfo> AcufInfoList;
};

#endif // GOBSDTMAGERDIFFTIME_H
