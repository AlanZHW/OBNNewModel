#include "rnmgraphview.h"

#define  GroupBox_Item_VSpace   20
#define  GroupBox_Item_HSpace   10

#define  Default_Refresh_Interval       10000

#include <QTimer>
#include <QMouseEvent>
#include <QDialog>
#include <QTableWidget>
#include <QMessageBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <QHeaderView>

RNMGraphView::RNMGraphView(QWidget *parent)
    :QGraphicsView(parent)
    ,m_showAllConnected(false)
    ,m_timer(new QTimer(this))
{
    m_scene = new QGraphicsScene(this);
    this->setScene(m_scene);


    this->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    m_updateInterval = Default_Refresh_Interval;
    m_timer->setInterval(Default_Refresh_Interval);
    m_NodeInfoDlg = new NodeInfoDlg(this);

    //connect(m_timer,SIGNAL(timeout()),this,SLOT(slotRefresh()));
}

RNMGraphView::~RNMGraphView()
{
    //正在刷新，停止
    if(m_timer->isActive()){
        startOrStopUpdateNode(false);
    }
}

//void RNMGraphView::mouseMoveEvent(QMouseEvent *e)
//{
//    qDebug()<<"mouse move";
//    QGraphicsView::mouseMoveEvent(e);
//}

void RNMGraphView::setNodes(const QVector<Node*> &nodes)
{
    m_Nodes = nodes;

    //初始化布局显示
    initNodeDisplay(nodes);
}

void RNMGraphView::setStatisticsData(StatisticsData *data)
{
    m_statisticsData = data;
}

/// ===== 启动定时器,按照规定时间刷新当前节点的链接状态与参数
void RNMGraphView::startOrStopUpdateNode(const bool &start)
{
    //启动
    if(start)
    {
        foreach (Node *node, m_Nodes)
        {
            node->startRefresh(m_updateInterval);
        }
        m_timer->start();
    }
    //停止
    else
    {
        m_timer->stop();
        foreach (Node *node, m_Nodes)
        {
            node->stopRefresh();
        }
    }
}

void RNMGraphView::setUpdateInterval(const int &interval)
{
    m_updateInterval = interval;
    m_timer->setInterval(m_updateInterval);
}

bool RNMGraphView::isUpdating() const
{
    return m_timer->isActive();
}

//
void RNMGraphView::setShowAllOrConnected(const bool &show)
{
    m_showAllConnected = show;

    /// ====== 先停止刷新
    bool is_updating = isUpdating();
    if(is_updating)
    {
        startOrStopUpdateNode(false);
    }
    initNodeDisplay(m_Nodes);
    //启动刷新
    if(is_updating)
    {
        startOrStopUpdateNode(true);
    }
}

void RNMGraphView::searchNode(const uint &node_no)
{
    foreach(NodeItem *item, m_nodeItems) {
        if(item->node()->no() == node_no){
            item->setSelected(true);
            this->ensureVisible(item);
            return;
        }
    }
    QMessageBox::information(this, tr("提示"), tr("未找到节点")+QString("G%1.").arg(node_no,3,10,QChar('0'))); ///< Not Found Node
}

void RNMGraphView::mouseDoubleClickEvent(QMouseEvent *e)
{
    QGraphicsItem *item = m_scene->itemAt(mapToScene(e->pos()),this->transform());
    if(item)
    {
        NodeItem *nodeItem = dynamic_cast<NodeItem *>(item);
        if(nodeItem)
        {
            m_NodeInfoDlg->showNodeInfo(nodeItem->node());
        }
    }
    QGraphicsView::mouseDoubleClickEvent(e);
}

void RNMGraphView::mousePressEvent(QMouseEvent *e)
{
    QGraphicsView::mousePressEvent(e);
}

/// ====== 刷新节点信息
void RNMGraphView::slotRefresh()
{
    foreach(Node *node, m_Nodes)
        node->refreshState();
    emit updateNodes();
}

/// ======原子钟相关
void RNMGraphView::startAtomicClockTameFunction()   ///< 开始驯服原子钟
{
    foreach(Node *node, m_Nodes)
        node->nodeStartAtomicClockTameFunction();
}
void RNMGraphView::endAtomicClockTameFunction()     ///< 停止驯服原子钟
{
    foreach(Node *node, m_Nodes)
        node->nodeEndAtomicClockTameFunction();
}
void RNMGraphView::setDFunction()                   ///< 设置D
{
    foreach(Node *node, m_Nodes)
        node->nodeSetDFunction();
}
void RNMGraphView::getDFunction()                   ///< 获取D
{
    foreach(Node *node, m_Nodes)
        node->nodeGetDFunction();
}
/// ======标定
void RNMGraphView::calibrationFunction(const bool _isCalibration)
{
    foreach(Node *node, m_Nodes)
    {
        node->nodeCalibrationFunction(_isCalibration);
    }
}

/// ===========================================================

