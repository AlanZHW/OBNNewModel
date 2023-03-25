QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = AppGlobal
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件
DEFINES += APPGLOBAL_LIBRARY
CONFIG += console c++11

SOURCES += \
        appglobal.cpp \
        main.cpp

HEADERS += \
    appglobal.h \
    appglobal_global.h

INCLUDEPATH += $$OBN_INCLUDE_PATH
