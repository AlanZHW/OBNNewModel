#ifndef RNMANAGER_H
#define RNMANAGER_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QTranslator>

#include "rnmgrunit.h"
#include "rnmsidebar.h"
#include "rnmgraphview.h"
#include "statusreport.h"
#include "appglobal.h"
#include "rnmanager_global.h"
namespace Ui {
class RNManager;
}
//警告信息
extern QTextBrowser    *txtBrwser;
extern bool             warning_enable;

class RNMANAGER_EXPORT RNManager : public QMainWindow
{
    Q_OBJECT
public:
    explicit RNManager(QWidget *parent = 0);
    ~RNManager();
    bool init();
    void setProjectInform(const QString&, const QString&);
    //打印警告信息,提示设备参数
    void outputMessage(QtMsgType type,const QMessageLogContext &/*context*/,const QString &msg);
    QTextBrowser *textBrowser(){return m_txtBrowser;}

private slots:
    //菜单file选项
    void slotSetSearchIpScope();
    void slotQuit();

    //set选项
    void slotLimits();
    void slotSetUpdateInterval(const int &interval);//设置更新时间
    void slotStartStopUpdate(const bool &start);

    //Ftp 文件管理
    void slotNodeFtpManager();

    //view选项
    void slotShowAllOrConnected(const bool &show);//显示全部或者只显示当前连接的节点
    //about选项
    void slotAbout();
    void slotPrintWarningEnable(const bool &enable);

    void slotShowStatusReport();
    void slotDisplayFilters(const int &);

    /// ====== 原子钟相关
    void slotAtomicClockTame(); ///<开始原子钟驯服
    void slotSetD();            ///<设置D
    void slotGetD();            ///<获取D
    /// ====== 标定
    void slotStartCalibrationFunction();
    void slotEndCalibrationFunction();
private:
    void initWindow();

private:
    Ui::RNManager *ui;
    QTranslator m_translator;

    ProjectInfo   m_projInfo;
    RNMMenuManager   *m_menuManager;//菜单管理
    RNMToolManager   *m_toolManager;//工具栏管理
    RNMSideBar      *m_sideBar;//侧边栏
    RNMGraphView    *m_RNView;
    QTextBrowser    *m_txtBrowser;
    StatusReportDlg *m_statusReport;
    //---------------------------
    SearchIpDialog  *m_searIPDlg;
    LimitsDialog    *m_limitsDlg;
    //Ftp Manager
    RNFtpManager    *m_FtpManager;
    NodeMediator    *m_nodeMediator;
    bool             m_updating;
    QVector<Node *>  m_Nodes;
    QVector<LimitData>   m_limitData;
    //statistics 信息
    StatisticsData       m_statisticsData;
    StatusControler     *m_stCtrler;      //状态控制
};

//打印警告信息,提示设备参数
extern "C" void outputMessage(QtMsgType type,const QMessageLogContext &/*context*/,const QString &msg);

#endif // RNMANAGER_H
