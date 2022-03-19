cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

set(CMAKE_AUTOUIC on)
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC on)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB private_files
  source/*.cc
  source/*.h
)
file(GLOB public_files
  include/${PROJECT_NAME}/*.h
  include/${PROJECT_NAME}/*.cc
  include/${PROJECT_NAME}/meta.json
)

add_library(${PROJECT_NAME} SHARED
  ${private_files}
  ${public_files}
)
add_library(core::plugins::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  core::plugins::Interface
)

include(ConfigQCustomPlot)
core_ConfigQCustomPlot(${PROJECT_NAME})
