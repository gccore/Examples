cmake_minimum_required(VERSION 3.5)
project(QCustomPlot LANGUAGES CXX)

set(CMAKE_AUTOUIC on)
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC on)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

add_library(${PROJECT_NAME} SHARED
  qcustomplot.cpp
  qcustomplot.h
)
add_library(core::third_party::QCustomPlot ALIAS ${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DQCUSTOMPLOT_COMPILE_LIBRARY)
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt5::PrintSupport
  Qt5::Widgets
  Qt5::Core
  Qt5::Gui
)
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

