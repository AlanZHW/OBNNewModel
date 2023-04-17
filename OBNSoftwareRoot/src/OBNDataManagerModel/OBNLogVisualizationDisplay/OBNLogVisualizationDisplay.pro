# ====== LOG曲线显示

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

CONFIG += c++11

TARGET = OBNLogVisualizationDisplay
#TEMPLATE = app
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件
DEFINES += OBNLOGVISUAILZATIONDISP_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    obnlogvisuailzationchart.cpp \
    obnlogvisuailzationdisplay.cpp \
    obnreadloghread.cpp \
    obnreadloginformprogress.cpp

HEADERS += \
    obnlogvisuailzationchart.h \
    obnlogvisuailzationdisp_global.h \
    obnlogvisuailzationdisplay.h \
    obnreadloghread.h \
    obnreadloginformprogress.h

FORMS += \
    obnlogvisuailzationdisplay.ui \
    obnreadloginformprogress.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
