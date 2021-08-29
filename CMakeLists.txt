cmake_minimum_required(VERSION 3.5)

project(examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -fsanitize=address
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors -fsanitize=address")

file(GLOB SUB_EXAMPLES ${CMAKE_CURRENT_SOURCE_DIR}/sub_examples/*)
foreach(EXAMPLE ${SUB_EXAMPLES})
  get_filename_component(EXAMPLE_SELECTED_NAME ${EXAMPLE} NAME)
  option(example_${EXAMPLE_SELECTED_NAME} "example_${EXAMPLE_SELECTED_NAME}" ON)

  if (example_${EXAMPLE_SELECTED_NAME})
    add_subdirectory(${EXAMPLE})
  endif(example_${EXAMPLE_SELECTED_NAME})
endforeach()
