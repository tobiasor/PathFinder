#-------------------------------------------------
#
# Project created by QtCreator 2015-10-28T05:19:39
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathFinderUi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygraphicsscene.cpp \
    ../a.inl \
    ../findpath.cpp \
    ../gridnode.cpp

HEADERS  += mainwindow.h \
    mygraphicsscene.h \
    ../a.h \
    ../findpath.h \
    ../gridnode.h

FORMS    += mainwindow.ui
