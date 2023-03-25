#ifndef OBNLOGVISUAILZATIONDISPLAY_H
#define OBNLOGVISUAILZATIONDISPLAY_H

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>

#include "obnlogvisuailzationchart.h"
#include "obnreadloghread.h"
#include "obnreadloginformprogress.h"
#include "obnlogvisualizationcurvecolor.h"
#include "obnlogvisuailzationdisp_global.h"

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
    void slotClickedSetupButton();      ///< 点击设置按钮触发槽函数
    void slotSetCurrentDisplayLabel();  ///< 复选按钮状态改变槽函数
    /// ======
    void slotReadLogInformProgress(const int& _progressValue);
    void slotReadLogInformSuccess(const QList<SuctLOGDrawInform>& _logDataInformList);
    /// ======
    void slotCancelReadLogThread();
private:
    QStringList m_logFileList;
    OBNLogVisualizationCurveColor* m_logCurveColorSetup;
    QList<SuctLOGDrawInform> m_logInformDispData;
    OBNReadLoghread* m_readLogThread;
    OBNReadLogInformProgress* m_readLogProgress;
    OBNLogVisuailzationChart* m_logVisuailzationChart;
    Ui::OBNLogVisuailzationDisplay *ui;
};
#endif // OBNLOGVISUAILZATIONDISPLAY_H
