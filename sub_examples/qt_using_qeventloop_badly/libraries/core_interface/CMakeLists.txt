cmake_minimum_required(VERSION 3.5)
project(core_interface LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_AUTOUIC on)
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC on)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

file(GLOB public_files
  include/${PROJECT_NAME}/*.h
  source/*.cc
)

add_library(${PROJECT_NAME} INTERFACE ${public_files})
add_library(core::plugins::Interface ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(${PROJECT_NAME} INTERFACE
  Qt5::Widgets
  Qt5::Core
)
