/********************************************************************************
** Form generated from reading UI file 'obnrealtimewaveformsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNREALTIMEWAVEFORMSETUP_H
#define UI_OBNREALTIMEWAVEFORMSETUP_H

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

class Ui_OBNRealTimeWaveformSetup
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidgetRealTimeWaveformSetup;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonOK;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *OBNRealTimeWaveformSetup)
    {
        if (OBNRealTimeWaveformSetup->objectName().isEmpty())
            OBNRealTimeWaveformSetup->setObjectName(QString::fromUtf8("OBNRealTimeWaveformSetup"));
        OBNRealTimeWaveformSetup->resize(739, 326);
        gridLayout = new QGridLayout(OBNRealTimeWaveformSetup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidgetRealTimeWaveformSetup = new QTableWidget(OBNRealTimeWaveformSetup);
        tableWidgetRealTimeWaveformSetup->setObjectName(QString::fromUtf8("tableWidgetRealTimeWaveformSetup"));

        gridLayout->addWidget(tableWidgetRealTimeWaveformSetup, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonOK = new QPushButton(OBNRealTimeWaveformSetup);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));

        horizontalLayout->addWidget(pushButtonOK);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonCancel = new QPushButton(OBNRealTimeWaveformSetup);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(OBNRealTimeWaveformSetup);

        QMetaObject::connectSlotsByName(OBNRealTimeWaveformSetup);
    } // setupUi

    void retranslateUi(QDialog *OBNRealTimeWaveformSetup)
    {
        OBNRealTimeWaveformSetup->setWindowTitle(QApplication::translate("OBNRealTimeWaveformSetup", "Dialog", nullptr));
        pushButtonOK->setText(QApplication::translate("OBNRealTimeWaveformSetup", "\347\241\256\345\256\232", nullptr));
        pushButtonCancel->setText(QApplication::translate("OBNRealTimeWaveformSetup", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNRealTimeWaveformSetup: public Ui_OBNRealTimeWaveformSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNREALTIMEWAVEFORMSETUP_H
