#ifndef OBNLOGVISUALIZATIONCURVECOLOR_H
#define OBNLOGVISUALIZATIONCURVECOLOR_H

#include <QLabel>
#include <QDialog>

namespace Ui {
class OBNLogVisualizationCurveColor;
}

class OBNLogVisualizationCurveColor : public QDialog
{
    Q_OBJECT

public:
    explicit OBNLogVisualizationCurveColor(QWidget *parent = nullptr);
    ~OBNLogVisualizationCurveColor();
    void setCurrentColorInformList(const QStringList&, const QList<QColor>&);
private:
    Ui::OBNLogVisualizationCurveColor *ui;
};

#endif // OBNLOGVISUALIZATIONCURVECOLOR_H
