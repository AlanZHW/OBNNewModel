/********************************************************************************
** Form generated from reading UI file 'rnmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RNMANAGER_H
#define UI_RNMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RNManager
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *RNManager)
    {
        if (RNManager->objectName().isEmpty())
            RNManager->setObjectName(QStringLiteral("RNManager"));
        RNManager->resize(881, 531);
        centralWidget = new QWidget(RNManager);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        RNManager->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RNManager);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 881, 26));
        RNManager->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RNManager);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RNManager->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(RNManager);

        QMetaObject::connectSlotsByName(RNManager);
    } // setupUi

    void retranslateUi(QMainWindow *RNManager)
    {
        RNManager->setWindowTitle(QApplication::translate("RNManager", "RNManager", 0));
    } // retranslateUi

};

namespace Ui {
    class RNManager: public Ui_RNManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RNMANAGER_H
