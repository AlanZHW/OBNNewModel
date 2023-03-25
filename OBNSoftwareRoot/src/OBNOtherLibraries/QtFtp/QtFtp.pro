#-------------------------------------------------
#
# Project created by QtCreator 2017-12-04T13:51:47
#
#-------------------------------------------------

QT       += core network
QT       -= gui

include(../../../obnsoftwareroot.pri)

TEMPLATE = lib
TARGET   = QtFtp
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

DEFINES += QTFTP_LIBRARY

SOURCES += qftp.cpp \
           qurlinfo.cpp

HEADERS += qftp.h\
           qurlinfo.h \
           qtftp_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
