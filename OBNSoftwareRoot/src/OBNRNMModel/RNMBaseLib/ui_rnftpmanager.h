/********************************************************************************
** Form generated from reading UI file 'rnftpmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RNFTPMANAGER_H
#define UI_RNFTPMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RNFtpManager
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *datapathEdit;
    QPushButton *brwserBtn;
    QLabel *label_2;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *timePeriodCbx;
    QFrame *timePeriodFrame;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_5;
    QTableView *tableView;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QLineEdit *TClineEdit;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QDateTimeEdit *dateTimeStart;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEnd;
    QLabel *label_5;
    QLineEdit *lineEditDisTime;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox;
    QPushButton *downloadBtn;
    QPushButton *clearMemBtn;
    QPushButton *setSampleFreqBtn;
    QPushButton *stopCurrentBtn;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *closeBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *clearBtn;
    QSpacerItem *horizontalSpacer_7;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *RNFtpManager)
    {
        if (RNFtpManager->objectName().isEmpty())
            RNFtpManager->setObjectName(QStringLiteral("RNFtpManager"));
        RNFtpManager->resize(1055, 751);
        gridLayout_2 = new QGridLayout(RNFtpManager);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(RNFtpManager);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_7 = new QHBoxLayout(widget);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        datapathEdit = new QLineEdit(widget);
        datapathEdit->setObjectName(QStringLiteral("datapathEdit"));

        horizontalLayout_2->addWidget(datapathEdit);

        brwserBtn = new QPushButton(widget);
        brwserBtn->setObjectName(QStringLiteral("brwserBtn"));
        brwserBtn->setMaximumSize(QSize(36, 16777215));

        horizontalLayout_2->addWidget(brwserBtn);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(20);

        horizontalLayout_2->addWidget(spinBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        timePeriodCbx = new QCheckBox(widget);
        timePeriodCbx->setObjectName(QStringLiteral("timePeriodCbx"));

        horizontalLayout_3->addWidget(timePeriodCbx);

        timePeriodFrame = new QFrame(widget);
        timePeriodFrame->setObjectName(QStringLiteral("timePeriodFrame"));
        timePeriodFrame->setMinimumSize(QSize(20, 0));
        timePeriodFrame->setFrameShape(QFrame::StyledPanel);
        timePeriodFrame->setFrameShadow(QFrame::Raised);

        horizontalLayout_3->addWidget(timePeriodFrame);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_3);

        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_4->addWidget(checkBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tableView = new QTableView(widget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout_2->addWidget(tableView);


        horizontalLayout_6->addLayout(verticalLayout_2);

        frame = new QFrame(widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(260, 16777215));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(9);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 10);
        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setWordWrap(true);

        verticalLayout_3->addWidget(label_7);

        TClineEdit = new QLineEdit(frame);
        TClineEdit->setObjectName(QStringLiteral("TClineEdit"));

        verticalLayout_3->addWidget(TClineEdit);


        verticalLayout->addLayout(verticalLayout_3);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        dateTimeStart = new QDateTimeEdit(groupBox_2);
        dateTimeStart->setObjectName(QStringLiteral("dateTimeStart"));

        gridLayout->addWidget(dateTimeStart, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        dateTimeEnd = new QDateTimeEdit(groupBox_2);
        dateTimeEnd->setObjectName(QStringLiteral("dateTimeEnd"));

        gridLayout->addWidget(dateTimeEnd, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        lineEditDisTime = new QLineEdit(groupBox_2);
        lineEditDisTime->setObjectName(QStringLiteral("lineEditDisTime"));

        gridLayout->addWidget(lineEditDisTime, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_5 = new QHBoxLayout(groupBox);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_5->addWidget(comboBox);


        verticalLayout->addWidget(groupBox);

        downloadBtn = new QPushButton(frame);
        downloadBtn->setObjectName(QStringLiteral("downloadBtn"));

        verticalLayout->addWidget(downloadBtn);

        clearMemBtn = new QPushButton(frame);
        clearMemBtn->setObjectName(QStringLiteral("clearMemBtn"));

        verticalLayout->addWidget(clearMemBtn);

        setSampleFreqBtn = new QPushButton(frame);
        setSampleFreqBtn->setObjectName(QStringLiteral("setSampleFreqBtn"));

        verticalLayout->addWidget(setSampleFreqBtn);

        stopCurrentBtn = new QPushButton(frame);
        stopCurrentBtn->setObjectName(QStringLiteral("stopCurrentBtn"));

        verticalLayout->addWidget(stopCurrentBtn);


        horizontalLayout_6->addWidget(frame);


        verticalLayout_4->addLayout(horizontalLayout_6);

        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        refreshBtn = new QPushButton(widget);
        refreshBtn->setObjectName(QStringLiteral("refreshBtn"));

        horizontalLayout->addWidget(refreshBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        closeBtn = new QPushButton(widget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));

        horizontalLayout->addWidget(closeBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        clearBtn = new QPushButton(widget);
        clearBtn->setObjectName(QStringLiteral("clearBtn"));

        horizontalLayout->addWidget(clearBtn);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout_4->addLayout(horizontalLayout);


        horizontalLayout_7->addLayout(verticalLayout_4);

        splitter->addWidget(widget);
        textBrowser = new QTextBrowser(splitter);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setEnabled(true);
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        splitter->addWidget(textBrowser);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        splitter->raise();
        frame->raise();
        frame->raise();

        retranslateUi(RNFtpManager);

        QMetaObject::connectSlotsByName(RNFtpManager);
    } // setupUi

    void retranslateUi(QDialog *RNFtpManager)
    {
        RNFtpManager->setWindowTitle(QApplication::translate("RNFtpManager", "Dialog", 0));
        label->setText(QApplication::translate("RNFtpManager", "Data Path:", 0));
        brwserBtn->setText(QApplication::translate("RNFtpManager", "...", 0));
        label_2->setText(QApplication::translate("RNFtpManager", "Max Work Together Nodes:", 0));
        timePeriodCbx->setText(QApplication::translate("RNFtpManager", "Download By Time Period", 0));
        checkBox->setText(QApplication::translate("RNFtpManager", "SelectAll/Clear", 0));
        label_7->setText(QApplication::translate("RNFtpManager", "\346\231\266\346\214\257\344\270\273\351\242\221TC\357\274\232", 0));
        TClineEdit->setText(QApplication::translate("RNFtpManager", "3145728000", 0));
        groupBox_2->setTitle(QApplication::translate("RNFtpManager", "\351\207\207\351\233\206\346\227\266\351\227\264\344\277\241\346\201\257", 0));
        label_3->setText(QApplication::translate("RNFtpManager", "\345\274\200\345\247\213\351\207\207\346\240\267\346\227\266\351\227\264", 0));
        label_4->setText(QApplication::translate("RNFtpManager", "\347\273\223\346\235\237\351\207\207\346\240\267\346\227\266\351\227\264", 0));
        label_5->setText(QApplication::translate("RNFtpManager", "\346\227\266\346\240\207\344\277\241\346\201\257\351\207\207\346\240\267\351\227\264\351\232\224(h)", 0));
        groupBox->setTitle(QApplication::translate("RNFtpManager", "Sampe Frequncy:", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("RNFtpManager", "1000", 0)
         << QApplication::translate("RNFtpManager", "500", 0)
         << QApplication::translate("RNFtpManager", "250", 0)
        );
        downloadBtn->setText(QApplication::translate("RNFtpManager", "&DownLoad\n"
"Files", 0));
        clearMemBtn->setText(QApplication::translate("RNFtpManager", "&Clear \n"
"Memory", 0));
        setSampleFreqBtn->setText(QApplication::translate("RNFtpManager", "&Set\n"
"Sample Frequency", 0));
        stopCurrentBtn->setText(QApplication::translate("RNFtpManager", "&Stop \n"
"Current Work", 0));
        refreshBtn->setText(QApplication::translate("RNFtpManager", "&Refresh", 0));
        closeBtn->setText(QApplication::translate("RNFtpManager", "&Close", 0));
        clearBtn->setText(QApplication::translate("RNFtpManager", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class RNFtpManager: public Ui_RNFtpManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RNFTPMANAGER_H
