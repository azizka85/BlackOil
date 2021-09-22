ROOT_DIR = $${OUT_PWD}/..

TARGET = $$qtLibraryTarget(BlackOil.Data)
DESTDIR = $${ROOT_DIR}/lib

TEMPLATE = lib
DEFINES += DATA_LIBRARY

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
    Readers \
    Project \
    Arrays \
    Helpers \
    Helpers/Eclipse \

SOURCES += \
    Arrays/boxarray.cpp \
    Arrays/subarray.cpp \
    Grid/block.cpp \
    Grid/box.cpp \
    Grid/line.cpp \
    Grid/plane.cpp \
    Grid/point.cpp \
    Grid/segment.cpp \
    Helpers/Eclipse/readfilehelper.cpp \
    Helpers/mathhelper.cpp \
    Project/aquancondata.cpp \
    Project/aqufetpdata.cpp \
    Project/arraynamesenum.cpp \
    Project/compdatdata.cpp \
    Project/datatypeenum.cpp \
    Project/defaultvalues.cpp \
    Project/densitydata.cpp \
    Project/dimpesdata.cpp \
    Project/endscaledata.cpp \
    Project/enkrvddata.cpp \
    Project/enpcvddata.cpp \
    Project/enspcvddata.cpp \
    Project/eqldimsdata.cpp \
    Project/equildata.cpp \
    Project/facetypeenum.cpp \
    Project/fluidtypeenum.cpp \
    Project/gravitydata.cpp \
    Project/ihboptionsenum.cpp \
    Project/maotpoptionsenum.cpp \
    Project/oilvisctdata.cpp \
    Project/operatordata.cpp \
    Project/operatortypeenum.cpp \
    Project/pbvddata.cpp \
    Project/pmaxdata.cpp \
    Project/ppcwmaxdata.cpp \
    Project/projectdata.cpp \
    Project/prvddata.cpp \
    Project/pvcdodata.cpp \
    Project/pvcodata.cpp \
    Project/pvdgdata.cpp \
    Project/pvdodata.cpp \
    Project/pvtgdata.cpp \
    Project/pvtodata.cpp \
    Project/pvtwdata.cpp \
    Project/referencepressureoptionsenum.cpp \
    Project/regionoptionsenum.cpp \
    Project/rockdata.cpp \
    Project/rockoptsdata.cpp \
    Project/rpmenum.cpp \
    Project/rsconstdata.cpp \
    Project/rsvddata.cpp \
    Project/sgfndata.cpp \
    Project/sgofdata.cpp \
    Project/sgwfndata.cpp \
    Project/slgofdata.cpp \
    Project/sof2data.cpp \
    Project/sof32ddata.cpp \
    Project/sof32dkrodata.cpp \
    Project/sof3data.cpp \
    Project/somgasdata.cpp \
    Project/somwatdata.cpp \
    Project/specheatdata.cpp \
    Project/specrockdata.cpp \
    Project/swfndata.cpp \
    Project/swofdata.cpp \
    Project/tabdimsdata.cpp \
    Project/casesenum.cpp \
    Project/directionalenum.cpp \
    Project/viscrefdata.cpp \
    Project/watvisctdata.cpp \
    Project/wconhistdata.cpp \
    Project/wconinjedata.cpp \
    Project/wconinjhdata.cpp \
    Project/wconproddata.cpp \
    Project/wellcontrolenum.cpp \
    Project/wellstatusenum.cpp \
    Project/welspecsdata.cpp \
    Project/weltargdata.cpp \
    Readers/eclipsefilereader.cpp \
    Project/irreversibleenum.cpp \
    Project/modelsenum.cpp \
    Project/monthsenum.cpp \
    Project/unitsenum.cpp

HEADERS += \
    Arrays/boxarray.h \
    Arrays/subarray.h \
    Grid/block.h \
    Grid/box.h \
    Grid/line.h \
    Grid/plane.h \
    Grid/point.h \
    Grid/segment.h \
    Helpers/Eclipse/readfilehelper.h \
    Helpers/mathhelper.h \
    Project/aquancondata.h \
    Project/aqufetpdata.h \
    Project/arraynamesenum.h \
    Project/compdatdata.h \
    Project/datatypeenum.h \
    Project/defaultvalues.h \
    Project/densitydata.h \
    Project/dimpesdata.h \
    Project/endscaledata.h \
    Project/enkrvddata.h \
    Project/enpcvddata.h \
    Project/enspcvddata.h \
    Project/eqldimsdata.h \
    Project/equildata.h \
    Project/facetypeenum.h \
    Project/fluidtypeenum.h \
    Project/gravitydata.h \
    Project/ihboptionsenum.h \
    Project/maotpoptionsenum.h \
    Project/oilvisctdata.h \
    Project/operatordata.h \
    Project/operatortypeenum.h \
    Project/pbvddata.h \
    Project/pmaxdata.h \
    Project/ppcwmaxdata.h \
    Project/projectdata.h \
    Project/prvddata.h \
    Project/pvcdodata.h \
    Project/pvcodata.h \
    Project/pvdgdata.h \
    Project/pvdodata.h \
    Project/pvtgdata.h \
    Project/pvtodata.h \
    Project/pvtwdata.h \
    Project/referencepressureoptionsenum.h \
    Project/regionoptionsenum.h \
    Project/rockdata.h \
    Project/rockoptsdata.h \
    Project/rpmenum.h \
    Project/rsconstdata.h \
    Project/rsvddata.h \
    Project/sgfndata.h \
    Project/sgofdata.h \
    Project/sgwfndata.h \
    Project/slgofdata.h \
    Project/sof2data.h \
    Project/sof32ddata.h \
    Project/sof32dkrodata.h \
    Project/sof3data.h \
    Project/somgasdata.h \
    Project/somwatdata.h \
    Project/specheatdata.h \
    Project/specrockdata.h \
    Project/swfndata.h \
    Project/swofdata.h \
    Project/tabdimsdata.h \
    Project/casesenum.h \
    Project/directionalenum.h \
    Project/viscrefdata.h \
    Project/watvisctdata.h \
    Project/wconhistdata.h \
    Project/wconinjedata.h \
    Project/wconinjhdata.h \
    Project/wconproddata.h \
    Project/wellcontrolenum.h \
    Project/wellstatusenum.h \
    Project/welspecsdata.h \
    Project/weltargdata.h \
    Readers/eclipsefilereader.h \
    Project/irreversibleenum.h \
    Project/modelsenum.h \
    Project/monthsenum.h \
    Project/unitsenum.h \
    data_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
