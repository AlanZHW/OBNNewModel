#ifndef EXPORTSEGYDLG_H
#define EXPORTSEGYDLG_H

#include <QDialog>
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QTextBrowser>
#include <QTableWidget>
#include <QFileDialog>

#include "macro.h"
#include "publicHostInform.h"
#include "projectarea.h"
#include "shotlinedlg.h"
#include "spsfiles.h"
#include "projectarea.h"
#include "obnexportsegy_global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ExportSegyDlg; }
QT_END_NAMESPACE

class OBNEXPORTSEGY_EXPORT ExportSegyDlg : public QDialog
{
    Q_OBJECT

public:
    ExportSegyDlg(QWidget *parent = nullptr);
    ~ExportSegyDlg();
    void setProjectInfo(const ProjectInfo &projInfo);

private slots:
    void on_dataPathBrwser_clicked();

    void on_outputPathBrwser_clicked();

    //开始运行抽取道集
    void on_startBtn_clicked();

    void on_CloseBtn_clicked();

    void on_ShotLineBrwser_clicked();

    void on_areasCbx_currentIndexChanged(const QString &arg1);

    void on_recvRbtn_clicked(bool checked);

    void on_shotRbtn_clicked(bool checked);

    void on_fromLineSpx_valueChanged(int arg1);

    void on_toLineSpx_valueChanged(int arg1);

    void on_fromStaSpx_valueChanged(int arg1);

    void on_toStaSpx_valueChanged(int arg1);

private:
    /// ====== 根据当前项目初始化
    void initByProject();
    /// ======
    void updateScopeInfo();
    /// ====== 输出Job文件到工区目录
    /// 参数说明: jobFile:  Job文件名
    ///          paramter: Job参数信息
    bool saveJobParameter(const QString &jobFile,const ExportSegyParameter &paramter);

private:
    ProjectInfo         m_projInfo;
    ExportSegyParameter m_exportParameters;
    ShotLineDlg        *m_shotLineDlg;
    AreaDataInfo       *m_areaDataInfo;
    Ui::ExportSegyDlg *ui;
};
#endif // EXPORTSEGYDLG_H
