#include "obnretrieveavailablenodes.h"
#include "ui_obnretrieveavailablenodes.h"

/// 每个网段的100-200为节点的IP地址
extern bool isNodeIP(const uint &ipV4, const uint & _startIp)
{
    uint val  = ipV4 - _startIp;
    uint temp = val%256;
    return temp; /// (100 <= temp && temp<200); ///< 20220919 ZHW UPDATE
}

extern uint ip2DeviceNo(const uint &ipV4, const uint & _startIp)
{
    uint temp = ipV4 - _startIp;
//    uint nCurentNO = (temp/256)*100 + ((temp%256)-100);   ///< 从100开始
    uint nCurentNO = (temp/256)*2+(temp%256);///< 从0开始
    return nCurentNO;
}

ONBRetrieveAvailableNodes::ONBRetrieveAvailableNodes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ONBRetrieveAvailableNodes)
{
    ui->setupUi(this);
    setWindowTitle(tr("筛选有效节点"));

    /// ====== 退出按钮
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &ONBRetrieveAvailableNodes::close);
    /// ====== 搜索按钮
    connect(ui->pushButtonSearch, &QPushButton::clicked, this, &ONBRetrieveAvailableNodes::slotSearchButtonClicked);
    /// ====== 确定按钮
    connect(ui->pushButtonOK,     &QPushButton::clicked, this, &ONBRetrieveAvailableNodes::slotOKButtonClicked);
    /// ====== 重置按钮
    connect(ui->pushButtonReset,  &QPushButton::clicked, this, [=](){
        /// ====== 清除表格内容
        for(int row = ui->tableWidget->rowCount()-1; row >= 0; row --)
        {
            ui->tableWidget->removeRow(row);
        }
        /// ====== 重置IP输入框
        ui->lineEditIpStart->setText("192.168.137.100");
        ui->lineEditIpEnd->setText("192.168.137.105");
        /// ====== 重置进度条
        ui->progressBar->setValue(0);
        /// ====== 设置重置按钮不可点击
        ui->pushButtonReset->setEnabled(false);
    });

    /// ====== 设置OK按钮初始不可点击
    ui->pushButtonOK->setEnabled(false);
    ui->pushButtonReset->setEnabled(false);
    /// ====== 设置表格属性
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnWidth(0, this->width()/3);
    ui->tableWidget->setColumnWidth(1, this->width()/3);
    ui->tableWidget->setColumnWidth(2, this->width()/3);
    /// ====== 设置进度条初始值为0
    ui->progressBar->setValue(0);
    /// ====== 设置初始IP信息
    ui->lineEditIpStart->setText("192.168.137.100");
    ui->lineEditIpEnd->setText("192.168.137.105");
}

ONBRetrieveAvailableNodes::~ONBRetrieveAvailableNodes()
{
    delete ui;
}

/// ======
void ONBRetrieveAvailableNodes::slotSearchButtonClicked()
{
    m_linkHostsNum = 0;
    m_hostsStateLVector.clear();

    /// ====== 调用线程，将IP范围发送到线程，筛选能够ping通的IP
    QString fromIP = ui->lineEditIpStart->text();
    QString toIP   = ui->lineEditIpEnd->text();
    if(fromIP.isEmpty() || toIP.isEmpty())
    {
        QMessageBox::warning(this, tr("错误"), tr("IP范围不正确,请检查。"), tr("确定"));
        return;
    }

    QStringList nfromIPList = fromIP.split(".");
    QString firstIP;
    for(int iList = 0; iList < nfromIPList.count()-1; iList ++)
    {
        firstIP = firstIP + nfromIPList[iList] + ".";
    }
    firstIP = firstIP + "0";
    qDebug() << "fromIP = " << fromIP << "\t toIP = " << toIP << "\t firstIP = " << firstIP;


    QHostAddress addr1(fromIP);
    QHostAddress addr2(toIP);
    QHostAddress addrFirst(firstIP);

    /// ===== 满足 起始 < 结束
    if(addr1.toIPv4Address() > addr2.toIPv4Address())
    {
        QMessageBox::warning(this, tr("错误"), tr("IP范围不正确,请检查."), tr("确定"));
        return;
    }

    quint32 m_startIP =  addr1.toIPv4Address();
    quint32 m_lastIP  =  addr2.toIPv4Address();
    m_startIp = addrFirst.toIPv4Address();

    n_rstInform.clear();
    findNodesFromScope(m_startIP, m_lastIP, n_rstInform);

    if(0 == n_rstInform.count())
    {
        return;
    }
    /// ====== 设置表格内容
    int nTableWidgetRowNum = n_rstInform.count();
    ui->tableWidget->setRowCount(nTableWidgetRowNum);
    for(int iRow = 0; iRow < nTableWidgetRowNum; iRow ++)
    {
        ui->tableWidget->setItem(iRow, 0, new QTableWidgetItem(QHostAddress(n_rstInform[iRow]).toString()));
        ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(QString("G%1").arg(ip2DeviceNo(n_rstInform[iRow], m_startIp), 3, 10, QChar('0'))));
    }
    ui->labelNodeTotalDisp->setText(QString::number(nTableWidgetRowNum));

    if(0 != nTableWidgetRowNum)
    {
        ui->pushButtonOK->setEnabled(true);
        ui->pushButtonReset->setEnabled(true);
    }

    ui->progressBar->setRange(0, n_rstInform.count());
    /// ====== 搜索可用节点
    for(int iList = 0; iList < n_rstInform.count(); iList ++)
    {
        OBNSearchHostsThread* n_searchHostsThread = new OBNSearchHostsThread;
        connect(n_searchHostsThread, &OBNSearchHostsThread::signalSearchHostsLinkStatus, this, &ONBRetrieveAvailableNodes::slotRecvSearchHostsInform);
        n_searchHostsThread->setValue(n_rstInform[iList], iList);
        n_searchHostsThread->start();

    }
}

/// ====== 接收当前可用的IP
void ONBRetrieveAvailableNodes::slotRecvSearchHostsInform(const int& _row, bool state)
{
    if(state)
    {
        m_linkHostsNum += 1;
        ui->tableWidget->setItem(_row, 2, new QTableWidgetItem(tr("链接")));
    }
    else
    {
        ui->tableWidget->setItem(_row, 2, new QTableWidgetItem(tr("断开")));
    }
    n_rstConectNum += 1;
    ui->progressBar->setValue(n_rstConectNum);
    if(n_rstConectNum == ui->tableWidget->rowCount())
    {
        ui->labelNodeIsConnectedDisp->setText(QString::number(m_linkHostsNum));
    }
}


void ONBRetrieveAvailableNodes::findNodesFromScope(const quint32 &start,const quint32 &last, QVector<uint>& pRst)
{
    pRst.resize(last-start +1);
    int num = 0;
    for(uint i = start; i <= last; i ++)
    {
        if(isNodeIP(i, m_startIp))
        {
            pRst[num] = i;
            num ++;
        }
    }
    pRst.resize(num);
}

/// ======
void ONBRetrieveAvailableNodes::slotOKButtonClicked()
{
    m_hostsStateLVector.clear();
    for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
    {
        HostsState pHostsState;
        pHostsState.ip      = ui->tableWidget->item(iRow, 0)->text();
        pHostsState.hostNum = ui->tableWidget->item(iRow, 1)->text();
        pHostsState.state   = ui->tableWidget->item(iRow, 2)->text() == "断开" ? false : true;
        m_hostsStateLVector.append(pHostsState);
    }
    emit signalCurrentHostsSend(m_hostsStateLVector);
    /// ======
    this->close();
}


