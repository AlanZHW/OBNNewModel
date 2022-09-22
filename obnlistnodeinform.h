#ifndef OBNLISTNODEINFORM_H
#define OBNLISTNODEINFORM_H

#include <QLabel>
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

    void setHostInforms(QVector<HostsState> pHostInforms);

private:
    Ui::OBNListNodeInform *ui;
};

#endif // OBNLISTNODEINFORM_H
