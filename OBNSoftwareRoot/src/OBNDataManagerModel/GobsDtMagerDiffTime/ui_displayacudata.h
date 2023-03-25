/********************************************************************************
** Form generated from reading UI file 'displayacudata.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYACUDATA_H
#define UI_DISPLAYACUDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DisplayAcuData
{
public:

    void setupUi(QDialog *DisplayAcuData)
    {
        if (DisplayAcuData->objectName().isEmpty())
            DisplayAcuData->setObjectName(QStringLiteral("DisplayAcuData"));
        DisplayAcuData->resize(491, 386);

        retranslateUi(DisplayAcuData);

        QMetaObject::connectSlotsByName(DisplayAcuData);
    } // setupUi

    void retranslateUi(QDialog *DisplayAcuData)
    {
        DisplayAcuData->setWindowTitle(QApplication::translate("DisplayAcuData", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DisplayAcuData: public Ui_DisplayAcuData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYACUDATA_H