void RNMGraphView::initNodeDisplay(const QVector<Node*> &nodes)
{
    //按照每行15 台设备固定显示---
    m_scene->clear();

    m_nodeItems.clear();
    m_groupBoxItem.clear();

    //计算行数(组)
    int node_num     = nodes.size();
    int max_rowCount = node_num/Group_Node_Num;
    max_rowCount     = (node_num%Group_Node_Num==0)?max_rowCount:(max_rowCount+1);

    m_groupBoxItem.resize(max_rowCount);
    m_nodeItems.resize(node_num);

    QSize groupSize =  GroupBoxItem::size();
    int row = 0;
    int base_y = 0;
    int index  = 0;
    GroupBoxItem  *boxItem = 0;
    int avalibleNum = 0;
    for(int i = 0 ;i<nodes.size();i++)
    {
        //15个一组----------------------
        if(!boxItem || boxItem->childs() == 15)
        {
            base_y += GroupBox_Item_VSpace;

            //添加组--------------------
            boxItem = new GroupBoxItem;
            m_groupBoxItem[row] = boxItem;
            boxItem->setPos(GroupBox_Item_HSpace,base_y);
            boxItem->setGroupId(row+1);
            m_scene->addItem(boxItem);
            row ++;
            base_y += groupSize.height();
        }

        qDebug() << "m_showAllConnected = " << m_showAllConnected << "\t state = " << nodes[i]->state();
        if(m_showAllConnected || nodes[i]->state())
        {
            if(nodes[i]->state())
            {
                avalibleNum ++;
            }
            //添加和保存节点
            NodeItem *nodeItem = boxItem->addNodeItem(nodes[i]);
            nodes[i]->setId(i);
            nodes[i]->setItem(nodeItem);
            m_nodeItems[index] = nodeItem;
            index ++;
        }
        else
        {
            nodes[i]->setItem(0);//不显示需要将对应的项指针置为0,不再更新显示状态
        }
    }

    m_groupBoxItem.resize(row);
    m_nodeItems.resize(index);

    //统计数据
    m_statisticsData->totalNodes     = node_num;
    m_statisticsData->avaliableNodes = avalibleNum;
    m_statisticsData->nodeBoxes      = row;

    m_scene->setSceneRect(0,0,groupSize.width()+10*2,(groupSize.height())*row+(row+1)*20);
}

void RNMGraphView::updateNodeDisplay()
{
    m_nodeItems.clear();
    m_groupBoxItem.clear();
    //...
}

/// ====== 显示当前节点信息
NodeInfoDlg::NodeInfoDlg(QWidget *parent)
    :QDialog(parent)
{
    this->setWindowTitle(tr("节点信息")); ///< Node Information
    this->setMinimumSize(500, 400);
    initDlg();
}

void NodeInfoDlg::initDlg()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_tableWidget = new QTableWidget;
    mainLayout->addWidget(m_tableWidget);

    QPushButton* saveButton  = new QPushButton(tr("&保存"),this);
    connect(saveButton, &QPushButton::clicked, this, &NodeInfoDlg::slotSaveInformFunction);
    QPushButton* closeButton    = new QPushButton(tr("&关闭"),this);
    connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(saveButton);
    hLayout->addStretch(1);
    hLayout->addWidget(closeButton);
    mainLayout->addLayout(hLayout);

    this->setLayout(mainLayout);
}

void NodeInfoDlg::showNodeInfo(const Node *node)
{
    m_tableWidget->clear();

    m_tableWidget->setRowCount(9);
    m_tableWidget->setColumnCount(2);
    QStringList nTableHeaderList;
    nTableHeaderList << tr("设备信息") << tr("状态");
    m_tableWidget->setHorizontalHeaderLabels(nTableHeaderList);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->verticalHeader()->hide();

    m_tableWidget->setItem(0, 0, new QTableWidgetItem(tr("设备编号")));
    m_tableWidget->setItem(0, 1, new QTableWidgetItem(QString("G%1").arg(node->no(),3,10,QChar('0'))));

    m_tableWidget->setItem(1, 0, new QTableWidgetItem(tr("连接状态")));
    QString stateStr = node->state()?"true":"false";
    m_tableWidget->setItem(1, 1, new QTableWidgetItem(stateStr));

    m_tableWidget->setItem(2, 0, new QTableWidgetItem(tr("电压(V)")));
    m_tableWidget->setItem(2, 1, new QTableWidgetItem(QString("%1").arg(node->voltage())));

    m_tableWidget->setItem(3, 0, new QTableWidgetItem(QStringLiteral("仓温(℃)")));
    m_tableWidget->setItem(3, 1, new QTableWidgetItem(QString("%1").arg(node->temperature())));

    m_tableWidget->setItem(4, 0, new QTableWidgetItem(tr("仓压(atm)")));
    m_tableWidget->setItem(4, 1, new QTableWidgetItem(QString("%1").arg(node->pressure(),0,'g',3)));

    m_tableWidget->setItem(5, 0, new QTableWidgetItem(QStringLiteral("俯仰角(℃)")));
    m_tableWidget->setItem(5, 1, new QTableWidgetItem(QString("%1").arg(node->isPitchAngle())));

    m_tableWidget->setItem(6, 0, new QTableWidgetItem(tr("翻滚角(℃)")));
    m_tableWidget->setItem(6, 1, new QTableWidgetItem(QString("%1").arg(node->isRollAngle())));

    m_tableWidget->setItem(7, 0, new QTableWidgetItem(tr("方位角(℃)")));
    m_tableWidget->setItem(7, 1, new QTableWidgetItem(QString("%1").arg(node->isAzimuthAngle())));

    m_tableWidget->setItem(8, 0, new QTableWidgetItem(tr("存储容量(GB)")));
    m_tableWidget->setItem(8, 1, new QTableWidgetItem(QString("%1").arg(node->memory())));
    /// ====== 显示
    this->show();
}

void NodeInfoDlg::slotSaveInformFunction(bool)
{

}

















