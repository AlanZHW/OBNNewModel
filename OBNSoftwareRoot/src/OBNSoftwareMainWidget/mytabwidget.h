#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QDir>
#include <QDrag>
#include <QDebug>
#include <QPainter>
#include <QWidget>
#include <QMimeData>
#include <QTabWidget>

#include "../OBNOtherLibraries/Core/projectarea.h"
#include "mytabbar.h"
#include "mytabpopup.h"

#include "rnmanager.h"
#include "linemanager.h"
#include "obndisplaysegy.h"
#include "gpositionsystem.h"
#include "gobsdtmagerdifftime.h"
#include "obnlowercumputerota.h"
#include "obnjobmonitorprograme.h"
#include "obnlogvisuailzationdisplay.h"
#include "obnrealtimewaveroot.h"
#include "obncalibrationdatadisplay.h"

class MyTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    MyTabWidget(QWidget *parent = 0);
    ~MyTabWidget();

    /// 设置工区信息
    void setProjectInfo(QString p_projectPath, QString p_projectName);

    void initTabBar();

    //检查index是否有效
    bool indexValid(int index) const;
    void takeNormalPage(QWidget *page);
    void popPage(QWidget *page);

    int  appendNormalPage(QWidget *page, QIcon pIcon);
    /// ====== 显示观测系统
    void setLMGRDisplay(const QString &, const QString&, const QString&);
    /// ====== 显示定位系统
    void setGPositiSystem();
    /// ====== 显示SEGY数据
    void setDisplaySEGY(QList<SegyFileHandle*>, int, int, OpenFilesType);
    /// ====== 显示LOG数据
    void setDisplayLogInform();
    /// ====== 显示时钟计算功能
    void setStdManagerDiffTime();
    /// ====== 显示节点控制功能
    void setRNMMainWindow();
    /// ====== 显示OTA功能
    void setOTAProgrameWindow();
    /// ====== 显示实时波形显示功能
    void setRealTimeWaveformDispProgrameWindow();
    /// ====== 标定数据显示
    void setCalibrationDataDisplayProgrameWindow();
    /// ====== 显示作业监控功能
    void setJobMonitorProgreamWindow();
protected:
    void showEvent(QShowEvent *event);

private:
    void slotTabCloseRequested(int index);

private:
    QString m_iconPath;
    QString m_projectPath, m_projectName;
    QList<QWidget*> fixedPage;
};

#endif // MYTABWIDGET_H
