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
DESTDIR = ../images_plugins

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

RESOURCES += \
    snow.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../images_lib/release/ -lblok-images
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../images_lib/debug/ -lblok-images
else:unix: LIBS += -L$$PWD/../images_lib/ -lblok-images

INCLUDEPATH += $$PWD/../images_lib
DEPENDPATH += $$PWD/../images_lib
