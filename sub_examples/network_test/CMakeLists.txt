cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)


file(GLOB SUB_EXAMPLES sub_examples/*)
foreach(example ${SUB_EXAMPLES})
  get_filename_component(EXAMPLE_SELECTED_NAME ${example} NAME)
  option(example_${EXAMPLE_SELECTED_NAME} "example_${EXAMPLE_SELECTED_NAME}" off)

  if (example_${EXAMPLE_SELECTED_NAME})
    add_subdirectory(${example})
  endif(example_${EXAMPLE_SELECTED_NAME})
endforeach()
