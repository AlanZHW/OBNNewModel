#-------------------------------------------------
#
# Project created by QtCreator 2018-01-08T16:51:45
#
#-------------------------------------------------

QT       += core  sql
QT       -= gui

TARGET = ExportSegyProgram
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
TARGET   = ExportSegyProgram
DESTDIR  += $$OBN_RUN_PATH

include(../../obnsoftwareroot.pri)

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/OBNOtherLibraries/GPublicSo
INCLUDEPATH += $$OBN_ROOT_PATH/OBNOtherLibraries/Algorithm

LIBS  += -L$$OBN_RUN_PATH -lCore -lGPublicSo -lAlgorithm #-lFrftProcess

#LIBS  += -L$$GOBS_THIRDPARTY_LIB -llibfftw3f-3


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
