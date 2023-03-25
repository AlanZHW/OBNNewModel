#-------------------------------------------------
#
# Project created by QtCreator 2017-11-07T15:10:09
#
#-------------------------------------------------

QT       += core gui network #webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = RNManager
TEMPLATE = lib
#TEMPLATE = app
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件
DEFINES += RNMANAGER_LIBRARY

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += ../RNMBaseLib
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/QtFtp
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/AppGlobal

LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo -lRNMBaseLib -lQtFtp -lAppGlobal

DEFINES += ZHW_DEBUG

INCLUDEPATH +=../RNMBaseLib \

SOURCES += \
        main.cpp\
        rnmanager.cpp \
        rnmgrunit.cpp\
        rnmsidebar.cpp \
        rnmgraphview.cpp


HEADERS  += \
        rnmanager.h \
        rnmanager_global.h \
        rnmgrunit.h \
        rnmsidebar.h \
        rnmgraphview.h

FORMS    += rnmanager.ui \
            rnmsidebar.ui

#DEFINES += ALGORITHM_LIBRARY ADD_   HAVE_LAPACK_CONFIG_H  LAPACK_COMPLEX_STRUCTURE

TRANSLATIONS += rnmanager_cn.ts \
                rnmanager_en.ts
