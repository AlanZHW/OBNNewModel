
# ------ OBN项目实时波形显示功能

QT       += core gui charts network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include(../../../obnsoftwareroot.pri)

TEMPLATE = lib
#TEMPLATE = app
TARGET   = obnrealtimewaveformdisp
DESTDIR  += $$OBN_RUN_PATH
#CONFIG   += plugin  #描述生成单一库文件
DEFINES += OBNREALTIMEWAVEFORMDISPLAY_LIBRARY

SOURCES += \
    main.cpp \
    obnchart.cpp \
    obnrealtimewaveformdispgroup.cpp \
    obnrealtimewaveroot.cpp \
    obnwaveformtcpsocket.cpp

HEADERS += \
    obnchart.h \
    obnrealtimewaveformdispgroup.h \
    obnrealtimewaveformdisplay_global.h \
    obnrealtimewaveformpublic.h \
    obnrealtimewaveroot.h \
    obnwaveformtcpsocket.h

FORMS += \
    obnrealtimewaveformdispgroup.ui \
    obnrealtimewaveroot.ui

INCLUDEPATH += $$OBN_ROOT_PATH/include
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/OBNRetrieveAvailableNodes

LIBS        += -L$$OBN_RUN_PATH -lobnretrieveavailablenodes

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
