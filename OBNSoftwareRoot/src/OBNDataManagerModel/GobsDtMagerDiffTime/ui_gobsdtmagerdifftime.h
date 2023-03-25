/********************************************************************************
** Form generated from reading UI file 'gobsdtmagerdifftime.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOBSDTMAGERDIFFTIME_H
#define UI_GOBSDTMAGERDIFFTIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_GobsDtMagerDiffTime
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *labelOriginPath;
    QLineEdit *lineEditOriginPath;
    QPushButton *PushBrowse;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *EditConfig;
    QPushButton *buttonConfig;
    QLabel *labelN1;
    QLineEdit *lineEditN1;
    QLabel *labelFs;
    QLineEdit *lineEditFs;
    QLabel *labelB;
    QLineEdit *lineEditB;
    QLabel *labelF0;
    QLineEdit *lineEditF0;
    QLabel *label_3;
    QLineEdit *lineEditDistance;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *PushImplement;
    QTableWidget *tableWidget;

    void setupUi(QDialog *GobsDtMagerDiffTime)
    {
        if (GobsDtMagerDiffTime->objectName().isEmpty())
            GobsDtMagerDiffTime->setObjectName(QStringLiteral("GobsDtMagerDiffTime"));
        GobsDtMagerDiffTime->resize(718, 450);
        gridLayout_3 = new QGridLayout(GobsDtMagerDiffTime);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labelOriginPath = new QLabel(GobsDtMagerDiffTime);
        labelOriginPath->setObjectName(QStringLiteral("labelOriginPath"));

        gridLayout_2->addWidget(labelOriginPath, 0, 0, 1, 1);

        lineEditOriginPath = new QLineEdit(GobsDtMagerDiffTime);
        lineEditOriginPath->setObjectName(QStringLiteral("lineEditOriginPath"));

        gridLayout_2->addWidget(lineEditOriginPath, 0, 1, 1, 1);

        PushBrowse = new QPushButton(GobsDtMagerDiffTime);
        PushBrowse->setObjectName(QStringLiteral("PushBrowse"));

        gridLayout_2->addWidget(PushBrowse, 0, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(GobsDtMagerDiffTime);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        EditConfig = new QLineEdit(groupBox);
        EditConfig->setObjectName(QStringLiteral("EditConfig"));

        gridLayout->addWidget(EditConfig, 0, 1, 1, 4);

        buttonConfig = new QPushButton(groupBox);
        buttonConfig->setObjectName(QStringLiteral("buttonConfig"));

        gridLayout->addWidget(buttonConfig, 0, 5, 1, 1);

        labelN1 = new QLabel(groupBox);
        labelN1->setObjectName(QStringLiteral("labelN1"));

        gridLayout->addWidget(labelN1, 1, 0, 1, 1);

        lineEditN1 = new QLineEdit(groupBox);
        lineEditN1->setObjectName(QStringLiteral("lineEditN1"));

        gridLayout->addWidget(lineEditN1, 1, 1, 1, 1);

        labelFs = new QLabel(groupBox);
        labelFs->setObjectName(QStringLiteral("labelFs"));

        gridLayout->addWidget(labelFs, 1, 2, 1, 1);

        lineEditFs = new QLineEdit(groupBox);
        lineEditFs->setObjectName(QStringLiteral("lineEditFs"));

        gridLayout->addWidget(lineEditFs, 1, 3, 1, 1);

        labelB = new QLabel(groupBox);
        labelB->setObjectName(QStringLiteral("labelB"));

        gridLayout->addWidget(labelB, 1, 4, 1, 1);

        lineEditB = new QLineEdit(groupBox);
        lineEditB->setObjectName(QStringLiteral("lineEditB"));

        gridLayout->addWidget(lineEditB, 1, 5, 1, 1);

        labelF0 = new QLabel(groupBox);
        labelF0->setObjectName(QStringLiteral("labelF0"));

        gridLayout->addWidget(labelF0, 2, 0, 1, 1);

        lineEditF0 = new QLineEdit(groupBox);
        lineEditF0->setObjectName(QStringLiteral("lineEditF0"));

        gridLayout->addWidget(lineEditF0, 2, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        lineEditDistance = new QLineEdit(groupBox);
        lineEditDistance->setObjectName(QStringLiteral("lineEditDistance"));

        gridLayout->addWidget(lineEditDistance, 2, 3, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 4, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 2, 5, 1, 1);

        PushImplement = new QPushButton(groupBox);
        PushImplement->setObjectName(QStringLiteral("PushImplement"));

        gridLayout->addWidget(PushImplement, 3, 5, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        tableWidget = new QTableWidget(GobsDtMagerDiffTime);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_3->addWidget(tableWidget, 2, 0, 1, 1);


        retranslateUi(GobsDtMagerDiffTime);

        QMetaObject::connectSlotsByName(GobsDtMagerDiffTime);
    } // setupUi

    void retranslateUi(QDialog *GobsDtMagerDiffTime)
    {
        GobsDtMagerDiffTime->setWindowTitle(QApplication::translate("GobsDtMagerDiffTime", "GobsDtMagerDiffTime", 0));
        labelOriginPath->setText(QApplication::translate("GobsDtMagerDiffTime", "Origin Data Path", 0));
        PushBrowse->setText(QApplication::translate("GobsDtMagerDiffTime", "...", 0));
        groupBox->setTitle(QApplication::translate("GobsDtMagerDiffTime", "Parameter  ", 0));
        label_2->setText(QApplication::translate("GobsDtMagerDiffTime", "Config file", 0));
        buttonConfig->setText(QApplication::translate("GobsDtMagerDiffTime", "Browse", 0));
        labelN1->setText(QApplication::translate("GobsDtMagerDiffTime", "OneSampleCount", 0));
        labelFs->setText(QApplication::translate("GobsDtMagerDiffTime", "FS(sps)", 0));
        labelB->setText(QApplication::translate("GobsDtMagerDiffTime", "Bandwidth(Hz)", 0));
        labelF0->setText(QApplication::translate("GobsDtMagerDiffTime", "CenterFrequency(Hz)", 0));
        label_3->setText(QApplication::translate("GobsDtMagerDiffTime", "Distance(m)", 0));
        label->setText(QApplication::translate("GobsDtMagerDiffTime", "Area", 0));
        PushImplement->setText(QApplication::translate("GobsDtMagerDiffTime", "Implement", 0));
    } // retranslateUi

};

namespace Ui {
    class GobsDtMagerDiffTime: public Ui_GobsDtMagerDiffTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOBSDTMAGERDIFFTIME_H
