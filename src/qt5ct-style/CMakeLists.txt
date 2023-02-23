project(qt5ct-style)

add_definitions(-DUSE_WIDGETS)

set(app_SRCS
  plugin.cpp
  qt5ctproxystyle.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_library(qt5ct-style MODULE ${app_SRCS})
target_link_libraries(qt5ct-style PRIVATE Qt5::Widgets qt5ct-common)
install(TARGETS qt5ct-style DESTINATION ${PLUGINDIR}/styles)
