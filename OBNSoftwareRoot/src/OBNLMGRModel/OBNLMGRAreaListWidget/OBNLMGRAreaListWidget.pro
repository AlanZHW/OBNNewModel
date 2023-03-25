QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
include(../../../obnsoftwareroot.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = OBNLMGRAreaListWidget
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件
DEFINES += OBNLMGRAREALISTWIDGET_LIBRARY
SOURCES += \
    main.cpp \
    obnlmgrarealistwidget.cpp

HEADERS += \
    obnlmgrarealistwidget.h \
    obnlmgrarealistwidget_global.h

FORMS += \
    obnlmgrarealistwidget.ui

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core

LIBS += -L$$OBN_RUN_PATH -lCore

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
