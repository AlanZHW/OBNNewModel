# OBN

QT       += core gui charts network #webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include(../../obnsoftwareroot.pri)

TEMPLATE = lib
TARGET   = obnSoftwareMainWidget
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

DEFINES += OBNMAINWINDOW_LIBRARY

INCLUDEPATH += $$OBN_INCLUDE_PATH
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/QtFtp
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/GPublicSo
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/AppGlobal

INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNLMGRModel/LineManager
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNLMGRModel/AreaNodeManager
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNLMGRModel/OBNLMGRAreaListWidget
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/GPositionSystem
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/OBNDisplaySEGY
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/OBNExportSEGY
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/OBNOpenSEGY
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/QCPlotter
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/OBNLogVisualizationDisplay
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/GobsDtMagerDiffTime
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/OBNCalibrationDataDisplay

INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/RNManager
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/RNMBaseLib
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/OBNRealTimeWaveformDisplay
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/OBNLowerCumputerOTA
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/OBNRetrieveAvailableNodes
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNQualityControl/OBNJobMonitorPrograme

SOURCES += \
        abstractareadialog.cpp \
        createareadialog.cpp \
        main.cpp     \
        mytabbar.cpp \
        mytabpopup.cpp \
        mytabwidget.cpp \
        obnmainwindow.cpp \
        updateareadialog.cpp

HEADERS += \
        abstractareadialog.h \
        createareadialog.h \
        mytabbar.h \
        mytabpopup.h \
        mytabwidget.h \
        obnmainwindow.h \
        obnmainwindow_global.h \
        updateareadialog.h

FORMS   += \
        obnmainwindow.ui

LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo -lAreaNodeManager -lQtFtp
LIBS += -L$$OBN_RUN_PATH -lLineManager -lGPositionSystem
LIBS += -L$$OBN_RUN_PATH -lOBNDisplaySEGY -lQCPlotter -lOBNExportSEGY -lOBNOpenSEGY -lOBNLMGRAreaListWidget -lOBNCalirationDataDisplay
LIBS += -L$$OBN_RUN_PATH -lOBNLogVisualizationDisplay -lGobsDtMagerDiffTime
LIBS += -L$$OBN_RUN_PATH -lRNManager -lRNMBaseLib -lobnrealtimewaveformdisp -lobnlowercomputerota
LIBS += -L$$OBN_RUN_PATH -lOBNJobMonitorPrograme -lobnretrieveavailablenodes -lAppGlobal

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += mainwindow_cn.ts \
                mainwindow_en.ts

RESOURCES += \
    image.qrc \
    qss.qrc \
    translate.qrc


