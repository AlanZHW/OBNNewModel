#ifndef OBNREALCONTROLWIDGET_H
#define OBNREALCONTROLWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QTabWidget>

#include "LowerComputerControlPublic.h"
#include "obnretrieveavailablenodes.h"
#include "obnlowercumputerota.h"

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

    /// ======
    void selectAllFunction(bool flag);

public slots:
    void slotCurrentTabChange(const int & index);

signals:
    void signalCurrentTabChange(const int & index);

private:
    Ui::OBNRealControlWidget *ui;
};

#endif // OBNREALCONTROLWIDGET_H
