#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T18:36:22
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += gui core widgets

TARGET = snow
TEMPLATE = lib
CONFIG += plugin

DEFINES += SNOW_LIBRARY
DESTDIR = ../image_plugins

SOURCES += snowimagefactory.cpp \
    snowbackgroundimage.cpp \
    snowgroundimage.cpp \
    snowblockimage.cpp \
    snowplayerimage.cpp

HEADERS += snowimagefactory.h\
        snow_global.h \
    snowbackgroundimage.h \
    snowgroundimage.h \
    snowblockimage.h \
    snowplayerimage.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug/release/ -lblok-images
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug/debug/ -lblok-images
else:unix: LIBS += -L$$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug/ -lblok-images

INCLUDEPATH += $$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug
DEPENDPATH += $$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug

RESOURCES += \
    snow.qrc
