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
DESTDIR = ../images_plugins

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

RESOURCES += \
    default.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../images_lib/release/ -lblok-images
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../images_lib/debug/ -lblok-images
else:unix: LIBS += -L$$PWD/../images_lib/ -lblok-images

INCLUDEPATH += $$PWD/../images_lib
DEPENDPATH += $$PWD/../images_lib
