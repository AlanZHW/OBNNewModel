#ifndef OBNREALCONTROLWIDGET_H
#define OBNREALCONTROLWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QTabWidget>

namespace Ui {
class OBNRealControlWidget;
}

class OBNRealControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OBNRealControlWidget(QWidget *parent = nullptr);
    ~OBNRealControlWidget();

private:
    Ui::OBNRealControlWidget *ui;
};

#endif // OBNREALCONTROLWIDGET_H
