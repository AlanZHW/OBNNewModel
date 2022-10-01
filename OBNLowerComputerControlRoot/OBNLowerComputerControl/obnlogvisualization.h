#ifndef OBNLOGVISUALIZATION_H
#define OBNLOGVISUALIZATION_H

#include <QFile>
#include <QPointF>
#include <QWidget>
#include <QSpacerItem>
#include <QScrollArea>
#include <QStringList>
#include <QHBoxLayout>


#include "obnlogvisualizationdsp.h"

namespace Ui {
class OBNLogVisualization;
}

class OBNLogVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit OBNLogVisualization(QWidget *parent = nullptr);
    ~OBNLogVisualization();

    /// ====== 设置当前需要显示日志信息的节点列表
    void setHostInformList(const QStringList &pFileNameList);

private:
    Ui::OBNLogVisualization *ui;
};

#endif // OBNLOGVISUALIZATION_H
