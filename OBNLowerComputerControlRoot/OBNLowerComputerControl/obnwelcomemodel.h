#ifndef OBNWELCOMEMODEL_H
#define OBNWELCOMEMODEL_H

#include <QFile>
#include <QDialog>
#include "obnlowercomputercontrol.h"

namespace Ui {
class OBNWelcomeModel;
}

class OBNWelcomeModel : public QDialog
{
    Q_OBJECT
public:
    explicit OBNWelcomeModel(QWidget *parent = nullptr);
    ~OBNWelcomeModel();

public slots:
    void slotEnterTheSystem();

private:
    Ui::OBNWelcomeModel *ui;
};

#endif // OBNWELCOMEMODEL_H
