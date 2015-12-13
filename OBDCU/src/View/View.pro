#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T19:45:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = View
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    homewidget.cpp \
    dtcwidget.cpp \
    emulationwidget.cpp \
    settingswidget.cpp \
    communicationswidget.cpp \
    databasewidget.cpp \
    sensorwidget.cpp \
    actionsidebar.cpp \
    stackedtabwrapper.cpp \
    errorpage.cpp \
    abstractobdwidget.cpp \
    viewadministrator.cpp

HEADERS  += mainwindow.h \
    homewidget.h \
    dtcwidget.h \
    emulationwidget.h \
    settingswidget.h \
    communicationswidget.h \
    databasewidget.h \
    sensorwidget.h \
    actionsidebar.h \
    stackedtabwrapper.h \
    errorpage.h \
    abstractobdwidget.h \
    viewadministrator.h

FORMS    += mainwindow.ui \
    homewidget.ui \
    dtcwidget.ui \
    emulationwidget.ui \
    settingswidget.ui \
    communicationswidget.ui \
    databasewidget.ui \
    sensorwidget.ui \
    actionsidebar.ui \
    stackedtabwrapper.ui \
    errorpage.ui

RESOURCES += \
    resources.qrc

OTHER_FILES +=
