#ifndef LMGRUNIT_H
#define LMGRUNIT_H

#define Menu_Name_File   "File"
#define Menu_Name_Edit   "Edit"
#define Menu_Name_View   "View"

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QButtonGroup>
#include <QGroupBox>

#include <QListWidget>
#include <QStandardItem>
#include <QStandardItemModel>

class QPushButton;

class QCheckBox;
class QProgressBar;
class CreateAreaDialog;
class PreferenceDlg;

#include "core.h"
#include "publicwidgets.h"
#include "lmgrpublic.h"

class LmgrUnit
{
public:
    LmgrUnit();
};

//站点总体信息显示控件
class StationsInfoWg : public QWidget
{
public:
    StationsInfoWg(QWidget *parent = 0);

    void setStationNum(const int &shots,const int recvs);

    void setRNInfoNum(const int &depolyed,const int &pickedUp);

    void clearData();

private:
    void initWg();

    QLabel *m_shotsLbl,*m_recvLbl,*m_deployedLbl,*m_pickedLbl;
};

/*菜单控制管理--------------------
 *File:
 *Edit
 *View
 *Help
 */
class LineManager;
class LMGRMenuManager : public QObject
{
public:
    LMGRMenuManager(QObject *parent = 0):QObject(parent),m_enable(true){}
    void createMenu(QMenuBar *menuBar,LineManager *parent);

    // 更新菜单,根据当期是否有显示区域更新状态
    void updateMenuStatus(const bool &enable);

    void setDeploySysConnected(const bool &connected);

private:
    QMenu *menuFile,*menuEdit,*menuView;
    bool   m_enable;
    QAction *dis_con_DpySysAct;
};

/*工具栏管理----------
 *
 *New Open Close | Delete | Update | ZoomIn ZoomOut ZoomIn Full Zoom Out Full | ItemList
 */
class LMGRToolManager : public QObject
{
public:
    LMGRToolManager(QObject *parent = 0):QObject(parent),m_enable(true){}
    void createToolBar(QToolBar *toolBar,LineManager *parent);

    //更新状态栏，根据是否有显示区域设置选项使能
    void updateToolBarStatus(const bool &enable);

private:
    QToolBar *m_toolBar;
    bool   m_enable;
};

//项目工区列表
class AreaListDlg : public QDialog
{
    Q_OBJECT
public:
    enum AreaOpt
    {
        Open_Area   = 1,    ///< 打开工区
        Delete_Area = 2     ///< 删除工区
    };
    AreaListDlg(QWidget *parent = 0);
    ~AreaListDlg();

    void setAreaOpt(const AreaOpt &opt);
    void setProjInfo(const ProjectInfo &projInfo){m_projInfo = projInfo;}

    /// ====== 更新列表
    void updateAreaList();

    /// ====== 显示工区列表
    void showAreaList();

signals:
    void signalOpenArea(const QString &areaName);
    void signalDeleteArea(const QString &areaName);

protected slots:
    void slotOk();

private:
    void initDlg();
    ProjectInfo          m_projInfo;
    AreaOpt              m_areaOpt;
    QListWidget         *m_listWidget;
};


class PreferenceDlg : public QDialog
{
    Q_OBJECT
public:
    PreferenceDlg(QWidget *parent = 0);
    QMap<int,QColor> colorMap()const{return m_colorMap;}

signals:
    void colorChanged(const int &id,const QColor &color);
    void colorMapChanged(const QMap<int,QColor> &colorMap);

private:
    void initDlg();

private slots:
    void slotOkBtn();
    void slotCancelBtn();

private:
    QButtonGroup    *m_btnGroup;
    ColorPickButton *m_bkColorBtn,*m_shotColorBtn,*m_firedShotColorBtn,*m_recvColorBtn\
    ,*m_shotLineColorBtn,*m_recvLineColorBtn,*m_legendColorBtn
    ,*m_deployedColorBtn,*m_pickedColorBtn,*m_downloadedColorBtn,*m_shotTextColorBtn
    ,*m_recvTextColorBtn;
    QMap<int,QColor> m_colorMap;
};

#endif // LMGRUNIT_H
