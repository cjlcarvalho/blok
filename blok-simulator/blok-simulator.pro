#-------------------------------------------------
#
# Project created by QtCreator 2018-01-20T17:19:11
#
#-------------------------------------------------

QT       -= gui

TARGET = blok-simulator
TEMPLATE = lib

DEFINES += BLOKSIMULATOR_LIBRARY
DESTDIR += ../simulator_lib

SOURCES += \
        isimulator.cpp

HEADERS += \
        isimulator.h \
        blok-simulator_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
