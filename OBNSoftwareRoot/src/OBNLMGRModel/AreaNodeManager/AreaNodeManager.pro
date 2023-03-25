#-------------------------------------------------
#
# Project created by QtCreator 2017-11-22T16:32:00
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

TARGET = AreaNodeManager
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

DEFINES += AREANODEMANAGER_LIBRARY

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo

LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo

SOURCES +=  main.cpp\
            assignnodedlg.cpp \
            deploysystem.cpp \
            rndeployments.cpp \
            lmgrpublic.cpp

HEADERS  += assignnodedlg.h \
            deploysystem.h \
            rndeployments.h \
            lmgrpublic.h \
            areanodemanager_global.h

FORMS    += assignnodedlg.ui \
             deploysystem.ui \
             rndeployments.ui
