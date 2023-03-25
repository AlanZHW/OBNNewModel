
# ====== OBN软件主界面

QT       += core gui network charts #webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../obnsoftwareroot.pri)

TEMPLATE = app
TARGET   = OBNSoftwareMain
DESTDIR  += $$OBN_RUN_PATH

CONFIG += c++11

INCLUDEPATH += $$OBN_ROOT_PATH/include
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNWelcomeToTheInterface
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNLowerMachineControl/OBNRetrieveAvailableNodes
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNSoftwareMainWidget
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/QtFtp
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/QtFtp
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNOtherLibraries/Core
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
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/RNManager
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/RNMBaseLib
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/OBNRealTimeWaveformDisplay
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/OBNLowerCumputerOTA
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNRNMModel/OBNRetrieveAvailableNodes
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNQualityControl/OBNJobMonitorPrograme
INCLUDEPATH += $$OBN_ROOT_PATH/src/OBNDataManagerModel/OBNCalibrationDataDisplay

LIBS += -L$$OBN_RUN_PATH -lobnWelcomeToTheInterface -lobnSoftwareMainWidget
LIBS += -L$$OBN_RUN_PATH -lobnretrieveavailablenodes
LIBS += -L$$OBN_RUN_PATH -lCore -lGPublicSo -lAreaNodeManager -lQtFtp
LIBS += -lAppGlobal
LIBS += -L$$OBN_RUN_PATH -lLineManager -lGPositionSystem
LIBS += -L$$OBN_RUN_PATH -lOBNDisplaySEGY -lQCPlotter -lOBNExportSEGY -lOBNOpenSEGY -lOBNCalirationDataDisplay
LIBS += -L$$OBN_RUN_PATH -lOBNLogVisualizationDisplay -lGobsDtMagerDiffTime
LIBS += -L$$OBN_RUN_PATH -lRNManager -lRNMBaseLib -lobnrealtimewaveformdisp -lobnlowercomputerota
LIBS += -L$$OBN_RUN_PATH -lOBNJobMonitorPrograme -lOBNLMGRAreaListWidget -lobnretrieveavailablenodes

SOURCES += \
        main.cpp \
        obnsoftwaremain.cpp

HEADERS += \
    obnsoftwaremain.h
