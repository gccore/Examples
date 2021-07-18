cmake_minimum_required(VERSION 3.5)

project(examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(flags_address_sanitizer "flags_address_sanitizer" OFF)
option(flags_gcc_analyzer "flags_analyzer" OFF)
option(flags_warnings "flags_warnings" OFF)
option(flags_optimization "flags_optimization" OFF)

if (flags_address_sanitizer)
 list(APPEND CMAKE_CXX_FLAGS "-fsanitize=address")
endif(flags_address_sanitizer)

if (flags_gcc_analyzer)
 list(APPEND CMAKE_CXX_FLAGS "-fanalyzer")
endif(flags_gcc_analyzer)

if (flags_warnings)
 list(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors")
endif(flags_warnings)

if (flags_optimization)
 list(APPEND CMAKE_CXX_FLAGS "-O2")
endif(flags_optimization)

file(GLOB SUB_EXAMPLES ${CMAKE_CURRENT_SOURCE_DIR}/sub_examples/*)
foreach(EXAMPLE ${SUB_EXAMPLES})
  get_filename_component(EXAMPLE_SELECTED_NAME ${EXAMPLE} NAME)
  option(example_${EXAMPLE_SELECTED_NAME} "example_${EXAMPLE_SELECTED_NAME}" ON)

  if (example_${EXAMPLE_SELECTED_NAME})
    add_subdirectory(${EXAMPLE})
  endif(example_${EXAMPLE_SELECTED_NAME})
endforeach()
