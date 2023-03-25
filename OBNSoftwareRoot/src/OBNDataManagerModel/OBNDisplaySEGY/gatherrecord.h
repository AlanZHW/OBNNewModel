#ifndef GATHERRECORD_H
#define GATHERRECORD_H

#include <QLabel>
#include <QSpinBox>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>


#include "projectarea.h"
#include "publicwidgets.h"
#include "qcplotter.h"

//segy 显示道集管理类
class GatherRecord : public QDialog
{
    Q_OBJECT
public:
    GatherRecord(QWidget *parent = 0);
    void setGatherInfo(const int &totalTraces,const int &maxTraces,const int &startTrace);

    void readNextGather();
    void readPrevGather();

    int  gatherNumer()const{return m_gatherNum;}
    int  gatherNo()const{return m_CurrentGather;}

signals:
    void signalReadGather(const int &gatherNo);

private slots:
    void slotOkClicked();
    void slotCloseClicked();

private:
    void initDlg();
    //工具栏两个前后道集功能选项，控制使能
    QAction    *m_prevAction,*m_nextAction;
    QLabel     *m_readLabel;
    QSpinBox   *m_gatherSpx;
    int         m_CurrentGather;
    int         m_gatherNum;
};
#endif // GATHERRECORD_H
