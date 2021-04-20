project(qt5ct-qtplugin)

set(app_SRCS
  main.cpp
  qt5ctplatformtheme.cpp
  ../qt5ct/qt5ct.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_library(qt5ct-qtplugin MODULE ${app_SRCS})
set_target_properties(qt5ct-qtplugin PROPERTIES OUTPUT_NAME qt5ct)
target_link_libraries(qt5ct-qtplugin PRIVATE Qt5::Widgets Qt5::GuiPrivate)
install(TARGETS qt5ct-qtplugin DESTINATION ${PLUGINDIR}/platformthemes)
