#-------------------------------------------------
#
# Project created by QtCreator 2018-01-08T16:51:45
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += console
CONFIG   -= app_bundle

include(../../../obnsoftwareroot.pri)

TEMPLATE = app
TARGET   = ExportSegyProgram
#DESTDIR  += $$OBN_RUN_PATH

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Algorithm
contains(QMAKE_HOST.os,Linux){
INCLUDEPATH += $$OBN_INCLUDE_PATH/Linux
}else{
INCLUDEPATH += $$OBN_INCLUDE_PATH/Windows
}

LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo -lAlgorithm

contains(QMAKE_HOST.os,Linux){
LIBS += -L$$OBN_RUN_PATH/Linux -lfftw3f
}else{
LIBS += -L$$OBN_RUN_PATH/Windows -lfftw3f-3
}


#LIBS  += -L$$GOBS_THIRDPARTY_LIB


INCLUDEPATH += $$GOBS_SRC/Algorithm \
               $$GOBS_THIRDPARTY/include \
               $$GOBS_SRC/Core

SOURCES += main.cpp \
        abstractsegyproducer.cpp \
        recvorientedsegy.cpp \
        shotorientedsegy.cpp \
        responseprocessorf.cpp

HEADERS += \
        abstractsegyproducer.h \
        recvorientedsegy.h \
        shotorientedsegy.h \
        responseprocessorf.h

win32-msvc* {
    QMAKE_CXXFLAGS *=  /wd"4100"
    contains (QMAKE_CXXFLAGS_WARN_ON, -w34100) : QMAKE_CXXFLAGS_WARN_ON -= -w34100
}
