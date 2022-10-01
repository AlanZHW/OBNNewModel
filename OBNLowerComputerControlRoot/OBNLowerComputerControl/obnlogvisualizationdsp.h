#ifndef OBNLOGVISUALIZATIONDSP_H
#define OBNLOGVISUALIZATIONDSP_H

#include <QFile>
#include <QDebug>
#include <QPainter>
#include <QWidget>
#include <QCheckBox>
#include <QIODevice>
#include <QTextStream>
#include <QPaintEvent>

#include "obnlogvisualizationdraw.h"

namespace Ui {
class OBNLogVisualizationDsp;
}

class OBNLogVisualizationDsp : public QWidget
{
    Q_OBJECT

public:
    explicit OBNLogVisualizationDsp(const QString& pName, QWidget *parent = nullptr);
    ~OBNLogVisualizationDsp();

//    void paintEvent(QPaintEvent *event);

    void readLogFileFunction(const QString& fileName);

public slots:
    /// ====== 响应全选按钮状态变化
    void slotSelAllCheckBoxStateChange(const int &);
    /// ====== 响应表格复选按钮状态变化
    void slotTableWidgetCheckBoxStateChange(const int&);

private:
    QList<SuctLOGInform> nLOGInformList;

    Ui::OBNLogVisualizationDsp *ui;
};

#endif // OBNLOGVISUALIZATIONDSP_H
