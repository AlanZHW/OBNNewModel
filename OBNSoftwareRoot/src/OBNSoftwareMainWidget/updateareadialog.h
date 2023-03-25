#ifndef UPDATEAREADIALOG_H
#define UPDATEAREADIALOG_H

#include "abstractareadialog.h"
#include "spsfiles.h"
#include "projectarea.h"

class UpdateAreaDialog : public AbstractAreaDialog
{
    Q_OBJECT
public:
    UpdateAreaDialog(QWidget *parent = 0);
    void  updateArea(const QString &areaName);
protected slots:
    void run();
    void slotHelp();
};

#endif // UPDATEAREADIALOG_H
