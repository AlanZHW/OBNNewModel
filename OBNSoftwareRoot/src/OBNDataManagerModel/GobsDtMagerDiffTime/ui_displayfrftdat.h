/********************************************************************************
** Form generated from reading UI file 'displayfrftdat.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYFRFTDAT_H
#define UI_DISPLAYFRFTDAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DisplayFrftDat
{
public:

    void setupUi(QDialog *DisplayFrftDat)
    {
        if (DisplayFrftDat->objectName().isEmpty())
            DisplayFrftDat->setObjectName(QStringLiteral("DisplayFrftDat"));
        DisplayFrftDat->resize(400, 300);

        retranslateUi(DisplayFrftDat);

        QMetaObject::connectSlotsByName(DisplayFrftDat);
    } // setupUi

    void retranslateUi(QDialog *DisplayFrftDat)
    {
        DisplayFrftDat->setWindowTitle(QApplication::translate("DisplayFrftDat", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DisplayFrftDat: public Ui_DisplayFrftDat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYFRFTDAT_H
