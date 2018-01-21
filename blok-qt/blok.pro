#-------------------------------------------------
#
# Project created by QtCreator 2012-03-19T21:00:45
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = blok
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    pluginloader.cpp

HEADERS  += mainwindow.h \
    pluginloader.h

FORMS    += mainwindow.ui

RESOURCES += \
    blok.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../images_lib/release/ -lblok-images
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../images_lib/debug/ -lblok-images
else:unix: LIBS += -L$$PWD/../images_lib/ -lblok-images

INCLUDEPATH += $$PWD/../images_lib
DEPENDPATH += $$PWD/../images_lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../simulator_lib/release/ -lblok-simulator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../simulator_lib/debug/ -lblok-simulator
else:unix: LIBS += -L$$PWD/../simulator_lib/ -lblok-simulator

INCLUDEPATH += $$PWD/../simulator_lib
DEPENDPATH += $$PWD/../simulator_lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../audio_lib/release/ -lblok-audio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../audio_lib/debug/ -lblok-audio
else:unix: LIBS += -L$$PWD/../audio_lib/ -lblok-audio

INCLUDEPATH += $$PWD/../audio_lib
DEPENDPATH += $$PWD/../audio_lib
