cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

include(FetchContent)

set(BENCHMARK_ENABLE_GTEST_TESTS off)
FetchContent_Declare(
  GoogleBenchmarkContent
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.6.2
)
FetchContent_GetProperties(GoogleBenchmarkContent)
if(NOT googlebenchmarkcontent_POPULATED)
  FetchContent_Populate(GoogleBenchmarkContent)
  add_subdirectory(
    ${googlebenchmarkcontent_SOURCE_DIR}
    ${googlebenchmarkcontent_BINARY_DIR}
    EXCLUDE_FROM_ALL
  )
endif()

add_library(ep_lib STATIC external_polymorphism/print_concept.hh)
target_include_directories(ep_lib PUBLIC external_polymorphism)
set_target_properties(ep_lib PROPERTIES LINKER_LANGUAGE CXX)
add_executable(ep
  external_polymorphism/print.hh
  external_polymorphism/print.cc
  external_polymorphism/main.cc
)
target_link_libraries(ep PRIVATE ep_lib benchmark::benchmark)
target_include_directories(ep PRIVATE external_polymorphism)

add_library(gp_lib STATIC ghasem_polymorphism/print_interface.hh)
target_include_directories(gp_lib PUBLIC ghasem_polymorphism/)
set_target_properties(gp_lib PROPERTIES LINKER_LANGUAGE CXX)
add_executable(gp
  ghasem_polymorphism/print_impl.cc
  ghasem_polymorphism/main.cc
)
target_link_libraries(gp PRIVATE gp_lib benchmark::benchmark)
target_include_directories(gp PRIVATE ghasem_polymorphism/)
