#ifndef OBNEDITPORJECTINTERFACE_H
#define OBNEDITPORJECTINTERFACE_H

#include <QDialog>

namespace Ui {
class OBNEditPorjectInterface;
}

class OBNEditPorjectInterface : public QDialog
{
    Q_OBJECT

public:
    explicit OBNEditPorjectInterface(QWidget *parent = nullptr);
    ~OBNEditPorjectInterface();

private:
    Ui::OBNEditPorjectInterface *ui;
};

#endif // OBNEDITPORJECTINTERFACE_H
