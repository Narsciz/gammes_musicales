#-------------------------------------------------
#
# Project created by QtCreator 2017-03-10T10:10:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UtProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chord.cpp \
    scale.cpp \
    harmonicstructure.cpp \
    hschord.cpp \
    hsscale.cpp \
    chorddictionary.cpp \
    scaledictionary.cpp \
    cs.cpp \
    ut.cpp \
    menubar.cpp

HEADERS  += mainwindow.h \
    chord.h \
    scale.h \
    harmonicstructure.h \
    hschord.h \
    hsscale.h \
    chorddictionary.h \
    scaledictionary.h \
    algo.h \
    cs.h \
    ut.h \
    menubar.h

FORMS    += mainwindow.ui
