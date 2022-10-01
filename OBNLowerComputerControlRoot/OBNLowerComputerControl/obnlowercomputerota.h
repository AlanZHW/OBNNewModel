#ifndef OBNLOWERCOMPUTEROTA_H
#define OBNLOWERCOMPUTEROTA_H

#include <QFile>
#include <QDebug>
#include <QWidget>
#include <QProgressBar>

#include "LowerComputerControlPublic.h"

namespace Ui {
class OBNLowerComputerOTA;
}

class OBNLowerComputerOTA : public QWidget
{
    Q_OBJECT

public:
    explicit OBNLowerComputerOTA(QWidget *parent = nullptr);
    ~OBNLowerComputerOTA();

    void setCurrentOptionalInform(const QVector<HostsState>&);

public slots:
    /// =======选择升级文件
    void slotBrowseFunction(const bool&);
    /// =======开始升级
    void slotStartFunction(const bool&);

private:
    Ui::OBNLowerComputerOTA *ui;
};

#endif // OBNLOWERCOMPUTEROTA_H
