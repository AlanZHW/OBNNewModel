#ifndef OBNSEARCHHOSTS_H
#define OBNSEARCHHOSTS_H

/// ====== 筛选当前可以被链接上的节点

#include <QDialog>
#include <QMessageBox>
#include <QHostAddress>

#include "obnsearchhoststhread.h"
#include "LowerComputerControlPublic.h"

//起始地址
static const uint startIp = QHostAddress("192.168.137.0").toIPv4Address();

namespace Ui {
class OBNSearchHosts;
}

class OBNSearchHosts : public QDialog
{
    Q_OBJECT
public:
    explicit OBNSearchHosts(QWidget *parent = nullptr);
    ~OBNSearchHosts();

    void findNodesFromScope(const quint32 &start,const quint32 &last, QVector<uint>& pRst);

public slots:
    void slotSearchButtonClicked();
    void slotOKButtonClicked();
    void slotResetButtonClicked();

    /// ====== 接收当前筛选进度
    void slotRecvSearchHostsInform(const QString&, const int&, bool);

signals:
    void signalCurrentHostsSend(QVector<HostsState>);

private:
    int           m_linkHostsNum;
    QVector<uint> n_rstInform;
    OBNSearchHostsThread* n_searchHostsThread;

    QVector<HostsState> m_hostsStateLVector;

    Ui::OBNSearchHosts *ui;
};

#endif // OBNSEARCHHOSTS_H
