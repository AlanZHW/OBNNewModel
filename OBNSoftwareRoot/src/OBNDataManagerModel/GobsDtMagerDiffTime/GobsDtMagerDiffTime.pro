#-------------------------------------------------
#
# Project created by QtCreator 2019-04-30T17:15:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = GobsDtMagerDiffTime
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

CONFIG += c++11

DEFINES += GOBSDTMAGERDIFFTIME_LIBRARY

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core


LIBS        += -L$$OBN_RUN_PATH  -lCore #-ltestmatlab -lFrftProcess

#INCLUDEPATH += $$MATLAB_PATH\include
#INCLUDEPATH += $$MATLAB_PATH\include\win64
#INCLUDEPATH += $$MATLAB_PATH\lib\win64\microsoft
#DEPENDPATH  += $$MATLAB_PATH\lib\win64\microsoft
#DEPENDPATH  += $$MATLAB_PATH\lib\win64

#LIBS += -L$$MATLAB_PATH\lib\win64\microsoft -lmclmcrrt
#LIBS += -L$$MATLAB_PATH\lib\win64\microsoft -lmclmcr
#LIBS += -L$$MATLAB_PATH\lib\win64\microsoft -lmclbase
#LIBS += -L$$MATLAB_PATH\lib\win64\microsoft -llibeng
#LIBS += -L$$MATLAB_PATH\lib\win64\microsoft -llibmat
#LIBS += -L$$MATLAB_PATH\lib\win64\microsoft -lmclcommain
#LIBS += -L$$MATLAB_PATH\lib\win64\microsoft -llibmx


SOURCES +=  gobsdtmagerdifftime.cpp \
            visitacufile.cpp \
            displayacudata.cpp \
            displayfrftdat.cpp

HEADERS  += gobsdtmagerdifftime.h \
            visitacufile.h \
            displayacudata.h \
            displayfrftdat.h \
            gobsdtmagerdifftime_global.h

FORMS    += gobsdtmagerdifftime.ui \
            displayacudata.ui \
            displayfrftdat.ui

win32-msvc* {
    QMAKE_CXXFLAGS *=  /wd"4100"
    contains (QMAKE_CXXFLAGS_WARN_ON, -w34100) : QMAKE_CXXFLAGS_WARN_ON -= -w34100
}
