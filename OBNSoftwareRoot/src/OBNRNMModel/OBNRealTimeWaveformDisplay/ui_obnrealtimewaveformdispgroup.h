/********************************************************************************
** Form generated from reading UI file 'obnrealtimewaveformdispgroup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNREALTIMEWAVEFORMDISPGROUP_H
#define UI_OBNREALTIMEWAVEFORMDISPGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OBNRealTimeWaveformDispGroup
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QWidget *widget;

    void setupUi(QWidget *OBNRealTimeWaveformDispGroup)
    {
        if (OBNRealTimeWaveformDispGroup->objectName().isEmpty())
            OBNRealTimeWaveformDispGroup->setObjectName(QString::fromUtf8("OBNRealTimeWaveformDispGroup"));
        OBNRealTimeWaveformDispGroup->resize(610, 214);
        OBNRealTimeWaveformDispGroup->setMinimumSize(QSize(0, 0));
        gridLayout_2 = new QGridLayout(OBNRealTimeWaveformDispGroup);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(OBNRealTimeWaveformDispGroup);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(OBNRealTimeWaveformDispGroup);

        QMetaObject::connectSlotsByName(OBNRealTimeWaveformDispGroup);
    } // setupUi

    void retranslateUi(QWidget *OBNRealTimeWaveformDispGroup)
    {
        OBNRealTimeWaveformDispGroup->setWindowTitle(QApplication::translate("OBNRealTimeWaveformDispGroup", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("OBNRealTimeWaveformDispGroup", "GroupBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNRealTimeWaveformDispGroup: public Ui_OBNRealTimeWaveformDispGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNREALTIMEWAVEFORMDISPGROUP_H
