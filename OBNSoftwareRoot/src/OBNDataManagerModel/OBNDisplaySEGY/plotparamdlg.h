#ifndef PLOTPARAMDLG_H
#define PLOTPARAMDLG_H

#include <QMainWindow>
#include <QDebug>
#include <QButtonGroup>

#include "projectarea.h"
#include "publicwidgets.h"
#include "core.h"
#include "qcplotter.h"

//图像参数面板
namespace Ui {
class PlotParamDlg;
}
class PlotParamDlg: public QDialog
{
    Q_OBJECT
public:
    PlotParamDlg(QCPlotter *plotter, QWidget *parent = 0);

signals:

private slots:
    void on_positiveCbx_toggled(bool checked);

    void on_negativeCbx_toggled(bool checked);

    void on_ScaleScopeCbx_currentIndexChanged(int index);

    void on_gainEdit_textChanged(const QString &arg1);

    void on_okBtn_clicked();

    void on_horiAxesLbl_currentIndexChanged(const QString &arg1);

    void on_vertAxesLbl_currentIndexChanged(int index);

    void on_horiAxesMinLenEdit_valueChanged(int arg1);

    void on_vertAxesMinLenEdit_valueChanged(int arg1);

    void on_showHoriGridCbx_clicked(bool checked);

    void on_traceIncSpx_valueChanged(int arg1);

    //---------------------
    void slotGraphModeChanged(int mode,bool );

    void slotInterpolationChanged(int interType);

    void on_startTimeEdit_editingFinished();

    void on_endTimeEdit_editingFinished();

private:
    void initDlg();

private:
    Ui::PlotParamDlg *ui;
    QCPlotter        *m_QCPlotter;
};
#endif // PLOTPARAMDLG_H
