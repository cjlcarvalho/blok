#-------------------------------------------------
#
# Project created by QtCreator 2018-01-20T23:27:16
#
#-------------------------------------------------

QT       -= gui

TARGET = blok-audio
TEMPLATE = lib

DEFINES += BLOKAUDIO_LIBRARY
DESTDIR = ../audio_lib

SOURCES += \
        iaudio.cpp

HEADERS += \
        iaudio.h \
        blok-audio_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
