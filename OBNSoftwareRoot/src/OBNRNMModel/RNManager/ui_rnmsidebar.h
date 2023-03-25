/********************************************************************************
** Form generated from reading UI file 'rnmsidebar.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RNMSIDEBAR_H
#define UI_RNMSIDEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RNMSideBar
{
public:

    void setupUi(QWidget *RNMSideBar)
    {
        if (RNMSideBar->objectName().isEmpty())
            RNMSideBar->setObjectName(QStringLiteral("RNMSideBar"));
        RNMSideBar->resize(400, 300);

        retranslateUi(RNMSideBar);

        QMetaObject::connectSlotsByName(RNMSideBar);
    } // setupUi

    void retranslateUi(QWidget *RNMSideBar)
    {
        RNMSideBar->setWindowTitle(QApplication::translate("RNMSideBar", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class RNMSideBar: public Ui_RNMSideBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RNMSIDEBAR_H
