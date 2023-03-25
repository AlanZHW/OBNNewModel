
# ======  OBN软件欢使用欢迎界面

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include(../../obnsoftwareroot.pri)

TEMPLATE = lib
TARGET   = obnWelcomeToTheInterface
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

DEFINES += OBNWELCOMETOTHEINTERFACE_LIBRARY

SOURCES += \
    main.cpp \
    obncreateprojectinterface.cpp \
    obndeleteprojectinterface.cpp \
    obneditporjectinterface.cpp \
    obnwelcometotheinterface.cpp

HEADERS += \
    obncreateprojectinterface.h \
    obndeleteprojectinterface.h \
    obneditporjectinterface.h \
    obnwelcometotheinterface.h \
    obnwelcometotheinterface_global.h

FORMS += \
    obncreateprojectinterface.ui \
    obndeleteprojectinterface.ui \
    obneditporjectinterface.ui \
    obnwelcometotheinterface.ui

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/AppGlobal

LIBS += -L$$OBN_RUN_PATH -lAppGlobal

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc \
    translate.qrc

TRANSLATIONS += cn.ts \
                en.ts
