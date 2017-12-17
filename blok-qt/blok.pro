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
    simulator.cpp \
    pluginloader.cpp

HEADERS  += mainwindow.h \
    simulator.h \
    pluginloader.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug/release/ -lblok-images
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug/debug/ -lblok-images
else:unix: LIBS += -L$$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug/ -lblok-images

INCLUDEPATH += $$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug
DEPENDPATH += $$PWD/../build-blok-images-Qt_4_8_7_in_PATH_qt4-Debug
