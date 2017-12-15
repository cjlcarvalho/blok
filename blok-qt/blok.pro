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

RESOURCES += \
    blok.qrc
