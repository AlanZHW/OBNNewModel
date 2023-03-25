/********************************************************************************
** Form generated from reading UI file 'obnmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNMAINWINDOW_H
#define UI_OBNMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "mytabwidget.h"

QT_BEGIN_NAMESPACE

class Ui_OBNMainWindow
{
public:
    QAction *action_newproject;
    QAction *action_openproject;
    QAction *action_close;
    QAction *action_basemap;
    QAction *action_dataloat;
    QAction *action_logDataLoad;
    QAction *action_textLoad;
    QAction *action_VaSpStMap;
    QAction *action_FIWD;
    QAction *action_VFO;
    QAction *action_FAE;
    QAction *action_RSP;
    QAction *action_RMP;
    QAction *action_ISSP;
    QAction *action_QRA;
    QAction *action_help;
    QAction *actionDefault;
    QAction *actionCoffee;
    QAction *actionMetro;
    QAction *action_help_2;
    QAction *actionDefault_2;
    QAction *actionCoffee_2;
    QAction *actionMetroUI;
    QAction *action_display;
    QAction *action_Horizon;
    QAction *actionWellTrajectory;
    QAction *actionLoggingLoad;
    QAction *actionMudLogging;
    QAction *actionVelocity;
    QAction *actionDispLogging;
    QAction *action;
    QWidget *centralwidget;
    QGridLayout *gridLayout_10;
    QWidget *widgetMenu;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tabRNM;
    QGridLayout *gridLayout_5;
    QWidget *widgetDataManager;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButtonRealTimWaveform;
    QToolButton *toolButtonPositionSystem;
    QToolButton *toolButtonOTA;
    QToolButton *toolButtonRNM;
    QWidget *tabLMGR;
    QGridLayout *gridLayout_9;
    QWidget *widget_2;
    QGridLayout *gridLayout_8;
    QToolButton *toolButtonNewArea;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButtonDeleteArea;
    QToolButton *toolButtonOpenArea;
    QToolButton *toolButtonUpdateArea;
    QWidget *tabDMC;
    QGridLayout *gridLayout_6;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QToolButton *toolButtonHTimeAnilysis;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonExportSEGY;
    QToolButton *toolButtonLogDisplay;
    QToolButton *toolButtonOpenSEGY;
    QToolButton *toolButtonCalibration;
    QWidget *tabQC;
    QGridLayout *gridLayout_7;
    QWidget *widget_4;
    QGridLayout *gridLayout_4;
    QToolButton *toolButtonJobAnalysis;
    QSpacerItem *horizontalSpacer_4;
    QWidget *tabHELP;
    QGridLayout *gridLayout_12;
    QWidget *widget;
    QGridLayout *gridLayout_11;
    QToolButton *toolButtonHelp;
    QSpacerItem *horizontalSpacer_5;
    QSplitter *splitter_2;
    QTreeView *treeView_DataList;
    QSplitter *splitter;
    QWidget *widgetBaseImage;
    QGridLayout *gridLayout_13;
    MyTabWidget *tabWidgetMain;
    QTableWidget *tableWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OBNMainWindow)
    {
        if (OBNMainWindow->objectName().isEmpty())
            OBNMainWindow->setObjectName(QString::fromUtf8("OBNMainWindow"));
        OBNMainWindow->resize(1053, 635);
        action_newproject = new QAction(OBNMainWindow);
        action_newproject->setObjectName(QString::fromUtf8("action_newproject"));
        action_openproject = new QAction(OBNMainWindow);
        action_openproject->setObjectName(QString::fromUtf8("action_openproject"));
        action_close = new QAction(OBNMainWindow);
        action_close->setObjectName(QString::fromUtf8("action_close"));
        action_basemap = new QAction(OBNMainWindow);
        action_basemap->setObjectName(QString::fromUtf8("action_basemap"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        action_basemap->setFont(font);
        action_dataloat = new QAction(OBNMainWindow);
        action_dataloat->setObjectName(QString::fromUtf8("action_dataloat"));
        action_logDataLoad = new QAction(OBNMainWindow);
        action_logDataLoad->setObjectName(QString::fromUtf8("action_logDataLoad"));
        action_textLoad = new QAction(OBNMainWindow);
        action_textLoad->setObjectName(QString::fromUtf8("action_textLoad"));
        action_VaSpStMap = new QAction(OBNMainWindow);
        action_VaSpStMap->setObjectName(QString::fromUtf8("action_VaSpStMap"));
        action_FIWD = new QAction(OBNMainWindow);
        action_FIWD->setObjectName(QString::fromUtf8("action_FIWD"));
        action_VFO = new QAction(OBNMainWindow);
        action_VFO->setObjectName(QString::fromUtf8("action_VFO"));
        action_FAE = new QAction(OBNMainWindow);
        action_FAE->setObjectName(QString::fromUtf8("action_FAE"));
        action_RSP = new QAction(OBNMainWindow);
        action_RSP->setObjectName(QString::fromUtf8("action_RSP"));
        action_RMP = new QAction(OBNMainWindow);
        action_RMP->setObjectName(QString::fromUtf8("action_RMP"));
        action_ISSP = new QAction(OBNMainWindow);
        action_ISSP->setObjectName(QString::fromUtf8("action_ISSP"));
        action_QRA = new QAction(OBNMainWindow);
        action_QRA->setObjectName(QString::fromUtf8("action_QRA"));
        action_help = new QAction(OBNMainWindow);
        action_help->setObjectName(QString::fromUtf8("action_help"));
        actionDefault = new QAction(OBNMainWindow);
        actionDefault->setObjectName(QString::fromUtf8("actionDefault"));
        actionCoffee = new QAction(OBNMainWindow);
        actionCoffee->setObjectName(QString::fromUtf8("actionCoffee"));
        actionMetro = new QAction(OBNMainWindow);
        actionMetro->setObjectName(QString::fromUtf8("actionMetro"));
        action_help_2 = new QAction(OBNMainWindow);
        action_help_2->setObjectName(QString::fromUtf8("action_help_2"));
        actionDefault_2 = new QAction(OBNMainWindow);
        actionDefault_2->setObjectName(QString::fromUtf8("actionDefault_2"));
        actionCoffee_2 = new QAction(OBNMainWindow);
        actionCoffee_2->setObjectName(QString::fromUtf8("actionCoffee_2"));
        actionMetroUI = new QAction(OBNMainWindow);
        actionMetroUI->setObjectName(QString::fromUtf8("actionMetroUI"));
        action_display = new QAction(OBNMainWindow);
        action_display->setObjectName(QString::fromUtf8("action_display"));
        action_Horizon = new QAction(OBNMainWindow);
        action_Horizon->setObjectName(QString::fromUtf8("action_Horizon"));
        actionWellTrajectory = new QAction(OBNMainWindow);
        actionWellTrajectory->setObjectName(QString::fromUtf8("actionWellTrajectory"));
        actionLoggingLoad = new QAction(OBNMainWindow);
        actionLoggingLoad->setObjectName(QString::fromUtf8("actionLoggingLoad"));
        actionMudLogging = new QAction(OBNMainWindow);
        actionMudLogging->setObjectName(QString::fromUtf8("actionMudLogging"));
        actionVelocity = new QAction(OBNMainWindow);
        actionVelocity->setObjectName(QString::fromUtf8("actionVelocity"));
        actionDispLogging = new QAction(OBNMainWindow);
        actionDispLogging->setObjectName(QString::fromUtf8("actionDispLogging"));
        action = new QAction(OBNMainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        centralwidget = new QWidget(OBNMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_10 = new QGridLayout(centralwidget);
        gridLayout_10->setSpacing(10);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        widgetMenu = new QWidget(centralwidget);
        widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
        widgetMenu->setMaximumSize(QSize(16777215, 156));
        widgetMenu->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(widgetMenu);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 5, 0, 0);
        tabWidget = new QTabWidget(widgetMenu);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMaximumSize(QSize(16777215, 156));
        tabWidget->setBaseSize(QSize(0, 116));
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8("/***\n"
"QTabBar::tab{\n"
"	height:40;\n"
"}\n"
"QTabBar::tab{\n"
"	background-color:#2C1F82;\n"
"	color:#ffffff;\n"
"}\n"
"QTabBar::tab::selected{\n"
"	background-color:#fbfbfb;\n"
"	color:#000000;\n"
"}\n"
"QTabWidget::pane\n"
"{\n"
"	border: -1px;\n"
"	left: 1px;\n"
"}\n"
"***/"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setElideMode(Qt::ElideMiddle);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabRNM = new QWidget();
        tabRNM->setObjectName(QString::fromUtf8("tabRNM"));
        gridLayout_5 = new QGridLayout(tabRNM);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        widgetDataManager = new QWidget(tabRNM);
        widgetDataManager->setObjectName(QString::fromUtf8("widgetDataManager"));
        widgetDataManager->setStyleSheet(QString::fromUtf8("background:qlineargradient(spread:pad,x1:0,y2:1,x1:0,y2:1,stop:0 #fbfbfb,stop:1 #e8e8e8);\n"
"\n"
"QToolButton{\n"
"	border:none;\n"
"}"));
        gridLayout_2 = new QGridLayout(widgetDataManager);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(42);
        gridLayout_2->setContentsMargins(32, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(564, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        toolButtonRealTimWaveform = new QToolButton(widgetDataManager);
        toolButtonRealTimWaveform->setObjectName(QString::fromUtf8("toolButtonRealTimWaveform"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolButtonRealTimWaveform->sizePolicy().hasHeightForWidth());
        toolButtonRealTimWaveform->setSizePolicy(sizePolicy);
        toolButtonRealTimWaveform->setMinimumSize(QSize(70, 70));
        toolButtonRealTimWaveform->setMaximumSize(QSize(70, 70));
        toolButtonRealTimWaveform->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(toolButtonRealTimWaveform, 0, 2, 1, 1);

        toolButtonPositionSystem = new QToolButton(widgetDataManager);
        toolButtonPositionSystem->setObjectName(QString::fromUtf8("toolButtonPositionSystem"));
        sizePolicy.setHeightForWidth(toolButtonPositionSystem->sizePolicy().hasHeightForWidth());
        toolButtonPositionSystem->setSizePolicy(sizePolicy);
        toolButtonPositionSystem->setMinimumSize(QSize(70, 70));
        toolButtonPositionSystem->setMaximumSize(QSize(70, 70));
        toolButtonPositionSystem->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(toolButtonPositionSystem, 0, 4, 1, 1);

        toolButtonOTA = new QToolButton(widgetDataManager);
        toolButtonOTA->setObjectName(QString::fromUtf8("toolButtonOTA"));
        sizePolicy.setHeightForWidth(toolButtonOTA->sizePolicy().hasHeightForWidth());
        toolButtonOTA->setSizePolicy(sizePolicy);
        toolButtonOTA->setMinimumSize(QSize(70, 70));
        toolButtonOTA->setMaximumSize(QSize(70, 70));
        toolButtonOTA->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(toolButtonOTA, 0, 3, 1, 1);

        toolButtonRNM = new QToolButton(widgetDataManager);
        toolButtonRNM->setObjectName(QString::fromUtf8("toolButtonRNM"));
        sizePolicy.setHeightForWidth(toolButtonRNM->sizePolicy().hasHeightForWidth());
        toolButtonRNM->setSizePolicy(sizePolicy);
        toolButtonRNM->setMinimumSize(QSize(70, 70));
        toolButtonRNM->setMaximumSize(QSize(70, 70));
        toolButtonRNM->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(toolButtonRNM, 0, 0, 1, 1);


        gridLayout_5->addWidget(widgetDataManager, 0, 0, 1, 1);

        tabWidget->addTab(tabRNM, QString());
        tabLMGR = new QWidget();
        tabLMGR->setObjectName(QString::fromUtf8("tabLMGR"));
        gridLayout_9 = new QGridLayout(tabLMGR);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(tabLMGR);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setAutoFillBackground(false);
        widget_2->setStyleSheet(QString::fromUtf8("background:qlineargradient(spread:pad,x1:0,y2:1,x1:0,y2:1,stop:0 #fbfbfb,stop:1 #e8e8e8);"));
        gridLayout_8 = new QGridLayout(widget_2);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setHorizontalSpacing(42);
        gridLayout_8->setContentsMargins(32, -1, -1, -1);
        toolButtonNewArea = new QToolButton(widget_2);
        toolButtonNewArea->setObjectName(QString::fromUtf8("toolButtonNewArea"));
        toolButtonNewArea->setMinimumSize(QSize(70, 70));
        toolButtonNewArea->setMaximumSize(QSize(70, 70));

        gridLayout_8->addWidget(toolButtonNewArea, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_3, 0, 4, 1, 1);

        toolButtonDeleteArea = new QToolButton(widget_2);
        toolButtonDeleteArea->setObjectName(QString::fromUtf8("toolButtonDeleteArea"));
        toolButtonDeleteArea->setMinimumSize(QSize(70, 70));
        toolButtonDeleteArea->setMaximumSize(QSize(70, 70));

        gridLayout_8->addWidget(toolButtonDeleteArea, 0, 3, 1, 1);

        toolButtonOpenArea = new QToolButton(widget_2);
        toolButtonOpenArea->setObjectName(QString::fromUtf8("toolButtonOpenArea"));
        toolButtonOpenArea->setMinimumSize(QSize(70, 70));
        toolButtonOpenArea->setMaximumSize(QSize(70, 70));

        gridLayout_8->addWidget(toolButtonOpenArea, 0, 1, 1, 1);

        toolButtonUpdateArea = new QToolButton(widget_2);
        toolButtonUpdateArea->setObjectName(QString::fromUtf8("toolButtonUpdateArea"));
        toolButtonUpdateArea->setMinimumSize(QSize(70, 70));
        toolButtonUpdateArea->setMaximumSize(QSize(70, 70));

        gridLayout_8->addWidget(toolButtonUpdateArea, 0, 2, 1, 1);


        gridLayout_9->addWidget(widget_2, 0, 0, 1, 1);

        tabWidget->addTab(tabLMGR, QString());
        tabDMC = new QWidget();
        tabDMC->setObjectName(QString::fromUtf8("tabDMC"));
        tabDMC->setStyleSheet(QString::fromUtf8(""));
        gridLayout_6 = new QGridLayout(tabDMC);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(tabDMC);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8("background:qlineargradient(spread:pad,x1:0,y2:1,x1:0,y2:1,stop:0 #fbfbfb,stop:1 #e8e8e8);\n"
"\n"
""));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(42);
        gridLayout_3->setContentsMargins(32, -1, -1, -1);
        toolButtonHTimeAnilysis = new QToolButton(widget_3);
        toolButtonHTimeAnilysis->setObjectName(QString::fromUtf8("toolButtonHTimeAnilysis"));
        toolButtonHTimeAnilysis->setMinimumSize(QSize(70, 70));
        toolButtonHTimeAnilysis->setMaximumSize(QSize(70, 70));

        gridLayout_3->addWidget(toolButtonHTimeAnilysis, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(827, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 5, 1, 1);

        toolButtonExportSEGY = new QToolButton(widget_3);
        toolButtonExportSEGY->setObjectName(QString::fromUtf8("toolButtonExportSEGY"));
        toolButtonExportSEGY->setMinimumSize(QSize(70, 70));
        toolButtonExportSEGY->setMaximumSize(QSize(70, 70));

        gridLayout_3->addWidget(toolButtonExportSEGY, 0, 1, 1, 1);

        toolButtonLogDisplay = new QToolButton(widget_3);
        toolButtonLogDisplay->setObjectName(QString::fromUtf8("toolButtonLogDisplay"));
        toolButtonLogDisplay->setMinimumSize(QSize(70, 70));
        toolButtonLogDisplay->setMaximumSize(QSize(70, 70));

        gridLayout_3->addWidget(toolButtonLogDisplay, 0, 3, 1, 1);

        toolButtonOpenSEGY = new QToolButton(widget_3);
        toolButtonOpenSEGY->setObjectName(QString::fromUtf8("toolButtonOpenSEGY"));
        toolButtonOpenSEGY->setMinimumSize(QSize(70, 70));
        toolButtonOpenSEGY->setMaximumSize(QSize(70, 70));

        gridLayout_3->addWidget(toolButtonOpenSEGY, 0, 0, 1, 1);

        toolButtonCalibration = new QToolButton(widget_3);
        toolButtonCalibration->setObjectName(QString::fromUtf8("toolButtonCalibration"));
        toolButtonCalibration->setMinimumSize(QSize(70, 70));
        toolButtonCalibration->setMaximumSize(QSize(70, 70));

        gridLayout_3->addWidget(toolButtonCalibration, 0, 4, 1, 1);


        gridLayout_6->addWidget(widget_3, 0, 0, 1, 1);

        tabWidget->addTab(tabDMC, QString());
        tabQC = new QWidget();
        tabQC->setObjectName(QString::fromUtf8("tabQC"));
        gridLayout_7 = new QGridLayout(tabQC);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(tabQC);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("background:qlineargradient(spread:pad,x1:0,y2:1,x1:0,y2:1,stop:0 #fbfbfb,stop:1 #e8e8e8);\n"
"\n"
""));
        gridLayout_4 = new QGridLayout(widget_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(42);
        gridLayout_4->setContentsMargins(32, -1, -1, -1);
        toolButtonJobAnalysis = new QToolButton(widget_4);
        toolButtonJobAnalysis->setObjectName(QString::fromUtf8("toolButtonJobAnalysis"));
        toolButtonJobAnalysis->setMinimumSize(QSize(70, 70));
        toolButtonJobAnalysis->setMaximumSize(QSize(70, 70));

        gridLayout_4->addWidget(toolButtonJobAnalysis, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(827, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 0, 1, 1, 1);


        gridLayout_7->addWidget(widget_4, 0, 0, 1, 1);

        tabWidget->addTab(tabQC, QString());
        tabHELP = new QWidget();
        tabHELP->setObjectName(QString::fromUtf8("tabHELP"));
        gridLayout_12 = new QGridLayout(tabHELP);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(tabHELP);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background:qlineargradient(spread:pad,x1:0,y2:1,x1:0,y2:1,stop:0 #fbfbfb,stop:1 #e8e8e8);"));
        gridLayout_11 = new QGridLayout(widget);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setHorizontalSpacing(42);
        gridLayout_11->setContentsMargins(32, -1, -1, -1);
        toolButtonHelp = new QToolButton(widget);
        toolButtonHelp->setObjectName(QString::fromUtf8("toolButtonHelp"));
        toolButtonHelp->setMinimumSize(QSize(70, 70));
        toolButtonHelp->setMaximumSize(QSize(70, 70));

        gridLayout_11->addWidget(toolButtonHelp, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(893, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_5, 0, 1, 1, 1);


        gridLayout_12->addWidget(widget, 0, 0, 1, 1);

        tabWidget->addTab(tabHELP, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout_10->addWidget(widgetMenu, 0, 0, 1, 1);

        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setLineWidth(0);
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setHandleWidth(10);
        treeView_DataList = new QTreeView(splitter_2);
        treeView_DataList->setObjectName(QString::fromUtf8("treeView_DataList"));
        treeView_DataList->setMaximumSize(QSize(343, 16777215));
        treeView_DataList->setStyleSheet(QString::fromUtf8("QTreeView::item{\n"
"	height:35px;\n"
"}\n"
"background-color:#FFFFFF"));
        treeView_DataList->setLineWidth(5);
        splitter_2->addWidget(treeView_DataList);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(10);
        widgetBaseImage = new QWidget(splitter);
        widgetBaseImage->setObjectName(QString::fromUtf8("widgetBaseImage"));
        widgetBaseImage->setStyleSheet(QString::fromUtf8(""));
        gridLayout_13 = new QGridLayout(widgetBaseImage);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        tabWidgetMain = new MyTabWidget(widgetBaseImage);
        tabWidgetMain->setObjectName(QString::fromUtf8("tabWidgetMain"));
        tabWidgetMain->setStyleSheet(QString::fromUtf8("/**\n"
"QTabBar::tab{\n"
"	height:33;\n"
"}\n"
"QTabBar::tab::selected{\n"
"	background-color:#FFFFFF;\n"
"}\n"
"QTabBar::tab::!selected{\n"
"	background-color:#D9D9D9;\n"
"}**/"));
        tabWidgetMain->setTabsClosable(true);

        gridLayout_13->addWidget(tabWidgetMain, 0, 0, 1, 1);

        splitter->addWidget(widgetBaseImage);
        tableWidget = new QTableWidget(splitter);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMaximumSize(QSize(16777215, 100));
        splitter->addWidget(tableWidget);
        splitter_2->addWidget(splitter);

        gridLayout_10->addWidget(splitter_2, 1, 0, 1, 1);

        OBNMainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(OBNMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OBNMainWindow->setStatusBar(statusbar);

        retranslateUi(OBNMainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OBNMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *OBNMainWindow)
    {
        OBNMainWindow->setWindowTitle(QApplication::translate("OBNMainWindow", "\350\277\234\347\250\213\350\212\202\347\202\271\347\256\241\347\220\206\345\231\250", nullptr));
        action_newproject->setText(QApplication::translate("OBNMainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256   ", nullptr));
        action_openproject->setText(QApplication::translate("OBNMainWindow", "\346\211\223\345\274\200\351\241\271\347\233\256   ", nullptr));
        action_close->setText(QApplication::translate("OBNMainWindow", "\351\200\200\345\207\272", nullptr));
        action_basemap->setText(QApplication::translate("OBNMainWindow", "\345\272\225\345\233\276", nullptr));
        action_dataloat->setText(QApplication::translate("OBNMainWindow", "\345\234\260\351\234\207\346\225\260\346\215\256", nullptr));
        action_logDataLoad->setText(QApplication::translate("OBNMainWindow", "\346\265\213\344\272\225\346\225\260\346\215\256", nullptr));
        action_textLoad->setText(QApplication::translate("OBNMainWindow", "\346\226\207\346\234\254\345\257\274\345\205\245", nullptr));
        action_VaSpStMap->setText(QApplication::translate("OBNMainWindow", "\345\217\230\351\200\237\346\236\204\351\200\240\346\210\220\345\233\276", nullptr));
        action_FIWD->setText(QApplication::translate("OBNMainWindow", "\351\232\217\351\222\273\345\277\253\351\200\237\346\210\220\345\203\217", nullptr));
        action_VFO->setText(QApplication::translate("OBNMainWindow", "\351\200\237\345\272\246\345\234\272\344\274\230\345\214\226", nullptr));
        action_FAE->setText(QApplication::translate("OBNMainWindow", "\346\226\255\350\243\202\345\261\236\346\200\247\346\217\220\345\217\226", nullptr));
        action_RSP->setText(QApplication::translate("OBNMainWindow", "\345\216\213\345\212\233\347\263\273\347\273\237\345\217\202\346\225\260", nullptr));
        action_RMP->setText(QApplication::translate("OBNMainWindow", "\345\262\251\347\237\263\345\212\233\345\255\246\345\217\202\346\225\260", nullptr));
        action_ISSP->setText(QApplication::translate("OBNMainWindow", "\345\234\260\345\272\224\345\212\233\345\217\202\346\225\260", nullptr));
        action_QRA->setText(QApplication::translate("OBNMainWindow", "\351\243\216\351\231\251\351\207\217\345\214\226\350\257\204\344\274\260", nullptr));
        action_help->setText(QApplication::translate("OBNMainWindow", "\345\270\256\345\212\251", nullptr));
        actionDefault->setText(QApplication::translate("OBNMainWindow", "\351\273\230\350\256\244\351\243\216\346\240\274", nullptr));
        actionCoffee->setText(QApplication::translate("OBNMainWindow", "Coffee", nullptr));
        actionMetro->setText(QApplication::translate("OBNMainWindow", "MetroUI", nullptr));
        action_help_2->setText(QApplication::translate("OBNMainWindow", "\345\270\256\345\212\251", nullptr));
        actionDefault_2->setText(QApplication::translate("OBNMainWindow", "\351\273\230\350\256\244\351\243\216\346\240\274", nullptr));
        actionCoffee_2->setText(QApplication::translate("OBNMainWindow", "Coffee", nullptr));
        actionMetroUI->setText(QApplication::translate("OBNMainWindow", "MetroUI", nullptr));
        action_display->setText(QApplication::translate("OBNMainWindow", "\345\234\260\351\234\207\346\230\276\347\244\272", nullptr));
        action_Horizon->setText(QApplication::translate("OBNMainWindow", "\345\261\202\344\275\215\346\225\260\346\215\256", nullptr));
        actionWellTrajectory->setText(QApplication::translate("OBNMainWindow", "\344\272\225\350\275\250\350\277\271\346\225\260\346\215\256", nullptr));
        actionLoggingLoad->setText(QApplication::translate("OBNMainWindow", "\346\265\213\344\272\225\346\225\260\346\215\256", nullptr));
        actionMudLogging->setText(QApplication::translate("OBNMainWindow", "\345\275\225\344\272\225\346\225\260\346\215\256", nullptr));
        actionVelocity->setText(QApplication::translate("OBNMainWindow", "\345\216\237\345\247\213\351\200\237\345\272\246\345\234\272", nullptr));
        actionDispLogging->setText(QApplication::translate("OBNMainWindow", "\346\265\213\344\272\225\346\230\276\347\244\272", nullptr));
        action->setText(QApplication::translate("OBNMainWindow", "\345\257\274\345\205\245\351\200\237\345\272\246\346\225\260\346\215\256", nullptr));
        toolButtonRealTimWaveform->setText(QString());
        toolButtonPositionSystem->setText(QString());
        toolButtonOTA->setText(QString());
        toolButtonRNM->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabRNM), QApplication::translate("OBNMainWindow", "\350\212\202\347\202\271\347\256\241\347\220\206", nullptr));
        toolButtonNewArea->setText(QString());
        toolButtonDeleteArea->setText(QString());
        toolButtonOpenArea->setText(QString());
        toolButtonUpdateArea->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabLMGR), QApplication::translate("OBNMainWindow", " \350\247\202\346\265\213\347\263\273\347\273\237", nullptr));
        toolButtonHTimeAnilysis->setText(QString());
        toolButtonExportSEGY->setText(QString());
        toolButtonLogDisplay->setText(QString());
        toolButtonOpenSEGY->setText(QString());
        toolButtonCalibration->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabDMC), QApplication::translate("OBNMainWindow", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        toolButtonJobAnalysis->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabQC), QApplication::translate("OBNMainWindow", "\350\264\250\351\207\217\346\216\247\345\210\266", nullptr));
        toolButtonHelp->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabHELP), QApplication::translate("OBNMainWindow", "\345\270\256\345\212\251\346\226\207\346\241\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNMainWindow: public Ui_OBNMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNMAINWINDOW_H
