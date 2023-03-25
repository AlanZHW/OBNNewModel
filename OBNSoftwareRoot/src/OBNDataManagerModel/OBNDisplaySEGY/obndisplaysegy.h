#ifndef OBNDISPLAYSEGY_H
#define OBNDISPLAYSEGY_H

#include <QVBoxLayout>
#include <QMainWindow>

#include "dmgrunit.h"
#include "qcplotter.h"
#include "gatherrecord.h"
#include "plotparamdlg.h"
#include "obndisplaysegy_global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OBNDisplaySEGY; }
QT_END_NAMESPACE

class OBNDISPLAYSEGY_EXPORT OBNDisplaySEGY : public QMainWindow
{
    Q_OBJECT

public:
    OBNDisplaySEGY(QWidget *parent = nullptr);
    ~OBNDisplaySEGY();
    /// ======
    void setCurrentSEGYFileHandles(QList<SegyFileHandle*>, int, int, OpenFilesType);

    GatherInfo m_gatherInfo;

private slots:
    /// ====== FILE-Menu
    void slotAbout();
    void slotExit();
    void slotDisplayOption();

    /// ======
    void slotPreviousGather();
    void slotNextGather();
    void slotMoveToGather();

    void slotZoomIn(const bool &enable);
    void slotZoomOut();

    void slotTraceInform(const bool&);

    /// ====== 读取SEGY数据
    void slotReadGather(const int&);
private:
    QCPlotter*   m_QCPlotter;
    MenuManager* m_menuInform;
    ToolManager* m_toolInfrom;
    PlotParamDlg *m_paramDlg;
    //当前文件句柄
    QList<SegyFileHandle*> m_FileHandles;
    int                 m_maxShowTraces;
    int                 m_startTrace; //起始道，规划道集后的起始，可以为负值
    GatherRecord       *m_gatherRecord;
    //道头和数据
    TraceHead          *m_headers;
    char               *m_data;

    Ui::OBNDisplaySEGY *ui;
};
#endif // OBNDISPLAYSEGY_H
