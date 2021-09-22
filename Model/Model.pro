ROOT_DIR = $${OUT_PWD}/..

TARGET = $$qtLibraryTarget(BlackOil.Model)
DESTDIR = $${ROOT_DIR}/lib

TEMPLATE = lib
DEFINES += MODEL_LIBRARY

CONFIG += c++11 qt

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    Grid \
    Tasks \
    Wells \
    SF \
    PVT \
    Helpers \
    ../Data \
    ../Data/Grid \
    ../Data/Readers \
    ../Data/Project \
    ../Data/Arrays \
    ../Data/Helpers \
    ../Data/Helpers/Eclipse

SOURCES += \
    Grid/xlayermodel.cpp \
    Grid/ylayermodel.cpp \
    Grid/zlayermodel.cpp \
    PVT/pvtgmodel.cpp \
    PVT/pvtmodel.cpp \
    PVT/pvtomodel.cpp \
    PVT/pvtregionmodel.cpp \
    SF/sfmodel.cpp \
    SF/sfregionmodel.cpp \
    SF/sgofmodel.cpp \
    SF/swofmodel.cpp \
    Tasks/loadprojecttask.cpp \
    Tasks/processprojecttask.cpp \
    Wells/compdatmodel.cpp \
    Wells/wconinjemodel.cpp \
    Wells/wconprodmodel.cpp \
    Wells/wellsmodel.cpp \
    Wells/welspecsmodel.cpp \
    gridmodel.cpp \
    operatormodel.cpp \
    projectloadingstateenum.cpp \
    projectmodel.cpp

HEADERS += \
    Grid/xlayermodel.h \
    Grid/ylayermodel.h \
    Grid/zlayermodel.h \
    PVT/pvtgmodel.h \
    PVT/pvtmodel.h \
    PVT/pvtomodel.h \
    PVT/pvtregionmodel.h \
    SF/sfmodel.h \
    SF/sfregionmodel.h \
    SF/sgofmodel.h \
    SF/swofmodel.h \
    Tasks/loadprojecttask.h \
    Tasks/processprojecttask.h \
    Wells/compdatmodel.h \
    Wells/wconinjemodel.h \
    Wells/wconprodmodel.h \
    Wells/wellsmodel.h \
    Wells/welspecsmodel.h \
    gridmodel.h \
    model_global.h \
    operatormodel.h \
    projectloadingstateenum.h \
    projectmodel.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

LIBS += -L$${ROOT_DIR}/lib -lBlackOil.Data
