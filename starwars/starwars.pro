#-------------------------------------------------
#
# Project created by QtCreator 2017-12-18T23:35:52
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += gui core widgets

TARGET = starwars
TEMPLATE = lib
CONFIG += plugin

DEFINES += STARWARS_LIBRARY
DESTDIR = ../images_plugins

SOURCES += starwarsimagefactory.cpp \
    starwarsbackgroundimage.cpp \
    starwarsblockimage.cpp \
    starwarsgroundimage.cpp \
    starwarsplayerimage.cpp

HEADERS += starwarsimagefactory.h\
        starwars_global.h \
    starwarsbackgroundimage.h \
    starwarsblockimage.h \
    starwarsgroundimage.h \
    starwarsplayerimage.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../images_lib/release/ -lblok-images
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../images_lib/debug/ -lblok-images
else:unix: LIBS += -L$$PWD/../images_lib/ -lblok-images

INCLUDEPATH += $$PWD/../images_lib
DEPENDPATH += $$PWD/../images_lib

RESOURCES += \
    starwars.qrc
