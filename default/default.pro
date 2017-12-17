#-------------------------------------------------
#
# Project created by QtCreator 2017-12-17T20:00:36
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += gui core widgets

TARGET = default_
TEMPLATE = lib
CONFIG += plugin

DEFINES += DEFAULT_LIBRARY
DESTDIR = ../image_plugins

SOURCES += defaultimagefactory.cpp \
    defaultbackgroundimage.cpp \
    defaultblockimage.cpp \
    defaultgroundimage.cpp \
    defaultplayerimage.cpp

HEADERS += defaultimagefactory.h\
        default_global.h \
    defaultbackgroundimage.h \
    defaultblockimage.h \
    defaultgroundimage.h \
    defaultplayerimage.h

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
    default.qrc
