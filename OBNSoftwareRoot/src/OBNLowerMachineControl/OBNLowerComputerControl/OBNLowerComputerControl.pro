QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../obnsoftwareroot.pri)

CONFIG += c++11

TEMPLATE = lib
TARGET   = obnlowercomputercontrol
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# ====== 增加链接头文件
INCLUDEPATH += $$OBN_ROOT_PATH/include
INCLUDEPATH += $$OBN_ROOT_PATH/OBNLowerMachineControl/OBNRetrieveAvailableNodes
INCLUDEPATH += $$OBN_ROOT_PATH/OBNLowerMachineControl/OBNLowerCumputerOTA
INCLUDEPATH += $$OBN_ROOT_PATH/OBNOtherLibraries/QtFtp

# ====== 增加链接库文件
LIBS += -L$$OBN_RUN_PATH -lQtFtp
LIBS += -L$$OBN_RUN_PATH -lobnretrieveavailablenodes -lobnlowercomputerota

SOURCES += \
    obnlistnodeinform.cpp \
#    obnlogvisualization.cpp \
#    obnlogvisualizationdraw.cpp \
#    obnlogvisualizationdrawonlyone.cpp \
#    obnlogvisualizationdsp.cpp \
#    obnlogvisualzationonlyoneroot.cpp \
    obnlowercomputercontrol.cpp \
    obnrealcontrolwidget.cpp

HEADERS += \
    LowerComputerControlPublic.h \
    obnlistnodeinform.h \
#    obnlogvisualization.h \
#    obnlogvisualizationdraw.h \
#    obnlogvisualizationdrawonlyone.h \
#    obnlogvisualizationdsp.h \
#    obnlogvisualzationonlyoneroot.h \
    obnlowercomputercontrol.h \
    obnrealcontrolwidget.h

FORMS += \
    obnlistnodeinform.ui \
#    obnlogvisualization.ui \
#    obnlogvisualizationdraw.ui \
#    obnlogvisualizationdrawonlyone.ui \
#    obnlogvisualizationdsp.ui \
#    obnlogvisualzationonlyoneroot.ui \
    obnlowercomputercontrol.ui \
    obnrealcontrolwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Image.qrc \
    qss.qrc

















