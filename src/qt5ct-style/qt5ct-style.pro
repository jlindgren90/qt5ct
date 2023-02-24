include(../../qt5ct.pri)

TEMPLATE = lib
TARGET = qt5ct-style
QT += widgets

# Input

CONFIG += plugin

target.path = $$PLUGINDIR/styles
INSTALLS += target

INCLUDEPATH += ../

HEADERS += \
    qt5ctproxystyle.h

SOURCES += \
    plugin.cpp \
    qt5ctproxystyle.cpp

OTHER_FILES += \
    qt5ct.json
