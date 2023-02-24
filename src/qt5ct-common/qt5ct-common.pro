include(../../qt5ct.pri)

TEMPLATE = lib
TARGET = qt5ct-common
QT -= gui

# Input

CONFIG += hide_symbols

DEFINES += QT5CT_LIBRARY

HEADERS += \
    qt5ct.h

SOURCES += \
    qt5ct.cpp
