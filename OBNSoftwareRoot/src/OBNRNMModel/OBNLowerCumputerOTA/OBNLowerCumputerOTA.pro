# ====== 下位机系统升级

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../../obnsoftwareroot.pri)

CONFIG += c++11


TARGET   = obnlowercomputerota
#TEMPLATE = app
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件
DEFINES  += OBNOTA_LIBRARY

SOURCES += \
    main.cpp    \
    obnlowercumputerota.cpp \
    obnotanode.cpp \
    obnotanodeftp.cpp

HEADERS += \
    obnlowercumputerota.h \
    obnlowercumputerota_global.h \
    obnotanode.h \
    obnotanodeftp.h

FORMS += \
    obnlowercumputerota.ui

INCLUDEPATH += $$OBN_ROOT_PATH/include
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/QtFtp
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/OBNRetrieveAvailableNodes
LIBS        += -L$$OBN_RUN_PATH -lQtFtp -lobnretrieveavailablenodes

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#RESOURCES += \
#    qss.qrc
