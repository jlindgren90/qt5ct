project(qt5ct-common)

set(app_SRCS
  qt5ct.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_library(qt5ct-common STATIC ${app_SRCS})
target_link_libraries(qt5ct-common PRIVATE Qt5::Widgets)
