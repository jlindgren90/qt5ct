project(app)

set(app_SRCS
  appearancepage.cpp
  fontconfigdialog.cpp
  fontspage.cpp
  iconthemepage.cpp
  interfacepage.cpp
  main.cpp
  mainwindow.cpp
  paletteeditdialog.cpp
  qsseditordialog.cpp
  qsspage.cpp
  qt5ct.cpp
  tabpage.cpp
  troubleshootingpage.cpp
  appearancepage.ui
  fontconfigdialog.ui
  fontspage.ui
  iconthemepage.ui
  interfacepage.ui
  mainwindow.ui
  paletteeditdialog.ui
  previewform.ui
  qsseditordialog.ui
  qsspage.ui
  troubleshootingpage.ui
  translations/translations.qrc
)

add_executable(qt5ct ${app_SRCS})
target_link_libraries(qt5ct PRIVATE Qt5::Widgets Qt5::Concurrent Qt5::WidgetsPrivate)
install(TARGETS qt5ct DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES qt5ct.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
