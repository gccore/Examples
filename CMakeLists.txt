cmake_minimum_required(VERSION 3.5)

project(examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SUB_EXAMPLES ${CMAKE_CURRENT_SOURCE_DIR}/sub_examples/*)
foreach(EXAMPLE ${SUB_EXAMPLES})
  add_subdirectory(${EXAMPLE})
endforeach()
