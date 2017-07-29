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
    mediaserver/configreader.cpp \
    misc/pathmanager.cpp \
    utils/flog.cpp \
    utils/flaghandler.cpp \
    utils/pidwriter.cpp \
    mediaserver/commandparser.cpp

HEADERS += \
    mediaserver/cserver.h \
    mediaserver/cmediaplayer.h \
    mediaserver/configreader.h \
    misc/pathmanager.h \
    utils/flog.h \
    utils/flaghandler.h \
    utils/pidwriter.h \
    mediaserver/commandparser.h
