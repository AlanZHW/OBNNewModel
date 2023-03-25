#-------------------------------------------------
#
# Project created by QtCreator 2019-02-23T11:32:21
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = GPositionSystem
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

CONFIG += c++11

INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Chart
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Algorithm

LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo -lChart -lAlgorithm

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += GPOSTIONSYTEM_LIBRARY
#DEFINES += ALGORITHM_LIBRARY ADD_   HAVE_LAPACK_CONFIG_H  LAPACK_COMPLEX_STRUCTURE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#        main.cpp\
        gpositionsystem.cpp \
        gserialport.cpp \
        gpspublic.cpp \
        datamanager.cpp \
        deckunit.cpp \
        positionchart.cpp \
        postioncontrols.cpp \
        axis.cpp \
        systemdisplay.cpp

HEADERS  += \
        gpositionsystem.h \
        gserialport.h \
        gpositionsystem_global.h \
        gpspublic.h \
        datamanager.h \
        deckunit.h \
        positionchart.h \
        postioncontrols.h \
        axis.h \
        systemdisplay.h

FORMS    += \
        gpositionsystem.ui \
        gserialport.ui \
        deckunit.ui \
        systemdisplay.ui
