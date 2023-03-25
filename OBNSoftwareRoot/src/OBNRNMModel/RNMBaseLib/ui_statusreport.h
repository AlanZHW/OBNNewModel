/********************************************************************************
** Form generated from reading UI file 'statusreport.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSREPORT_H
#define UI_STATUSREPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StatusReportDlg
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *exportSheetBtn;
    QPushButton *pushButton;

    void setupUi(QDialog *StatusReportDlg)
    {
        if (StatusReportDlg->objectName().isEmpty())
            StatusReportDlg->setObjectName(QStringLiteral("StatusReportDlg"));
        StatusReportDlg->resize(970, 462);
        horizontalLayout_2 = new QHBoxLayout(StatusReportDlg);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(StatusReportDlg);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->verticalHeader()->setCascadingSectionResizes(true);

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        exportSheetBtn = new QPushButton(StatusReportDlg);
        exportSheetBtn->setObjectName(QStringLiteral("exportSheetBtn"));

        horizontalLayout->addWidget(exportSheetBtn);

        pushButton = new QPushButton(StatusReportDlg);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(StatusReportDlg);

        QMetaObject::connectSlotsByName(StatusReportDlg);
    } // setupUi

    void retranslateUi(QDialog *StatusReportDlg)
    {
        StatusReportDlg->setWindowTitle(QApplication::translate("StatusReportDlg", "Dialog", 0));
        exportSheetBtn->setText(QApplication::translate("StatusReportDlg", "&Export Sheet...", 0));
        pushButton->setText(QApplication::translate("StatusReportDlg", "&Close", 0));
    } // retranslateUi

};

namespace Ui {
    class StatusReportDlg: public Ui_StatusReportDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSREPORT_H
