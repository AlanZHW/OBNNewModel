/********************************************************************************
** Form generated from reading UI file 'obneditporjectinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNEDITPORJECTINTERFACE_H
#define UI_OBNEDITPORJECTINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_OBNEditPorjectInterface
{
public:

    void setupUi(QDialog *OBNEditPorjectInterface)
    {
        if (OBNEditPorjectInterface->objectName().isEmpty())
            OBNEditPorjectInterface->setObjectName(QString::fromUtf8("OBNEditPorjectInterface"));
        OBNEditPorjectInterface->resize(400, 300);

        retranslateUi(OBNEditPorjectInterface);

        QMetaObject::connectSlotsByName(OBNEditPorjectInterface);
    } // setupUi

    void retranslateUi(QDialog *OBNEditPorjectInterface)
    {
        OBNEditPorjectInterface->setWindowTitle(QApplication::translate("OBNEditPorjectInterface", "\347\274\226\350\276\221\345\267\245\345\214\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNEditPorjectInterface: public Ui_OBNEditPorjectInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNEDITPORJECTINTERFACE_H
