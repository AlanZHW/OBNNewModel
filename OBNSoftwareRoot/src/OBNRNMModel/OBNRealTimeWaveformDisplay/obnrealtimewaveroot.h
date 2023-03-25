#ifndef OBNREALTIMEWAVEROOT_H
#define OBNREALTIMEWAVEROOT_H

#include <QIcon>
#include <QDialog>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMainWindow>

#include "publicHostInform.h"
#include "obnrealtimewaveformsetup.h"
#include "obnretrieveavailablenodes.h"
#include "obnrealtimewaveformdispgroup.h"
#include "obnrealtimewaveformdisplay_global.h"
namespace Ui {
class OBNRealTimeWaveRoot;
}

class OBNREALTIMEWAVEFORMDISPLAY_EXPORT OBNRealTimeWaveRoot : public QMainWindow
{
    Q_OBJECT

public:
    explicit OBNRealTimeWaveRoot(QWidget *parent = nullptr);
    ~OBNRealTimeWaveRoot();
    /// ====== 设置当前可用设备列表
    void setCurrentAvailableHostInformList(const QList<TCPInform>&);
private:
    void initWindow();
private:
    QAction* m_actionStartCollection;   ///< 开始采集数据
    bool     m_curentCollecting = false;
    QAction* m_actionStartDispWaveform;
    bool     m_curentDispWaveform;

    QVector<HostsState> m_hostVertor;
    ONBRetrieveAvailableNodes* m_obnSeatchHosts;
    OBNRealTimeWaveformSetup*  m_obsHostInformSetup;
    QList<OBNRealTimeWaveformDispGroup*> m_waveDispGroup;
    Ui::OBNRealTimeWaveRoot *ui;
};

#endif // OBNREALTIMEWAVEROOT_H
