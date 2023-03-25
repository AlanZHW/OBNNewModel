QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include(../../../obnsoftwareroot.pri)


TARGET = OBNJobMonitorPrograme
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件
DEFINES += OBNJOBMONITORPROGRAME_LIBRARY

INCLUDEPATH += $$OBN_INCLUDE_PATH

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    jobmanager.cpp \
    main.cpp \
    obnjobmonitorprograme.cpp

HEADERS += \
    jobmanager.h \
    obnjobmonitorprograme.h \
    obnjobmonitorprograme_global.h

FORMS += \
    obnjobmonitorprograme.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += cn.ts \
                en.ts

RESOURCES += \
    translate.qrc

