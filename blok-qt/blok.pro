#-------------------------------------------------
#
# Project created by QtCreator 2012-03-19T21:00:45
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = blok
TEMPLATE = app
LIBS += -lBox2D -lphonon

SOURCES += main.cpp\
        mainwindow.cpp \
    pluginloader.cpp \
    isimulator.cpp \
    box2dsimulator.cpp

HEADERS  += mainwindow.h \
    pluginloader.h \
    isimulator.h \
    box2dsimulator.h

FORMS    += mainwindow.ui

RESOURCES += \
    blok.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../images_lib/release/ -lblok-images
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../images_lib/debug/ -lblok-images
else:unix: LIBS += -L$$PWD/../images_lib/ -lblok-images

INCLUDEPATH += $$PWD/../images_lib
DEPENDPATH += $$PWD/../images_lib
