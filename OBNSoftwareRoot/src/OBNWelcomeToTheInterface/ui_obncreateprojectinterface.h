/********************************************************************************
** Form generated from reading UI file 'obncreateprojectinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNCREATEPROJECTINTERFACE_H
#define UI_OBNCREATEPROJECTINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_OBNCreateProjectInterface
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *labelProjectName;
    QLineEdit *lineEditProjectName;
    QLabel *label;
    QLabel *labelProjectPath;
    QLineEdit *lineEditProjectPath;
    QPushButton *pushButtonGetPath;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonOK;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *OBNCreateProjectInterface)
    {
        if (OBNCreateProjectInterface->objectName().isEmpty())
            OBNCreateProjectInterface->setObjectName(QString::fromUtf8("OBNCreateProjectInterface"));
        OBNCreateProjectInterface->resize(581, 129);
        OBNCreateProjectInterface->setMinimumSize(QSize(581, 129));
        OBNCreateProjectInterface->setMaximumSize(QSize(581, 129));
        gridLayout_2 = new QGridLayout(OBNCreateProjectInterface);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelProjectName = new QLabel(OBNCreateProjectInterface);
        labelProjectName->setObjectName(QString::fromUtf8("labelProjectName"));

        gridLayout->addWidget(labelProjectName, 0, 0, 1, 1);

        lineEditProjectName = new QLineEdit(OBNCreateProjectInterface);
        lineEditProjectName->setObjectName(QString::fromUtf8("lineEditProjectName"));

        gridLayout->addWidget(lineEditProjectName, 0, 1, 1, 1);

        label = new QLabel(OBNCreateProjectInterface);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        labelProjectPath = new QLabel(OBNCreateProjectInterface);
        labelProjectPath->setObjectName(QString::fromUtf8("labelProjectPath"));

        gridLayout->addWidget(labelProjectPath, 1, 0, 1, 1);

        lineEditProjectPath = new QLineEdit(OBNCreateProjectInterface);
        lineEditProjectPath->setObjectName(QString::fromUtf8("lineEditProjectPath"));

        gridLayout->addWidget(lineEditProjectPath, 1, 1, 1, 1);

        pushButtonGetPath = new QPushButton(OBNCreateProjectInterface);
        pushButtonGetPath->setObjectName(QString::fromUtf8("pushButtonGetPath"));

        gridLayout->addWidget(pushButtonGetPath, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(123, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonCancel = new QPushButton(OBNCreateProjectInterface);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        horizontalSpacer_2 = new QSpacerItem(124, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonOK = new QPushButton(OBNCreateProjectInterface);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));

        horizontalLayout->addWidget(pushButtonOK);

        horizontalSpacer_3 = new QSpacerItem(123, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(OBNCreateProjectInterface);

        QMetaObject::connectSlotsByName(OBNCreateProjectInterface);
    } // setupUi

    void retranslateUi(QDialog *OBNCreateProjectInterface)
    {
        OBNCreateProjectInterface->setWindowTitle(QApplication::translate("OBNCreateProjectInterface", "\345\210\233\345\273\272\345\267\245\345\214\272", nullptr));
        labelProjectName->setText(QApplication::translate("OBNCreateProjectInterface", "\345\267\245\345\214\272\345\220\215", nullptr));
        label->setText(QString());
        labelProjectPath->setText(QApplication::translate("OBNCreateProjectInterface", "\345\267\245\345\214\272\350\267\257\345\276\204", nullptr));
        pushButtonGetPath->setText(QApplication::translate("OBNCreateProjectInterface", "......", nullptr));
        pushButtonCancel->setText(QApplication::translate("OBNCreateProjectInterface", "\345\217\226\346\266\210", nullptr));
        pushButtonOK->setText(QApplication::translate("OBNCreateProjectInterface", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNCreateProjectInterface: public Ui_OBNCreateProjectInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNCREATEPROJECTINTERFACE_H
