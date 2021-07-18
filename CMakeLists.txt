cmake_minimum_required(VERSION 3.5)

project(examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-fsanitize=address -fanalyzer -Wall -Wextra -Wpedantic -pedantic-errors")
endif()

file(GLOB SUB_EXAMPLES ${CMAKE_CURRENT_SOURCE_DIR}/sub_examples/*)
foreach(EXAMPLE ${SUB_EXAMPLES})
  get_filename_component(EXAMPLE_SELECTED_NAME ${EXAMPLE} NAME)
  option(example_${EXAMPLE_SELECTED_NAME} "example_${EXAMPLE_SELECTED_NAME}" ON)

  if (example_${EXAMPLE_SELECTED_NAME})
    add_subdirectory(${EXAMPLE})
  endif(${EXAMPLE}_example)
endforeach()
