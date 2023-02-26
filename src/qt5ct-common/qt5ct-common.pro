include(../../qt5ct.pri)

TEMPLATE = lib
TARGET = qt5ct-common
QT -= gui
LIBS -= -lqt5ct-common

VER_MAJ = $$system(cat qt5ct.h | grep 'define\\ QT5CT_VERSION_MAJOR' | cut -d '\\ ' -f3)
VER_MIN = $$system(cat qt5ct.h | grep 'define\\ QT5CT_VERSION_MINOR' | cut -d '\\ ' -f3)

# Input

DEFINES += QT5CT_LIBRARY

HEADERS += \
    qt5ct.h

SOURCES += \
    qt5ct.cpp

target.path = $$LIBDIR

INSTALLS += target
