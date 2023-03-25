#-------------------------------------------------
#
# Project created by QtCreator 2019-02-26T09:33:39
#
#-------------------------------------------------

# ====== 插值库

QT       -= gui


include(../../../obnsoftwareroot.pri)

TARGET = Algorithm
TEMPLATE = lib
DESTDIR  += $$OBN_RUN_PATH
CONFIG   += plugin  #描述生成单一库文件

DEFINES += ALGORITHM_LIBRARY ADD_
#DEFINES += HAVE_LAPACK_CONFIG_H  LAPACK_COMPLEX_STRUCTURE

#INCLUDEPATH += $$GOBS_THIRDPARTY/include
#LIBS        += -L$$GOBS_THIRDPARTY_LIB -llibblas -lliblapack -lliblapacke

SOURCES +=  algorithm.cpp \
            geo2xy_utm.cpp \
            gobs_interpolation.cpp \
            gobs_location.cpp

HEADERS +=  algorithm.h\
            algorithm_global.h \
            geo2xy_utm.h \
            ToolsAlgo.h \
            gobs_location.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
