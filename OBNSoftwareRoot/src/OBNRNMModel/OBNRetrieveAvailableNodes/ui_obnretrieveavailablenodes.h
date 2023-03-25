/********************************************************************************
** Form generated from reading UI file 'obnretrieveavailablenodes.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNRETRIEVEAVAILABLENODES_H
#define UI_OBNRETRIEVEAVAILABLENODES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "iplineedit.h"

QT_BEGIN_NAMESPACE

class Ui_ONBRetrieveAvailableNodes
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *labelIpSearch;
    IPLineEdit *lineEditIpStart;
    QLabel *labelSymbol;
    IPLineEdit *lineEditIpEnd;
    QHBoxLayout *horizontalLayout;
    QLabel *labelNodeTotal;
    QLabel *labelNodeTotalDisp;
    QLabel *labelNodeIsConnected;
    QLabel *labelNodeIsConnectedDisp;
    QTableWidget *tableWidget;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *ONBRetrieveAvailableNodes)
    {
        if (ONBRetrieveAvailableNodes->objectName().isEmpty())
            ONBRetrieveAvailableNodes->setObjectName(QString::fromUtf8("ONBRetrieveAvailableNodes"));
        ONBRetrieveAvailableNodes->resize(787, 421);
        gridLayout_3 = new QGridLayout(ONBRetrieveAvailableNodes);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(6, 6, 6, 6);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelIpSearch = new QLabel(ONBRetrieveAvailableNodes);
        labelIpSearch->setObjectName(QString::fromUtf8("labelIpSearch"));

        gridLayout->addWidget(labelIpSearch, 0, 0, 1, 1);

        lineEditIpStart = new IPLineEdit(ONBRetrieveAvailableNodes);
        lineEditIpStart->setObjectName(QString::fromUtf8("lineEditIpStart"));

        gridLayout->addWidget(lineEditIpStart, 0, 1, 1, 1);

        labelSymbol = new QLabel(ONBRetrieveAvailableNodes);
        labelSymbol->setObjectName(QString::fromUtf8("labelSymbol"));

        gridLayout->addWidget(labelSymbol, 0, 2, 1, 1);

        lineEditIpEnd = new IPLineEdit(ONBRetrieveAvailableNodes);
        lineEditIpEnd->setObjectName(QString::fromUtf8("lineEditIpEnd"));

        gridLayout->addWidget(lineEditIpEnd, 0, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelNodeTotal = new QLabel(ONBRetrieveAvailableNodes);
        labelNodeTotal->setObjectName(QString::fromUtf8("labelNodeTotal"));
        labelNodeTotal->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(labelNodeTotal);

        labelNodeTotalDisp = new QLabel(ONBRetrieveAvailableNodes);
        labelNodeTotalDisp->setObjectName(QString::fromUtf8("labelNodeTotalDisp"));
        labelNodeTotalDisp->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(labelNodeTotalDisp);

        labelNodeIsConnected = new QLabel(ONBRetrieveAvailableNodes);
        labelNodeIsConnected->setObjectName(QString::fromUtf8("labelNodeIsConnected"));
        labelNodeIsConnected->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(labelNodeIsConnected);

        labelNodeIsConnectedDisp = new QLabel(ONBRetrieveAvailableNodes);
        labelNodeIsConnectedDisp->setObjectName(QString::fromUtf8("labelNodeIsConnectedDisp"));
        labelNodeIsConnectedDisp->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(labelNodeIsConnectedDisp);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        tableWidget = new QTableWidget(ONBRetrieveAvailableNodes);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_3->addWidget(tableWidget, 1, 0, 1, 1);

        progressBar = new QProgressBar(ONBRetrieveAvailableNodes);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        gridLayout_3->addWidget(progressBar, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonSearch = new QPushButton(ONBRetrieveAvailableNodes);
        pushButtonSearch->setObjectName(QString::fromUtf8("pushButtonSearch"));

        horizontalLayout_2->addWidget(pushButtonSearch);

        pushButtonOK = new QPushButton(ONBRetrieveAvailableNodes);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));

        horizontalLayout_2->addWidget(pushButtonOK);

        pushButtonReset = new QPushButton(ONBRetrieveAvailableNodes);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));

        horizontalLayout_2->addWidget(pushButtonReset);

        pushButtonCancel = new QPushButton(ONBRetrieveAvailableNodes);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout_2->addWidget(pushButtonCancel);


        gridLayout_3->addLayout(horizontalLayout_2, 3, 0, 1, 1);


        retranslateUi(ONBRetrieveAvailableNodes);

        QMetaObject::connectSlotsByName(ONBRetrieveAvailableNodes);
    } // setupUi

    void retranslateUi(QDialog *ONBRetrieveAvailableNodes)
    {
        ONBRetrieveAvailableNodes->setWindowTitle(QApplication::translate("ONBRetrieveAvailableNodes", "ONBRetrieveAvailableNodes", nullptr));
        labelIpSearch->setText(QApplication::translate("ONBRetrieveAvailableNodes", "IP\350\214\203\345\233\264", nullptr));
        labelSymbol->setText(QApplication::translate("ONBRetrieveAvailableNodes", "     ~      ", nullptr));
        labelNodeTotal->setText(QApplication::translate("ONBRetrieveAvailableNodes", "\350\212\202\347\202\271\346\200\273\346\225\260:", nullptr));
        labelNodeTotalDisp->setText(QApplication::translate("ONBRetrieveAvailableNodes", "0", nullptr));
        labelNodeIsConnected->setText(QApplication::translate("ONBRetrieveAvailableNodes", "\345\217\257\347\224\250\350\212\202\347\202\271:", nullptr));
        labelNodeIsConnectedDisp->setText(QApplication::translate("ONBRetrieveAvailableNodes", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ONBRetrieveAvailableNodes", "IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ONBRetrieveAvailableNodes", "\350\256\276\345\244\207\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ONBRetrieveAvailableNodes", "\345\217\257\351\223\276\346\216\245\347\212\266\346\200\201", nullptr));
        pushButtonSearch->setText(QApplication::translate("ONBRetrieveAvailableNodes", "\347\255\233\351\200\211", nullptr));
        pushButtonOK->setText(QApplication::translate("ONBRetrieveAvailableNodes", "\347\241\256\345\256\232", nullptr));
        pushButtonReset->setText(QApplication::translate("ONBRetrieveAvailableNodes", "\345\244\215\344\275\215", nullptr));
        pushButtonCancel->setText(QApplication::translate("ONBRetrieveAvailableNodes", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ONBRetrieveAvailableNodes: public Ui_ONBRetrieveAvailableNodes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNRETRIEVEAVAILABLENODES_H
