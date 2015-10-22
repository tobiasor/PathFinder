QT += core
QT -= gui

TARGET = PathFinder
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -Wall
TEMPLATE = app

SOURCES += main.cpp \
    gridnode.cpp \
    a.inl \
    findpath.cpp

HEADERS += \
    gridnode.h \
    a.h \
    findpath.h

