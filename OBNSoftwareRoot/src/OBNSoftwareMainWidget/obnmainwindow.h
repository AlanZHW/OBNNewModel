#ifndef OBNMAINWINDOW_H
#define OBNMAINWINDOW_H

#include <QDir>
#include <QIcon>
#include <QMenu>
#include <QLabel>
#include <QDebug>
#include <QProcess>
#include <QToolBar>
#include <QPainter>
#include <QSettings>
#include <QTreeView>
#include <QTextEdit>
#include <QIODevice>
#include <QTextCodec>
#include <QToolButton>
#include <QPushButton>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTranslator>
#include <QStandardItemModel>
#include <QGraphicsDropShadowEffect>

#include "mytabwidget.h"
#include "../OBNOtherLibraries/Core/projectarea.h"
#include "publicHostInform.h"

#include "createareadialog.h"
#include "updateareadialog.h"
#include "abstractareadialog.h"
#include "opensegydlg.h"
#include "exportsegydlg.h"
#include "obnlmgrarealistwidget.h"
#include "appglobal.h"

#include "obnmainwindow_global.h"

#define STRING_SETTINGS_ORG "swigd"
#define STRING_SETTINGS_APP "SWIGD"

#define STRING_MENU_OPTION_ACTION_STYLE "Style Sheet"

/// 工区
#define ROLE_MARK_FOLDER_PRI Qt::UserRole+1     /// root
#define DATA_MARK_FOLDER_SEC Qt::UserRole+2     /// 数据标志

#define MARK_ITEM_ROOT 1 /// root
#define MARK_ITEM_PRI  2 /// 数据一级目录
#define MARK_ITEM_SEC  3 /// 数据二级目录

#define ROLE_MARK_DATA_NAME 1

inline void swigd_setStyle(const QString& strStyle)
{
    QSettings objSettings(STRING_SETTINGS_ORG, STRING_SETTINGS_APP);
    objSettings.setValue(STRING_MENU_OPTION_ACTION_STYLE, strStyle);
}

inline QString swigd_getStyle()
{
    QString strStyleSheet = STRING_MENU_OPTION_ACTION_STYLE;
    QSettings objSettiongs(STRING_SETTINGS_ORG, STRING_SETTINGS_APP);
    if(!objSettiongs.contains(STRING_MENU_OPTION_ACTION_STYLE))
    {
        objSettiongs.setValue(STRING_MENU_OPTION_ACTION_STYLE, strStyleSheet);
    }
    else
    {
        strStyleSheet = objSettiongs.value(STRING_MENU_OPTION_ACTION_STYLE).toString();
    }
    return strStyleSheet;
}

inline QString swigd_getStyleFile()
{
    QDir bin_dir(QCoreApplication::applicationDirPath());
    bin_dir.cdUp();
    QString n_ConfigPath = bin_dir.absolutePath();
    n_ConfigPath += "/.config/";
    QString n_StyleFile = n_ConfigPath + swigd_getStyle();
    return n_StyleFile;
}

inline void swigd_updateStyle()
{
    QString fileName = swigd_getStyleFile();
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QString styleSheet = file.readAll();
        file.close();
        qApp->setStyleSheet(styleSheet);
    }
}

namespace Ui {
class OBNMainWindow;
}

class OBNMAINWINDOW_EXPORT OBNMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit OBNMainWindow(QWidget *parent = 0);
    ~OBNMainWindow();
    void setToolButtonStyleSheet(QToolButton* pToolButton);
    void setToolButtonIconInfo(QToolButton* pToolButton);

    void initDataListInfoFunction();
    void showDataInfoListFunction();/// 显示数据列表信息

    void setCurrentProjectInfrom(const QString&, const QString&);
public slots:
    void slotRefreshDataList();

private slots:
    /// ======
    void slotNewArea(bool);         ///< 新建观测系统
    void slotOpenArea(bool);        ///< 打开观测系统
    void slotUpdateArea(bool);      ///< 修改观测系统
    void slotDeleteArea(bool);      ///< 删除观测系统
    /// ======
    void slotRNMFunction(bool);     ///< 节点管理
    void slotCalibration(bool);     ///< 标定
    void slotRealTimWaveform(bool); ///< 实时波形显示
    void slotOTA(bool);             ///< 软件升级
    void slotPositionSystem(bool);  ///< 定位系统
    /// ======
    void slotOpenSEGY(bool);        ///< 显示SEG-Y

    void slotExportSEGY(bool);      ///< 导出SEG-Y
    void slotHTimeAnilysis(bool);   ///< 水深信号分析
    void slotLogDisplay(bool);      ///< Log信息显示
    /// ======
    void slotJobAnalysis(bool);     ///< 作业分析

    void slotOpenHelpPrograme(bool);///< 帮助文档
    void slotRefushSidebarList();   ///< 刷新侧边栏
    void slotClickedDataList(const QModelIndex& index);
    void slotCustomContextDataMenuFunc(QPoint point);
    ///
    void slotRefreshTableStart(QString, QString);
    void slotRefreshTableEnd(QString, QString);

private:
    void initWindow();
    void displayDataList();
protected:
    void paintEvent(QPaintEvent*);

private:
    QLabel* m_labelStatubar;
    QString m_iconPath, m_binPath;

    CreateAreaDialog* m_createArea; ///<
    UpdateAreaDialog* m_updateArea; ///<
    OpenSegyDlg*    m_openSEGYDialog;
    ExportSegyDlg*  m_exportSEGYDialog;
    OBNLMGRAreaListWidget* m_openLmgrListWdget;

    QStandardItemModel* m_dataItems;
    QStandardItem*      m_itemRoot;
    QStandardItem*      m_itemArea; ///<SPS文件

    QStringList m_projList;
    ProjectInfo m_projectInform;
    QString m_currProjectName, m_currProjectPath;

    QToolBar* m_ToolBar;
    QString m_projectName, m_projectPath;
    QProcess *n_processLoadData, *m_processDisplay, *n_processBaseMap;
    QString m_currDataName;

    QTranslator *m_translator;

    Ui::OBNMainWindow *ui;
};

#endif // OBNMAINWINDOW_H
