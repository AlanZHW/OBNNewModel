#include "obnsearchhosts.h"
#include "ui_obnsearchhosts.h"

/// 每个网段的100-200为节点的IP地址
extern bool isNodeIP(const uint &ipV4)
{
    uint val  = ipV4 - startIp;
    uint temp = val%256;
    return temp; /// (100 <= temp && temp<200); ///< 20220919 ZHW UPDATE
}

extern uint ip2DeviceNo(const uint &ipV4)
{
    uint temp = ipV4 - startIp;
//    uint nCurentNO = (temp/256)*100 + ((temp%256)-100);   ///< 从100开始
    uint nCurentNO = (temp/256)*2 + ((temp%256)-2);         ///< 从2开始
    return nCurentNO;
}


OBNSearchHosts::OBNSearchHosts(QWidget *parent) :
    QDialog(parent), m_linkHostsNum(0),
    ui(new Ui::OBNSearchHosts)
{
    ui->setupUi(this);

    setWindowTitle(tr("筛选有效节点"));

    /// ======
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &OBNSearchHosts::close);
    connect(ui->pushButtonSearch, &QPushButton::clicked, this, &OBNSearchHosts::slotSearchButtonClicked);
    connect(ui->pushButtonOK,     &QPushButton::clicked, this, &OBNSearchHosts::slotOKButtonClicked);
    connect(ui->pushButtonReset,  &QPushButton::clicked, this, &OBNSearchHosts::slotResetButtonClicked);

    /// ======
    ui->pushButtonOK->setEnabled(false);

    /// ======
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnWidth(0, this->width()/3);
    ui->tableWidget->setColumnWidth(1, this->width()/3);
    ui->tableWidget->setColumnWidth(2, this->width()/3);

    /// ======
    ui->progressBar->setValue(0);

    /// ======
    ui->lineEditIpStart->setText("192.168.137.100");
    ui->lineEditIpEnd->setText("192.168.137.105");

    n_searchHostsThread = new OBNSearchHostsThread;
    connect(n_searchHostsThread, &OBNSearchHostsThread::signalSearchHostsLinkStatus, this, &OBNSearchHosts::slotRecvSearchHostsInform);
}

OBNSearchHosts::~OBNSearchHosts()
{
    delete ui;
}

/// ======
void OBNSearchHosts::slotSearchButtonClicked()
{
    m_linkHostsNum = 0;
    m_hostsStateLVector.clear();

    /// ====== 调用线程，将IP范围发送到线程，筛选能够ping通的IP
    QString fromIP = ui->lineEditIpStart->text();
    QString toIP   = ui->lineEditIpEnd->text();

    qDebug() << "fromIP = " << ui->lineEditIpStart->text();
    qDebug() << "toIP = "   << ui->lineEditIpEnd->text();

    if(fromIP.isEmpty() || toIP.isEmpty())
    {
        QMessageBox::warning(this, tr("错误"), tr("IP范围不正确,请检查。"));
        return;
    }

    QHostAddress addr1(fromIP);
    QHostAddress addr2(toIP);

    /// ===== 满足 起始 < 结束
    if(addr1.toIPv4Address() > addr2.toIPv4Address())
    {
        QMessageBox::warning(this,"错误","IP范围不正确,请检查。");
        return;
    }

    quint32 m_startIP =  addr1.toIPv4Address();
    quint32 m_lastIP  =  addr2.toIPv4Address();


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
        ui->tableWidget->setItem(iRow, 1, new QTableWidgetItem(QString("G%1").arg(ip2DeviceNo(n_rstInform[iRow]), 3, 10, QChar('0'))));
    }
    ui->labelNodeTotalDisp->setText(QString::number(nTableWidgetRowNum));

    if(0 != nTableWidgetRowNum)
    {
        ui->pushButtonOK->setEnabled(true);
    }

    OBNSearchHostsThread* n_searchHostsThread = new OBNSearchHostsThread;
    n_searchHostsThread->setValues(n_rstInform);
    connect(n_searchHostsThread, &OBNSearchHostsThread::signalSearchHostsLinkStatus, this, &OBNSearchHosts::slotRecvSearchHostsInform);
    n_searchHostsThread->start();
}

/// ====== 接收当前可用的IP
void OBNSearchHosts::slotRecvSearchHostsInform(const QString& ip, const int& pNumprocess, bool state)
{
    /// ======
    ui->progressBar->setValue(pNumprocess);

    /// ======
    for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
    {
        if(0 == ui->tableWidget->item(iRow, 0)->text().compare(ip))
        {
            if(state)
            {
                m_linkHostsNum += 1;
                ui->tableWidget->setItem(iRow, 2, new QTableWidgetItem(tr("链接")));
            }
            else
            {
                ui->tableWidget->setItem(iRow, 2, new QTableWidgetItem(tr("断开")));
            }
            break;
        }
    }
    ui->labelNodeIsConnectedDisp->setText(QString::number(m_linkHostsNum));
}


void OBNSearchHosts::findNodesFromScope(const quint32 &start,const quint32 &last, QVector<uint>& pRst)
{
    pRst.resize(last-start +1);
    int num = 0;
    for(uint i = start; i <= last; i ++)
    {
        if(isNodeIP(i))
        {
            pRst[num] = i;
            num ++;
        }
    }
    pRst.resize(num);
}

/// ======清除表格内容
void OBNSearchHosts::slotResetButtonClicked()
{
    for(int row = ui->tableWidget->rowCount()-1; row >= 0; row --)
    {
        ui->tableWidget->removeRow(row);
    }
}

/// ======
void OBNSearchHosts::slotOKButtonClicked()
{
    m_hostsStateLVector.clear();
    for(int iRow = 0; iRow < ui->tableWidget->rowCount(); iRow ++)
    {
        HostsState pHostsState;
        pHostsState.ip      = ui->tableWidget->item(iRow, 0)->text();
        pHostsState.hostNum = ui->tableWidget->item(iRow, 1)->text();
        pHostsState.state   = ui->tableWidget->item(iRow, 2)->text() == "断开" ? false : true;
        if(pHostsState.state)
            m_hostsStateLVector.append(pHostsState);
    }
    emit signalCurrentHostsSend(m_hostsStateLVector);
    /// ======
    this->close();
}





















