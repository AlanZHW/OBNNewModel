#ifndef OBNREALTIMEWAVEDISPLAY_H
#define OBNREALTIMEWAVEDISPLAY_H

/// 实时波形显示功能主界面

#include <QWidget>

namespace Ui {
class OBNRealTimeWaveDisplay;
}

class OBNRealTimeWaveDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit OBNRealTimeWaveDisplay(QWidget *parent = nullptr);
    ~OBNRealTimeWaveDisplay();

private:
    Ui::OBNRealTimeWaveDisplay *ui;
};

#endif // OBNREALTIMEWAVEDISPLAY_H
