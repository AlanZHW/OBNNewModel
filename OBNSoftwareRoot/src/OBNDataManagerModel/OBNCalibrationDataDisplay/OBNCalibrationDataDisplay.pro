QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

CONFIG += c++11

TARGET = OBNCalirationDataDisplay
#TEMPLATE = app
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$OBN_INCLUDE_PATH

DEFINES += OBNCALIBRATIONDATADISPLAY_LIBRARY

SOURCES += \
    main.cpp \
    obncalibrationdatadisplay.cpp \
    obncalibratondatachart.cpp \
    readcalibationdata.cpp

HEADERS += \
    obncalibrationdatadisplay.h \
    obncalibrationdatadisplay_global.h \
    obncalibrationdatapublic.h \
    obncalibratondatachart.h \
    readcalibationdata.h

FORMS += \
    obncalibrationdatadisplay.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
