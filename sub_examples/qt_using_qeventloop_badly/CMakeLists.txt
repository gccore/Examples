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

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB include_files include/${PROJECT_NAME}/*.h)
file(GLOB source_files source/*.cc)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

add_subdirectory(libraries/core_common_things)
add_subdirectory(libraries/core_interface)

file(GLOB plugins_directory plugins/*)
foreach(plugin ${plugins_directory})
  get_filename_component(plugin_dir_name ${plugin} NAME)
  option(plugin_${plugin_dir_name} "plugin_${plugin_dir_name}" on)

  if (plugin_${plugin_dir_name})
    add_subdirectory(${plugin})
  endif(plugin_${plugin_dir_name})
endforeach()

add_executable(${PROJECT_NAME}
  ${include_files}
  ${source_files}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  core::plugins::Interface
  core::CommonThings

  Qt5::Widgets
  Qt5::Core
  Qt5::Gui
)
target_include_directories(${PROJECT_NAME} PRIVATE
  include
)

