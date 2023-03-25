#ifndef OBNJOBMONITORPROGRAME_H
#define OBNJOBMONITORPROGRAME_H

#include <QDialog>

#include "jobmanager.h"
#include "obnjobmonitorprograme_global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OBNJobMonitorPrograme; }
QT_END_NAMESPACE

class OBNJOBMONITORPROGRAME_EXPORT OBNJobMonitorPrograme : public QDialog
{
    Q_OBJECT

public:
    OBNJobMonitorPrograme(QWidget *parent = nullptr);
    ~OBNJobMonitorPrograme();

public slots:
    void on_autoRefreshCbx_clicked(bool checked);
    void on_spinBox_valueChanged(int arg1);
    void on_refreshBtn_clicked();

private:
    JobManager *m_jobManager;
    ProjectInfo   m_projInfo;
    Ui::OBNJobMonitorPrograme *ui;
};
#endif // OBNJOBMONITORPROGRAME_H
