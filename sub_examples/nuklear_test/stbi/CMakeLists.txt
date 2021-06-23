cmake_minimum_required(VERSION 3.5)

project(stbi_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
 set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif()

add_library(${PROJECT_NAME} INTERFACE)
add_library(core::stbi::library ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

