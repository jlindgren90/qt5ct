include(../../qt5ct.pri)

TEMPLATE = lib
TARGET = qt5ct-common
QT -= gui

# Input

CONFIG += staticlib

HEADERS += \
    qt5ct.h

SOURCES += \
    qt5ct.cpp
