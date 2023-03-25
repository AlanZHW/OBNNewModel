# ====== 根据IP地址的范围筛选可用的IP地址列表

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include(../../../obnsoftwareroot.pri)

TEMPLATE = lib
TARGET   = obnretrieveavailablenodes
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件
DEFINES += OBNRETRIEVEAVAILABLENODES_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$OBN_ROOT_PATH/include

SOURCES += \
    iplineedit.cpp \
    ippartlineedit.cpp \
    obnretrieveavailablenodes.cpp \
    obnsearchhoststhread.cpp

HEADERS += \
    iplineedit.h \
    ippartlineedit.h \
    obnretrieveavailablenodes.h \
    obnretrieveavailablenodes_global.h \
    obnsearchhoststhread.h

FORMS += \
    obnretrieveavailablenodes.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
