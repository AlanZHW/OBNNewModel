#-------------------------------------------------
#
# Project created by QtCreator 2017-11-23T14:18:41
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = RNMBaseLib
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件


DEFINES += RNMBASELIB_LIBRARY

DEFINES += ZHW_DEBUG

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/QtFtp
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo

SOURCES += searchthread.cpp \
            rnitems.cpp \
            nodequery.cpp \
            rnmpublic.cpp \
            rnftpmanager.cpp \
            statusreport.cpp \
            ftpmanager.cpp \
            nodeftp.cpp

HEADERS += searchthread.h \
            rnitems.h \
            nodequery.h \
            rnmpublic.h \
            rnftpmanager.h \
            statusreport.h \
            rnmbaselib_global.h \
            ftpmanager.h \
            nodeftp.h

FORMS += \
        rnftpmanager.ui \
        statusreport.ui

LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo -lQtFtp
