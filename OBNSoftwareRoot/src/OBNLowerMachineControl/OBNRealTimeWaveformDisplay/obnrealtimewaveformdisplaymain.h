#ifndef OBNREALTIMEWAVEFORMDISPLAYMAIN_H
#define OBNREALTIMEWAVEFORMDISPLAYMAIN_H

#include "obnrealtimewaveformdispgroup.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class OBNRealTimeWaveformDisplayMain; }
QT_END_NAMESPACE

class OBNRealTimeWaveformDisplayMain : public QWidget
{
    Q_OBJECT
public:
    OBNRealTimeWaveformDisplayMain(QWidget *parent = nullptr);
    ~OBNRealTimeWaveformDisplayMain();
    /// ====== 设置当前可用设备列表
    void setCurrentAvailableHostInformList(const QStringList & pHostInformList);
private:
    Ui::OBNRealTimeWaveformDisplayMain *ui;
};
#endif // OBNREALTIMEWAVEFORMDISPLAYMAIN_H
