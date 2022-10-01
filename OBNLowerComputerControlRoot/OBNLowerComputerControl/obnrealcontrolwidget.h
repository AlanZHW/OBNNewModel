#ifndef OBNREALCONTROLWIDGET_H
#define OBNREALCONTROLWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QTabWidget>

#include "LowerComputerControlPublic.h"

namespace Ui {
class OBNRealControlWidget;
}

class OBNRealControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OBNRealControlWidget(QWidget *parent = nullptr);
    ~OBNRealControlWidget();

    void setCurrentOptionalInform(const QVector<HostsState>&);

private:
    Ui::OBNRealControlWidget *ui;
};

#endif // OBNREALCONTROLWIDGET_H
