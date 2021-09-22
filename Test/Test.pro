ROOT_DIR = $${OUT_PWD}/..

TARGET = BlackOil.Test
DESTDIR = $${ROOT_DIR}/lib

QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += \
    Data/Grid \
    Data/Arrays \
    Data/Helpers \
    Data/Helpers/Eclipse \
    Data/Project \
    Data/Readers \
    ../Data \
    ../Data/Grid \
    ../Data/Readers \
    ../Data/Project \
    ../Data/Arrays \
    ../Data/Helpers \
    ../Data/Helpers/Eclipse

SOURCES +=  \
    Data/Arrays/boxarraytest.cpp \
    Data/Grid/boxtest.cpp \
    Data/Helpers/Eclipse/readfilehelpertest.cpp \
    Data/Project/projectdatatest.cpp \
    Data/Readers/eclipsefilereadertest.cpp \
    main.cpp

HEADERS += \
    Data/Arrays/boxarraytest.h \
    Data/Grid/boxtest.h \
    Data/Helpers/Eclipse/readfilehelpertest.h \
    Data/Project/projectdatatest.h \
    Data/Readers/eclipsefilereadertest.h \
    test.h

LIBS += -L$${ROOT_DIR}/lib -lBlackOil.Data -lBlackOil.Model
