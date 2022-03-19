cmake_minimum_required(VERSION 3.5)
project(core_common_things LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(Qt5Core)

file(GLOB public_files
  include/${PROJECT_NAME}/*.cc
  include/${PROJECT_NAME}/*.inc
  include/${PROJECT_NAME}/*.h
)
file(GLOB private_files
  source/*.cc
  source/*.inc
  source/*.h
)

add_library(${PROJECT_NAME} SHARED
  ${public_files}
  ${private_files}
)
add_library(core::CommonThings ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt5::Core
)
