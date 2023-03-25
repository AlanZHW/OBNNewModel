#ifndef DMGRUNIT_H
#define DMGRUNIT_H

#include <QtWidgets/QWidget>
#include <QDialog>
#include <QButtonGroup>
#include <QTextBrowser>
#include <QTableWidget>
#include <QSpinBox>
#include <QApplication>

#include "projectarea.h"
#include "publicwidgets.h"
#include "core.h"
#include "qcplotter.h"

class OBNDisplaySEGY;
class QToolBar;
class QToolButton;
class QMenuBar;
class QMenu;

/// ====== 设置菜单栏
class MenuManager : public QObject
{
    Q_OBJECT
public:
    MenuManager(QObject *parent = 0);
    void createMenu(OBNDisplaySEGY *,QMenuBar *bar);
private:
    QMenu   *fileMenu,*toolsMenu,*helpMenu;
};

/// ====== 设置工具栏
class ToolManager : public QObject
{
    Q_OBJECT
public:
    ToolManager(QObject *parent = 0);
    void createTools(OBNDisplaySEGY *,QToolBar *toolBar);

signals:
    void signalZoomInEnable(const bool &enable);
    void signalTraceInformEnable(const bool &en);

private slots:
    void slotZoomIn(bool );
    void slotTraceInformation(bool);

private:
    DownToolButton *m_zoomInBtn;
    DownToolButton *m_traceInfBtn;
};


#endif // DMGRUNIT_H
