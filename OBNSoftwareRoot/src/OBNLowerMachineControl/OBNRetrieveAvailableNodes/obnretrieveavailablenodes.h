#ifndef OBNRETRIEVEAVAILABLENODES_H
#define OBNRETRIEVEAVAILABLENODES_H

#include <QDialog>
#include <QMessageBox>
#include <QHostAddress>

#include "publicHostInform.h"
#include "obnsearchhoststhread.h"

//起始地址
static const uint startIp = QHostAddress("192.168.137.0").toIPv4Address();

QT_BEGIN_NAMESPACE
namespace Ui { class ONBRetrieveAvailableNodes; }
QT_END_NAMESPACE

class ONBRetrieveAvailableNodes : public QDialog
{
    Q_OBJECT

public:
    ONBRetrieveAvailableNodes(QWidget *parent = nullptr);
    ~ONBRetrieveAvailableNodes();

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
    QVector<HostsState>   m_hostsStateLVector;

    Ui::ONBRetrieveAvailableNodes *ui;
};
#endif // OBNRETRIEVEAVAILABLENODES_H