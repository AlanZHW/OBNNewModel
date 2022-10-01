#ifndef OBNLISTNODEINFORM_H
#define OBNLISTNODEINFORM_H

#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QCheckBox>

#include "LowerComputerControlPublic.h"

namespace Ui {
class OBNListNodeInform;
}

class OBNListNodeInform : public QWidget
{
    Q_OBJECT

public:
    explicit OBNListNodeInform(QWidget *parent = nullptr);
    ~OBNListNodeInform();

    void setHostInforms(const QVector<HostsState>& pHostInforms);
    void selectAllFunction(bool);

signals:
    void signalOptionalHosts(const QVector<HostsState>&);

public slots:
    void slotCheckBoxStateChange(const int&);

private:
    QVector<HostsState> mInformHosts;

    Ui::OBNListNodeInform *ui;
};

#endif // OBNLISTNODEINFORM_H
