ROOT_DIR = $${OUT_PWD}/..

TARGET = BlackOil.Desktop
DESTDIR = $${ROOT_DIR}/lib

TEMPLATE = lib
DEFINES += DESKTOP_LIBRARY

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    Data \
    Views \    
    Views/Dialogs \
    Views/Settings \
    Views/Controls \
    Views/Controls/Scene3D \
    Models \
    Delegates \
    Tasks \
    Helpers \
    ../../Libraries/Qt-Advanced-Docking-System/src \
    ../Model \
    ../Model/Grid \
    ../Model/Tasks \
    ../Model/Wells \
    ../Model/SF \
    ../Model/PVT \
    ../Model/Helpers \
    ../Data \
    ../Data/Grid \
    ../Data/Readers \
    ../Data/Project \
    ../Data/Arrays \
    ../Data/Helpers \
    ../Data/Helpers/Eclipse

SOURCES += \
    Data/axesdata.cpp \
    Data/vertexdata.cpp \
    Delegates/booleandelegate.cpp \
    Delegates/colordelegate.cpp \
    Helpers/widgethelper.cpp \
    Models/figuresettingsmodel.cpp \
    Models/rotationaxisenum.cpp \
    Tasks/drawscenetask.cpp \
    Views/Controls/Scene3D/axes3d.cpp \
    Views/Controls/Scene3D/well3d.cpp \
    Views/Controls/fieldform.cpp \
    Views/Controls/pvtgform.cpp \
    Views/Controls/pvtoform.cpp \
    Views/Controls/sgofform.cpp \
    Views/Controls/swofform.cpp \
    Views/Controls/wellsscheduleform.cpp \
    Views/Dialogs/projectloadingdialog.cpp \
    Views/Dialogs/scenedrawingdialog.cpp \
    Views/Settings/fieldsettingsform.cpp \
    Views/Settings/figuresettingsform.cpp \
    Views/Settings/gridsettingsform.cpp \
    Views/Settings/palettesettingsform.cpp \
    Views/mainwindow.cpp

HEADERS += \
    Data/axesdata.h \
    Data/vertexdata.h \
    Delegates/booleandelegate.h \
    Delegates/colordelegate.h \
    Helpers/widgethelper.h \
    Models/rotationaxisenum.h \
    Tasks/drawscenetask.h \
    Views/Controls/Scene3D/axes3d.h \
    Views/Controls/Scene3D/well3d.h \
    Views/Controls/fieldform.h \
    Views/Controls/pvtgform.h \
    Views/Controls/pvtoform.h \
    Views/Controls/sgofform.h \
    Views/Dialogs/scenedrawingdialog.h \
    Views/Settings/figuresettingsform.h \
    Views/Settings/gridsettingsform.h \
    Views/Settings/palettesettingsform.h \
    desktop_global.h \
    Models/figuresettingsmodel.h \
    Views/Controls/swofform.h \
    Views/Controls/wellsscheduleform.h \
    Views/Dialogs/projectloadingdialog.h \
    Views/Settings/fieldsettingsform.h \    
    Views/mainwindow.h

FORMS += \
    Views/Controls/fieldform.ui \
    Views/Controls/pvtgform.ui \
    Views/Controls/pvtoform.ui \
    Views/Controls/sgofform.ui \
    Views/Controls/swofform.ui \
    Views/Controls/wellsscheduleform.ui \
    Views/Dialogs/projectloadingdialog.ui \
    Views/Dialogs/scenedrawingdialog.ui \
    Views/Settings/fieldsettingsform.ui \
    Views/Settings/figuresettingsform.ui \
    Views/Settings/gridsettingsform.ui \
    Views/Settings/palettesettingsform.ui \
    Views/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

LIBS += -L$${ROOT_DIR}/lib -lBlackOil.Data -lBlackOil.Model -lqtadvanceddocking
LIBS += -lopengl32
