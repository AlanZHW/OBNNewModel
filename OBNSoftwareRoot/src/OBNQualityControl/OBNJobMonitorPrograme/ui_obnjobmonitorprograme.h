/********************************************************************************
** Form generated from reading UI file 'obnjobmonitorprograme.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNJOBMONITORPROGRAME_H
#define UI_OBNJOBMONITORPROGRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OBNJobMonitorPrograme
{
public:
    QGridLayout *gridLayout;
    QSplitter *mainSplitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QListWidget *jobList;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *autoRefreshCbx;
    QSpinBox *spinBox;
    QLabel *label_3;
    QPushButton *refreshBtn;
    QTextBrowser *logBrowser;

    void setupUi(QDialog *OBNJobMonitorPrograme)
    {
        if (OBNJobMonitorPrograme->objectName().isEmpty())
            OBNJobMonitorPrograme->setObjectName(QString::fromUtf8("OBNJobMonitorPrograme"));
        OBNJobMonitorPrograme->resize(927, 562);
        gridLayout = new QGridLayout(OBNJobMonitorPrograme);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainSplitter = new QSplitter(OBNJobMonitorPrograme);
        mainSplitter->setObjectName(QString::fromUtf8("mainSplitter"));
        mainSplitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(mainSplitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        jobList = new QListWidget(layoutWidget);
        jobList->setObjectName(QString::fromUtf8("jobList"));

        verticalLayout->addWidget(jobList);

        mainSplitter->addWidget(layoutWidget);
        layoutWidget_2 = new QWidget(mainSplitter);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        autoRefreshCbx = new QCheckBox(layoutWidget_2);
        autoRefreshCbx->setObjectName(QString::fromUtf8("autoRefreshCbx"));

        horizontalLayout_3->addWidget(autoRefreshCbx);

        spinBox = new QSpinBox(layoutWidget_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setEnabled(false);
        spinBox->setMinimum(2);
        spinBox->setMaximum(30);
        spinBox->setValue(5);

        horizontalLayout_3->addWidget(spinBox);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        refreshBtn = new QPushButton(layoutWidget_2);
        refreshBtn->setObjectName(QString::fromUtf8("refreshBtn"));

        horizontalLayout_3->addWidget(refreshBtn);


        verticalLayout_2->addLayout(horizontalLayout_3);

        logBrowser = new QTextBrowser(layoutWidget_2);
        logBrowser->setObjectName(QString::fromUtf8("logBrowser"));

        verticalLayout_2->addWidget(logBrowser);

        mainSplitter->addWidget(layoutWidget_2);

        gridLayout->addWidget(mainSplitter, 0, 0, 1, 1);


        retranslateUi(OBNJobMonitorPrograme);

        QMetaObject::connectSlotsByName(OBNJobMonitorPrograme);
    } // setupUi

    void retranslateUi(QDialog *OBNJobMonitorPrograme)
    {
        OBNJobMonitorPrograme->setWindowTitle(QApplication::translate("OBNJobMonitorPrograme", "\344\275\234\344\270\232\347\233\221\346\216\247", nullptr));
        label->setText(QApplication::translate("OBNJobMonitorPrograme", "\344\275\234\344\270\232\345\210\227\350\241\250", nullptr));
        label_2->setText(QApplication::translate("OBNJobMonitorPrograme", "\344\275\234\344\270\232\346\227\245\345\277\227", nullptr));
        autoRefreshCbx->setText(QApplication::translate("OBNJobMonitorPrograme", "\350\207\252\345\212\250\346\233\264\346\226\260", nullptr));
        label_3->setText(QApplication::translate("OBNJobMonitorPrograme", "(\347\247\222)", nullptr));
        refreshBtn->setText(QApplication::translate("OBNJobMonitorPrograme", "&\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNJobMonitorPrograme: public Ui_OBNJobMonitorPrograme {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNJOBMONITORPROGRAME_H
