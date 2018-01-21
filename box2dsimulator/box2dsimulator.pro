#-------------------------------------------------
#
# Project created by QtCreator 2018-01-20T17:45:51
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT       -= gui

TARGET = box2dsimulator
TEMPLATE = lib
CONFIG += plugin

LIBS += -lBox2D

DEFINES += BOX2DSIMULATOR_LIBRARY
DESTDIR = ../simulator_plugins

SOURCES += \
        box2dsimulator.cpp

HEADERS += \
        box2dsimulator.h \
        box2dsimulator_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../simulator_lib/release/ -lblok-simulator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../simulator_lib/debug/ -lblok-simulator
else:unix: LIBS += -L$$PWD/../simulator_lib/ -lblok-simulator

INCLUDEPATH += $$PWD/../simulator_lib
DEPENDPATH += $$PWD/../simulator_lib
