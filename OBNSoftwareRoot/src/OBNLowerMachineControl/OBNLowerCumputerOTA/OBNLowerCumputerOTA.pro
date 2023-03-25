# ====== 下位机系统升级

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../obnsoftwareroot.pri)

CONFIG += c++11

TEMPLATE = lib
TARGET   = obnlowercomputerota
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

INCLUDEPATH += $$OBN_ROOT_PATH/include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    obnlowercumputerota.cpp

HEADERS += \
    obnlowercumputerota.h

FORMS += \
    obnlowercumputerota.ui

INCLUDEPATH += $$OBN_ROOT_PATH/OBNOtherLibraries/QtFtp
LIBS        += -L$$OBN_RUN_PATH -lQtFtp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
