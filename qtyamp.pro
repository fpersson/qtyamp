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
    cserver.cpp \
    cmediaplayer.cpp \
    configreader.cpp \
    fqlog.cpp

HEADERS += \
    cserver.h \
    cmediaplayer.h \
    configreader.h \
    fqlog.h
