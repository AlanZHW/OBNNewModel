#ifndef OBNLOWERCOMPUTERCONTROL_H
#define OBNLOWERCOMPUTERCONTROL_H

/// ====== 显示节点、OTA等主界面

#include <QFile>
#include <QDebug>
#include <QToolBar>
#include <QCheckBox>
#include <QMainWindow>

#include "obnsearchhosts.h"
#include "obnsearchhoststhread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OBNLowerComputerControl; }
QT_END_NAMESPACE

class OBNLowerComputerControl : public QMainWindow
{
    Q_OBJECT

public:
    OBNLowerComputerControl(QWidget *parent = nullptr);
    ~OBNLowerComputerControl();

    void initToolBar(); ///< 初始化工具栏

public slots:
    /// ===== 搜索
    void slotSearch();
    /// ====== 获取当前有效节点
    void slotSearchHostsList(QVector<HostsState>);

    /// ===== 全选
    void slotSelectall(int);

    /// ===== 下载
    void slotdownload();
    /// ===== 上传
    void slotupload();
    /// ===== 升级
    void slotupgrade();

private:
    QToolBar* m_toolBar;

    bool m_currentSelAll = false;

    OBNSearchHosts* m_obnSeatchHosts;

    Ui::OBNLowerComputerControl *ui;
};
#endif // OBNLOWERCOMPUTERCONTROL_H
