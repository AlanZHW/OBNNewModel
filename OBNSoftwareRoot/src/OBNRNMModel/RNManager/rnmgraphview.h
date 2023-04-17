#ifndef RNMGRAPHVIEW_H
#define RNMGRAPHVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDialog>
#include <QTableWidget>

#include "projectarea.h"
#include "rnitems.h"
#include "rnmpublic.h"
#include "rnftpmanager.h"


class QTimer;
class StatusControler;
class NodeInfoDlg;
class QTextBrowser;
class QTableWidget;
class RNMGraphView : public QGraphicsView
{
    Q_OBJECT
public:
    RNMGraphView(QWidget *parent = 0);
    ~RNMGraphView();

    void setNodes(const QVector<Node*> &nodes);
    void setStatisticsData(StatisticsData *data);
    //启动和停止刷新
    void startOrStopUpdateNode(const bool &start);
    //设置刷新间隔
    void setUpdateInterval(const int &interval);
    //正在刷新
    bool isUpdating() const;
    //View
    void setShowAllOrConnected(const bool &show);
    void searchNode(const uint &node);
    int  nodeBoxes() const{return m_groupBoxItem.size();}

    /// ======原子钟相关
    void startAtomicClockTameFunction();
    void endAtomicClockTameFunction();
    void setDFunction(const int&);
    void getDFunction();
    /// ====== 标定
    void calibrationFunction(const bool);
    /// ====== 开启和关闭保存设备信息定时器
    void startOrstopSaveDeviceInformTimer(bool);
signals:
    void updateNodes();
protected:
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
private slots:
    void slotRefresh();
private:
    //初始化节点布局
    void initNodeDisplay(const QVector<Node*> &nodes);
    //更新显示
    void updateNodeDisplay();
private:
    QVector<Node*>           m_Nodes;
    QGraphicsScene          *m_scene;
    QVector<GroupBoxItem *>  m_groupBoxItem;//组项
    QVector<NodeItem *>      m_nodeItems;   //节点项
    bool                     m_showAllConnected;    ///< 是否显示链接状态
    //刷新时间定时器
    QTimer                  *m_timer;
    int                      m_updateInterval;//刷新间隔
    StatisticsData          *m_statisticsData;
    NodeInfoDlg             *m_NodeInfoDlg;
    ProjectInfo             m_projectInform;
};


class NodeInfoDlg : public QDialog
{
    Q_OBJECT
public:
    NodeInfoDlg(QWidget *parent = 0);
    void showNodeInfo(const Node *node);
private:
    void          initDlg();
    QTableWidget* m_tableWidget;
};


#endif // RNMGRAPHVIEW_H
