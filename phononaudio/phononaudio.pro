#-------------------------------------------------
#
# Project created by QtCreator 2018-01-20T23:35:27
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT       -= gui

TARGET = phononaudio
TEMPLATE = lib
CONFIG += plugin

LIBS += -lphonon

DEFINES += PHONONAUDIO_LIBRARY
DESTDIR = ../audio_plugins

SOURCES += \
        phononaudio.cpp

HEADERS += \
        phononaudio.h \
        phononaudio_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../audio_lib/release/ -lblok-audio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../audio_lib/debug/ -lblok-audio
else:unix: LIBS += -L$$PWD/../audio_lib/ -lblok-audio

INCLUDEPATH += $$PWD/../audio_lib
DEPENDPATH += $$PWD/../audio_lib
