#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T12:17:47
#
#-------------------------------------------------

QT       += core widgets

TARGET = blok-images
TEMPLATE = lib static

DEFINES += BLOKIMAGES_LIBRARY
DESTDIR = ../images_lib

SOURCES += \
    imagefactory.cpp \
    ibackgroundimage.cpp \
    igroundimage.cpp \
    iplayerimage.cpp \
    iblockimage.cpp

HEADERS +=\
        blok-images_global.h \
    imagefactory.h \
    ibackgroundimage.h \
    igroundimage.h \
    iplayerimage.h \
    iblockimage.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
