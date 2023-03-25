#-------------------------------------------------
#
# Project created by QtCreator 2018-01-08T09:56:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = QCPlotter
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

DEFINES += QCPLOTTER_LIBRARY

INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Algorithm

LIBS      += -L$$OBN_RUN_PATH -lGPublicSo -lAlgorithm -lCore

SOURCES += main.cpp\
        qcplotter.cpp \
    qcgraphbase.cpp \
    graphbase_2d.cpp \
    qcgraphpublic.cpp

HEADERS  += qcplotter.h \
    qcgraphbase.h \
    graphbase_2d.h \
    qcgraphpublic.h \
    qcplotter_global.h

FORMS    += qcplotter.ui \
    traceheaddlg.ui
