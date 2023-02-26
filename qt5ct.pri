#Some conf to redirect intermediate stuff in separate dirs
UI_DIR=./.build/ui/
MOC_DIR=./.build/moc/
OBJECTS_DIR=./.build/obj
RCC_DIR=./.build/rcc

QMAKE_DISTCLEAN += -r .build
QMAKE_DISTCLEAN += translations/*.qm

CONFIG += c++11 hide_symbols ordered

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../qt5ct-common
QMAKE_LIBDIR += ../qt5ct-common
LIBS += -lqt5ct-common


!isEqual (QT_MAJOR_VERSION, 5) {
  error("Use Qt 5.9.0 or higher.")
}

!greaterThan(QT_MINOR_VERSION, 8) {
  error("Use Qt 5.9.0 or higher.")
}

#Install paths
unix {
  isEmpty(PREFIX): PREFIX = /usr
  isEmpty(PLUGINDIR): PLUGINDIR = $$[QT_INSTALL_PLUGINS]
  isEmpty(LIBDIR): LIBDIR=$$[QT_INSTALL_LIBS]

  BINDIR = $$PREFIX/bin
  DATADIR = $$PREFIX/share

  DEFINES += QT5CT_DATADIR=\\\"$$DATADIR\\\"
}
