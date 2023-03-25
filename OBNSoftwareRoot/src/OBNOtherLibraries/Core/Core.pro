#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T15:16:34
#
#-------------------------------------------------

QT      += core gui #webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = Core
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG += plugin

DEFINES += CORE_LIBRARY

INCLUDEPATH += $$OBN_INCLUDE_PATH

SOURCES += \
    core.cpp \
    spsfiles.cpp \
    segy.cpp \
    assistant.cpp \
    projectarea.cpp

HEADERS += \
    core.h \
    spsfiles.h \
    segy.h \
    assistant.h \
    core_global.h \
    projectarea.h

win32{
LIBS += -lwsock32
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
