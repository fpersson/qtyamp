#-------------------------------------------------
#
# Project created by QtCreator 2013-07-05T19:16:11
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += multimedia

QT       -= gui

TARGET = qtyamp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mediaserver/cserver.cpp \
    mediaserver/cmediaplayer.cpp \
    misc/pathmanager.cpp \
    misc/defaultsettings.cpp \
    utils/flog.cpp \
    utils/pidwriter.cpp \
    mediaserver/commandparser.cpp

HEADERS += \
    mediaserver/cserver.h \
    mediaserver/cmediaplayer.h \
    misc/pathmanager.h \
    misc/defaultsettings.h \
    utils/flog.h \
    utils/pidwriter.h \
    mediaserver/commandparser.h
