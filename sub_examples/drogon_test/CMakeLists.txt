cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(${PROJECT_NAME} "ghasem")

#list(APPEND CMAKE_PREFIX_PATH "/home/ghasem/Documents/src/drogon/binary/debug")
#find_package(Drogon REQUIRED)

#file(GLOB SUB_EXAMPLES ${CMAKE_CURRENT_SOURCE_DIR}/sub_examples/*)
#foreach(EXAMPLE ${SUB_EXAMPLES})
#  get_filename_component(EXAMPLE_SELECTED_NAME ${EXAMPLE} NAME)
#  option(example_${EXAMPLE_SELECTED_NAME} "example_${EXAMPLE_SELECTED_NAME}" ON)

#  if (example_${EXAMPLE_SELECTED_NAME})
#    add_subdirectory(${EXAMPLE})
#  endif(${EXAMPLE}_example)
#endforeach()
