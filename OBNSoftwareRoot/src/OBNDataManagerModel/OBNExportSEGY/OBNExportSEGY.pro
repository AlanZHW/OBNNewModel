QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

CONFIG += c++11

TARGET   = OBNExportSEGY
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

DEFINES += OBNEXPORTSEGY_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    exportsegydlg.cpp \
    shotlinedlg.cpp

HEADERS += \
    exportsegydlg.h \
    obnexportsegy_global.h \
    shotlinedlg.h

FORMS += \
    exportsegydlg.ui

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo

LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
