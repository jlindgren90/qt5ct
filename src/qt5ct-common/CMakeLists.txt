project(qt5ct-common)

add_definitions(-DQT5CT_LIBRARY)

set(app_SRCS
  qt5ct.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_library(qt5ct-common SHARED ${app_SRCS})
target_link_libraries(qt5ct-common PRIVATE Qt5::Core)
install(TARGETS qt5ct-common DESTINATION ${CMAKE_INSTALL_LIBDIR})
