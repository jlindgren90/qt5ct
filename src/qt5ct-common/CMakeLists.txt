project(qt5ct-common)

#extract version from qt5ct.h
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/qt5ct.h"
     QT5CT_VERSION_DATA REGEX "^#define[ \t]+QT5CT_VERSION_[A-Z]+[ \t]+[0-9]+.*$")

if(QT5CT_VERSION_DATA)
  foreach(item IN ITEMS MAJOR MINOR)
    string(REGEX REPLACE ".*#define[ \t]+QT5CT_VERSION_${item}[ \t]+([0-9]+).*"
       "\\1" QT5CT_VERSION_${item} ${QT5CT_VERSION_DATA})
  endforeach()
  set(QT5CT_VERSION "${QT5CT_VERSION_MAJOR}.${QT5CT_VERSION_MINOR}")
  set(QT5CT_SOVERSION "${QT5CT_VERSION_MAJOR}")
  message(STATUS "qt5ct version: ${QT5CT_VERSION}")
else()
  message(FATAL_ERROR "invalid header")
endif()

add_definitions(-DQT5CT_LIBRARY)

set(app_SRCS
  qt5ct.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_library(qt5ct-common SHARED ${app_SRCS})
set_target_properties(qt5ct-common PROPERTIES VERSION ${QT5CT_VERSION})
target_link_libraries(qt5ct-common PRIVATE Qt5::Core)
install(TARGETS qt5ct-common DESTINATION ${CMAKE_INSTALL_LIBDIR})
