/********************************************************************************
** Form generated from reading UI file 'obnwelcometotheinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBNWELCOMETOTHEINTERFACE_H
#define UI_OBNWELCOMETOTHEINTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OBNWelcomeToTheInterface
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QFrame *frameWelcomeImage;
    QGridLayout *gridLayout_5;
    QTextBrowser *textBrowser;
    QFrame *frameButtonGroup;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *labelProject;
    QLabel *labelLanguage;
    QComboBox *comboBoxProject;
    QComboBox *comboBoxLanguage;
    QPushButton *buttonEnterTheSystem;

    void setupUi(QWidget *OBNWelcomeToTheInterface)
    {
        if (OBNWelcomeToTheInterface->objectName().isEmpty())
            OBNWelcomeToTheInterface->setObjectName(QString::fromUtf8("OBNWelcomeToTheInterface"));
        OBNWelcomeToTheInterface->resize(1000, 643);
        OBNWelcomeToTheInterface->setMinimumSize(QSize(1000, 643));
        OBNWelcomeToTheInterface->setMaximumSize(QSize(800, 643));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/bootImage/img/tubiao.png"), QSize(), QIcon::Normal, QIcon::Off);
        OBNWelcomeToTheInterface->setWindowIcon(icon);
        OBNWelcomeToTheInterface->setWindowOpacity(1.000000000000000);
        gridLayout_4 = new QGridLayout(OBNWelcomeToTheInterface);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frameWelcomeImage = new QFrame(OBNWelcomeToTheInterface);
        frameWelcomeImage->setObjectName(QString::fromUtf8("frameWelcomeImage"));
        frameWelcomeImage->setStyleSheet(QString::fromUtf8(""));
        frameWelcomeImage->setFrameShape(QFrame::StyledPanel);
        frameWelcomeImage->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frameWelcomeImage);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(frameWelcomeImage);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setStyleSheet(QString::fromUtf8("/***\n"
"QTextEdit#textBrowser{\n"
"	background-color:transparent;\n"
"}***/"));

        gridLayout_5->addWidget(textBrowser, 0, 0, 1, 1);


        gridLayout_3->addWidget(frameWelcomeImage, 0, 0, 1, 1);

        frameButtonGroup = new QFrame(OBNWelcomeToTheInterface);
        frameButtonGroup->setObjectName(QString::fromUtf8("frameButtonGroup"));
        frameButtonGroup->setMinimumSize(QSize(0, 0));
        frameButtonGroup->setMaximumSize(QSize(16777215, 102));
        frameButtonGroup->setFrameShape(QFrame::StyledPanel);
        frameButtonGroup->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frameButtonGroup);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelProject = new QLabel(frameButtonGroup);
        labelProject->setObjectName(QString::fromUtf8("labelProject"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelProject->sizePolicy().hasHeightForWidth());
        labelProject->setSizePolicy(sizePolicy);

        gridLayout->addWidget(labelProject, 0, 0, 1, 1);

        labelLanguage = new QLabel(frameButtonGroup);
        labelLanguage->setObjectName(QString::fromUtf8("labelLanguage"));
        sizePolicy.setHeightForWidth(labelLanguage->sizePolicy().hasHeightForWidth());
        labelLanguage->setSizePolicy(sizePolicy);

        gridLayout->addWidget(labelLanguage, 1, 0, 1, 1);

        comboBoxProject = new QComboBox(frameButtonGroup);
        comboBoxProject->setObjectName(QString::fromUtf8("comboBoxProject"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxProject->sizePolicy().hasHeightForWidth());
        comboBoxProject->setSizePolicy(sizePolicy1);
        comboBoxProject->setMaximumSize(QSize(16777215, 16777215));
        comboBoxProject->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(comboBoxProject, 0, 1, 1, 1);

        comboBoxLanguage = new QComboBox(frameButtonGroup);
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->setObjectName(QString::fromUtf8("comboBoxLanguage"));
        sizePolicy1.setHeightForWidth(comboBoxLanguage->sizePolicy().hasHeightForWidth());
        comboBoxLanguage->setSizePolicy(sizePolicy1);
        comboBoxLanguage->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(comboBoxLanguage, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        buttonEnterTheSystem = new QPushButton(frameButtonGroup);
        buttonEnterTheSystem->setObjectName(QString::fromUtf8("buttonEnterTheSystem"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonEnterTheSystem->sizePolicy().hasHeightForWidth());
        buttonEnterTheSystem->setSizePolicy(sizePolicy2);
        buttonEnterTheSystem->setMinimumSize(QSize(100, 100));
        buttonEnterTheSystem->setMaximumSize(QSize(100, 100));
        buttonEnterTheSystem->setStyleSheet(QString::fromUtf8("QPushButton#buttonEnterTheSystem{\n"
"	background-color:\"#1E90FF\";\n"
"}"));

        gridLayout_2->addWidget(buttonEnterTheSystem, 0, 1, 1, 1);


        gridLayout_3->addWidget(frameButtonGroup, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        retranslateUi(OBNWelcomeToTheInterface);

        QMetaObject::connectSlotsByName(OBNWelcomeToTheInterface);
    } // setupUi

    void retranslateUi(QWidget *OBNWelcomeToTheInterface)
    {
        OBNWelcomeToTheInterface->setWindowTitle(QApplication::translate("OBNWelcomeToTheInterface", "\346\254\242\350\277\216\344\275\277\347\224\250OBN\350\275\257\344\273\266", nullptr));
        textBrowser->setHtml(QApplication::translate("OBNWelcomeToTheInterface", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">			<img src=\":/bootImage/img/logo.png\" /><br /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">		\345\205\250\345\233\275\345\205\215\350\264\271\346\234\215\345\212\241\347\203\255\347\272\277\357\274\232</span><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">800-807-2006 </span><span st"
                        "yle=\" font-size:9pt;\">\345\233\275\345\206\205\351\224\200\345\224\256\347\203\255\347\272\277\357\274\232</span><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">023-65291554</span><span style=\" font-size:9pt;\">\343\200\201</span><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">023-89863540</span><span style=\" font-size:9pt;\">\343\200\201</span><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">023-65291634</span><span style=\" font-size:9pt;\">\343\200\201</span><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">023-89863065</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">		\345\233\275\351\231\205\351\224\200\345\224\256\347\203\255\347\272\277\357\274\232</span><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">0086-023-65157761 </span><span style=\" font-size:9pt;\">\346\212"
                        "\200\346\234\257\346\234\215\345\212\241\347\203\255\347\272\277\357\274\232 </span><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">023-89863740</span><span style=\" font-size:9pt;\">\357\274\210\347\224\265\346\263\225\344\273\252\345\231\250\357\274\211</span><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">/ 023-89863764</span><span style=\" font-size:9pt;\">\357\274\210\346\265\213\344\272\225\344\273\252\345\231\250\357\274\211</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">		\344\274\240\347\234\237\357\274\232</span><span style=\" font-size:8pt;\">023-89863065</span><span style=\" font-family:'Microsoft YaHei','Segoe UI','system-ui','Roboto','Droid Sans','Helvetica Neue','sans-serif','Tahoma','Segoe UI Symbol','Myanmar Text'; font-size:8pt; color:#171a1d;\">023-65291634</span><span style=\" font-size:8pt;\">\357\274\210\346\265\267\346\264"
                        "\213\344\273\252\345\231\250\357\274\211</span><span style=\" font-family:'Liberation Serif','serif'; font-size:8pt;\">/ </span><span style=\" font-family:'Microsoft YaHei','Segoe UI','system-ui','Roboto','Droid Sans','Helvetica Neue','sans-serif','Tahoma','Segoe UI Symbol','Myanmar Text'; font-size:8pt; color:#171a1d;\">023-65291568</span><span style=\" font-size:9pt;\">\357\274\210\345\234\260\351\234\207\344\273\252\345\231\250\345\217\212\346\243\200\346\263\242\345\231\250\357\274\211</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt;\">		Email</span><span style=\" font-size:9pt;\">\357\274\232</span><a href=\"mailto:cdy@cgif.com.cn\"><span style=\" font-family:'Liberation Serif','serif'; font-size:9pt; font-weight:600; text-decoration: underline; color:#0000ff;\">cdy@cgif.com.cn </span></a></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; mar"
                        "gin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">		\345\234\260\345\235\200\357\274\232</span><span style=\" font-size:10pt; color:#171a1d;\">\351\207\215\345\272\206\345\270\202\351\253\230\346\226\260\345\214\272\346\233\276\345\256\266\351\225\207\345\205\264\345\276\267\350\267\257</span><span style=\" font-family:'Microsoft YaHei','Segoe UI','system-ui','Roboto','Droid Sans','Helvetica Neue','sans-serif','Tahoma','Segoe UI Symbol','Myanmar Text'; font-size:10pt; color:#171a1d;\">6</span><span style=\" font-size:10pt; color:#171a1d;\">\345\217\267</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#2e3436;\">		\344\275\277\347\224\250\350\275\257\344\273\266\344\271\213\345\211\215\357\274\214\344"
                        "\270\272\344\272\206\346\226\271\344\276\277\345\220\216\351\235\242\347\232\204\345\267\245\344\275\234\357\274\214\351\234\200\350\246\201\345\205\210\345\257\271\345\275\223\345\211\215\347\232\204\345\267\245\344\275\234\346\226\260\345\273\272\344\270\200\344\270\252\345\267\245\345\214\272\357\274\214\345\234\250\345\220\216\351\235\242\347\232\204\344\275\277\347\224\250\350\277\207\347\250\213\344\270\255\357\274\214</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#2e3436;\">		\346\211\200\346\234\211\346\223\215\344\275\234\344\272\247\347\224\237\347\232\204\346\225\260\346\215\256\351\203\275\345\260\206\345\255\230\345\202\250\345\234\250\345\275\223\345\211\215\345\267\245\347\250\213\344\270\255: </span><a href=\"NewProject\"><span style=\" font-size:9pt; text-decoration: underline; color:#000000;\">\346\226\260\345\273\272\345\267\245\345\214\272</span></a></p>\n"
"<p sty"
                        "le=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#000000;\">		\346\202\250\344\271\237\345\217\257\344\273\245\344\270\272\346\202\250\347\232\204\345\267\245\345\214\272\350\277\233\350\241\214\346\220\254\345\256\266\346\210\226\350\200\205\345\205\266\344\273\226\346\223\215\344\275\234\357\274\232 </span><a href=\"EditProject\"><span style=\" font-size:9pt; text-decoration: underline; color:#000000;\">\347\274\226\350\276\221\345\267\245\345\214\272</span></a></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#000000;\">		\345\275\223\346\202\250\347\232\204\345\267\245\347\250\213\345\267\262\347\273\217\347\273\223\346\235\237\346\210\226\350\200\205\344\270\215\351\234\200\350\246\201\346\227\266\357\274\214\346\202\250\345\217\257\344\273\245\345\260\206\345\205\266\350\277\233\350\241"
                        "\214\345\210\240\351\231\244\357\274\232</span><a href=\"DeleteProject\"><span style=\" font-size:9pt; text-decoration: underline; color:#000000;\">\345\210\240\351\231\244\345\267\245\345\214\272</span></a></p></body></html>", nullptr));
        labelProject->setText(QApplication::translate("OBNWelcomeToTheInterface", "\345\267\245\345\214\272\351\200\211\346\213\251", nullptr));
        labelLanguage->setText(QApplication::translate("OBNWelcomeToTheInterface", "\350\257\255\350\250\200\351\200\211\346\213\251 ", nullptr));
        comboBoxLanguage->setItemText(0, QApplication::translate("OBNWelcomeToTheInterface", "\347\256\200\344\275\223\344\270\255\346\226\207", nullptr));
        comboBoxLanguage->setItemText(1, QApplication::translate("OBNWelcomeToTheInterface", "English", nullptr));

        buttonEnterTheSystem->setText(QApplication::translate("OBNWelcomeToTheInterface", "\350\277\233\345\205\245\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBNWelcomeToTheInterface: public Ui_OBNWelcomeToTheInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBNWELCOMETOTHEINTERFACE_H
