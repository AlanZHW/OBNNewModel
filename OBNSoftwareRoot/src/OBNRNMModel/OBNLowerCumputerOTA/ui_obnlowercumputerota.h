/********************************************************************************
** Form generated from reading UI file 'obnlowercumputerota.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNLOWERCUMPUTEROTA_H
#define UI_OBNLOWERCUMPUTEROTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OBNLowerCumputerOTA
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBoxOTA;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBoxOption;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonGetAvailableNodes;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelInputfName;
    QLineEdit *lineEditInputfName;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonBrowse;
    QPushButton *pushButtonStart;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidgetOTA;
    QTableWidget *tableWidgetCfgInform;

    void setupUi(QDialog *OBNLowerCumputerOTA)
    {
        if (OBNLowerCumputerOTA->objectName().isEmpty())
            OBNLowerCumputerOTA->setObjectName(QString::fromUtf8("OBNLowerCumputerOTA"));
        OBNLowerCumputerOTA->resize(649, 520);
        gridLayout_3 = new QGridLayout(OBNLowerCumputerOTA);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBoxOTA = new QGroupBox(OBNLowerCumputerOTA);
        groupBoxOTA->setObjectName(QString::fromUtf8("groupBoxOTA"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxOTA->sizePolicy().hasHeightForWidth());
        groupBoxOTA->setSizePolicy(sizePolicy);
        groupBoxOTA->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(groupBoxOTA);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        comboBoxOption = new QComboBox(groupBoxOTA);
        comboBoxOption->addItem(QString());
        comboBoxOption->addItem(QString());
        comboBoxOption->setObjectName(QString::fromUtf8("comboBoxOption"));

        horizontalLayout->addWidget(comboBoxOption);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonGetAvailableNodes = new QPushButton(groupBoxOTA);
        pushButtonGetAvailableNodes->setObjectName(QString::fromUtf8("pushButtonGetAvailableNodes"));

        horizontalLayout->addWidget(pushButtonGetAvailableNodes);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelInputfName = new QLabel(groupBoxOTA);
        labelInputfName->setObjectName(QString::fromUtf8("labelInputfName"));

        horizontalLayout_2->addWidget(labelInputfName);

        lineEditInputfName = new QLineEdit(groupBoxOTA);
        lineEditInputfName->setObjectName(QString::fromUtf8("lineEditInputfName"));

        horizontalLayout_2->addWidget(lineEditInputfName);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButtonBrowse = new QPushButton(groupBoxOTA);
        pushButtonBrowse->setObjectName(QString::fromUtf8("pushButtonBrowse"));

        verticalLayout->addWidget(pushButtonBrowse);

        pushButtonStart = new QPushButton(groupBoxOTA);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));

        verticalLayout->addWidget(pushButtonStart);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBoxOTA, 0, 0, 1, 1);

        frame = new QFrame(OBNLowerCumputerOTA);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidgetOTA = new QTableWidget(frame);
        tableWidgetOTA->setObjectName(QString::fromUtf8("tableWidgetOTA"));

        gridLayout_2->addWidget(tableWidgetOTA, 0, 0, 1, 1);

        tableWidgetCfgInform = new QTableWidget(frame);
        tableWidgetCfgInform->setObjectName(QString::fromUtf8("tableWidgetCfgInform"));

        gridLayout_2->addWidget(tableWidgetCfgInform, 0, 1, 1, 1);


        gridLayout_3->addWidget(frame, 1, 0, 1, 1);


        retranslateUi(OBNLowerCumputerOTA);

        QMetaObject::connectSlotsByName(OBNLowerCumputerOTA);
    } // setupUi

    void retranslateUi(QDialog *OBNLowerCumputerOTA)
    {
        OBNLowerCumputerOTA->setWindowTitle(QApplication::translate("OBNLowerCumputerOTA", "OBNLowerCumputerOTA", nullptr));
        groupBoxOTA->setTitle(QApplication::translate("OBNLowerCumputerOTA", "\351\205\215\347\275\256\345\215\207\347\272\247\344\277\241\346\201\257", nullptr));
        comboBoxOption->setItemText(0, QApplication::translate("OBNLowerCumputerOTA", "\345\215\207\347\272\247\347\263\273\347\273\237", nullptr));
        comboBoxOption->setItemText(1, QApplication::translate("OBNLowerCumputerOTA", "\345\215\207\347\272\247\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));

        pushButtonGetAvailableNodes->setText(QApplication::translate("OBNLowerCumputerOTA", "\347\255\233\351\200\211\345\217\257\347\224\250\350\212\202\347\202\271", nullptr));
        labelInputfName->setText(QApplication::translate("OBNLowerCumputerOTA", "\346\226\207\344\273\266\345\220\215", nullptr));
        pushButtonBrowse->setText(QApplication::translate("OBNLowerCumputerOTA", "\346\265\217\350\247\210", nullptr));
        pushButtonStart->setText(QApplication::translate("OBNLowerCumputerOTA", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNLowerCumputerOTA: public Ui_OBNLowerCumputerOTA {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNLOWERCUMPUTEROTA_H
