#ifndef CREATEAREADIALOG_H
#define CREATEAREADIALOG_H

#include "macro.h"
#include "spsfiles.h"
#include "projectarea.h"
#include "abstractareadialog.h"
#include <QDialog>

class CreateAreaDialog : public AbstractAreaDialog
{
    Q_OBJECT
public:
    CreateAreaDialog(QWidget *parent = 0);
protected slots:
    void run();
    void slotHelp();
};

#endif // CREATEAREADIALOG_H
