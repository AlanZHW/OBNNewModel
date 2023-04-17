#ifndef OBNLOGVISUAILZATIONDISPLAY_H
#define OBNLOGVISUAILZATIONDISPLAY_H

#include <QDir>
#include <QFile>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QCheckBox>
#include <QColorDialog>
#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>

#include "obnlogvisuailzationchart.h"
#include "obnreadloghread.h"
#include "obnreadloginformprogress.h"
#include "obnlogvisuailzationdisp_global.h"

#define LINE_ISDISP_COLUMN 0    ///< 描述当前列是否显示
#define LINE_NAME_COLUMN   1    ///< 描述当前线数据名
#define LINE_COLOR_COLUMN  2    ///< 描述当前线颜色


QT_BEGIN_NAMESPACE
namespace Ui { class OBNLogVisuailzationDisplay; }
QT_END_NAMESPACE

class OBNLOGVISUAILZATIONDISP_EXPORT OBNLogVisuailzationDisplay : public QDialog
{
    Q_OBJECT
public:
    OBNLogVisuailzationDisplay(QWidget *parent = nullptr);
    ~OBNLogVisuailzationDisplay();

    void getBatVRange(qreal& _min, qreal& _max, int &_dtNumMax, QList<QList<QPointF> > &);
    void getTRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF> > &);
    void getPVRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF> > &);
    void getThetaRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF> > &);
    void getGammaRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF> > &);
    void getAzRange(qreal& _min, qreal& _max, int& _dtNumMax, QList<QList<QPointF> > &);
public slots:
    void slotPushButtonBrowse();        ///< 点击浏览按钮槽函数
    void slotSetCurrentDisplayLabel();  ///< 复选按钮状态改变槽函数
    /// ======
    void slotReadLogInformProgress(const int& _progressValue);
    void slotReadLogInformSuccess(const QList<SuctLOGDrawInform>& _logDataInformList);
    /// ======
    void slotCancelReadLogThread();
    /// ====== 调整表格中数据显示状态
    void slotLineDisplayStateChange(int);
private:
    QStringList m_logFileList;
    QList<SuctLOGDrawInform> m_logInformDispData;
    OBNReadLoghread* m_readLogThread;
    OBNReadLogInformProgress* m_readLogProgress;
    OBNLogVisuailzationChart* m_logVisuailzationChart;
    bool m_curentDisplaying;
    Ui::OBNLogVisuailzationDisplay *ui;
};
#endif // OBNLOGVISUAILZATIONDISPLAY_H
