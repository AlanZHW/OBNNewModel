#ifndef OBNCALIBRATIONLINECOLORWIDGET_H
#define OBNCALIBRATIONLINECOLORWIDGET_H

#include <QDialog>

namespace Ui {
class OBNCalibrationLineColorWidget;
}

class OBNCalibrationLineColorWidget : public QDialog
{
    Q_OBJECT
public:
    explicit OBNCalibrationLineColorWidget(QWidget *parent = nullptr);
    ~OBNCalibrationLineColorWidget();
    void setADJDataInform();
private:
    Ui::OBNCalibrationLineColorWidget *ui;
};

#endif // OBNCALIBRATIONLINECOLORWIDGET_H
