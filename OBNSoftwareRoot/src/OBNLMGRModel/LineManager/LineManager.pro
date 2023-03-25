#-------------------------------------------------
#
# Project created by QtCreator 2017-11-07T15:08:28
#
#-------------------------------------------------

QT       += core gui network sql #webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = LineManager
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件
DEFINES += LINEMANAGER_LIBRARY



INCLUDEPATH += ../AreaNodeManager
INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo

SOURCES += main.cpp\
           linemanager.cpp \
           lmgrunit.cpp \
           lmgrareaview.cpp \
           stationitem.cpp

HEADERS  += linemanager.h \
            linemanager_global.h \
            lmgrunit.h \
            lmgrareaview.h \
            stationitem.h

FORMS    += linemanager.ui

LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo -lAreaNodeManager

RESOURCES += \
    image.qrc
