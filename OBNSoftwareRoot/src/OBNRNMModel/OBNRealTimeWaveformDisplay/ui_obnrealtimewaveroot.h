/********************************************************************************
** Form generated from reading UI file 'obnrealtimewaveroot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNREALTIMEWAVEROOT_H
#define UI_OBNREALTIMEWAVEROOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OBNRealTimeWaveRoot
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QWidget *widgetRealTimeExhibition;
    QTextBrowser *textBrowser;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *OBNRealTimeWaveRoot)
    {
        if (OBNRealTimeWaveRoot->objectName().isEmpty())
            OBNRealTimeWaveRoot->setObjectName(QString::fromUtf8("OBNRealTimeWaveRoot"));
        OBNRealTimeWaveRoot->resize(784, 613);
        centralwidget = new QWidget(OBNRealTimeWaveRoot);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(tableWidget, 0, 0, 2, 1);

        widgetRealTimeExhibition = new QWidget(centralwidget);
        widgetRealTimeExhibition->setObjectName(QString::fromUtf8("widgetRealTimeExhibition"));

        gridLayout->addWidget(widgetRealTimeExhibition, 0, 1, 1, 1);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMaximumSize(QSize(16777215, 150));

        gridLayout->addWidget(textBrowser, 1, 1, 1, 1);

        OBNRealTimeWaveRoot->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(OBNRealTimeWaveRoot);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OBNRealTimeWaveRoot->setStatusBar(statusbar);
        toolBar = new QToolBar(OBNRealTimeWaveRoot);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        OBNRealTimeWaveRoot->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(OBNRealTimeWaveRoot);

        QMetaObject::connectSlotsByName(OBNRealTimeWaveRoot);
    } // setupUi

    void retranslateUi(QMainWindow *OBNRealTimeWaveRoot)
    {
        OBNRealTimeWaveRoot->setWindowTitle(QApplication::translate("OBNRealTimeWaveRoot", "MainWindow", nullptr));
        toolBar->setWindowTitle(QApplication::translate("OBNRealTimeWaveRoot", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNRealTimeWaveRoot: public Ui_OBNRealTimeWaveRoot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNREALTIMEWAVEROOT_H
