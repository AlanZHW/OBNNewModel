/********************************************************************************
** Form generated from reading UI file 'obndeleteprojectinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNDELETEPROJECTINTERFACE_H
#define UI_OBNDELETEPROJECTINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_OBNDeleteProjectInterface
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonDelete;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *OBNDeleteProjectInterface)
    {
        if (OBNDeleteProjectInterface->objectName().isEmpty())
            OBNDeleteProjectInterface->setObjectName(QString::fromUtf8("OBNDeleteProjectInterface"));
        OBNDeleteProjectInterface->resize(618, 298);
        OBNDeleteProjectInterface->setMinimumSize(QSize(359, 0));
        OBNDeleteProjectInterface->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(OBNDeleteProjectInterface);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        tableWidget = new QTableWidget(OBNDeleteProjectInterface);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonCancel = new QPushButton(OBNDeleteProjectInterface);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonDelete = new QPushButton(OBNDeleteProjectInterface);
        pushButtonDelete->setObjectName(QString::fromUtf8("pushButtonDelete"));

        horizontalLayout->addWidget(pushButtonDelete);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(OBNDeleteProjectInterface);

        QMetaObject::connectSlotsByName(OBNDeleteProjectInterface);
    } // setupUi

    void retranslateUi(QDialog *OBNDeleteProjectInterface)
    {
        OBNDeleteProjectInterface->setWindowTitle(QApplication::translate("OBNDeleteProjectInterface", "\345\210\240\351\231\244\345\267\245\345\214\272", nullptr));
        pushButtonCancel->setText(QApplication::translate("OBNDeleteProjectInterface", "\345\217\226\346\266\210", nullptr));
        pushButtonDelete->setText(QApplication::translate("OBNDeleteProjectInterface", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNDeleteProjectInterface: public Ui_OBNDeleteProjectInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNDELETEPROJECTINTERFACE_H
