cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(A)
add_subdirectory(B)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-fsanitize=address -Wall -Wextra -Wpedantic -pedantic-errors -O2")
endif()

file(GLOB HEADER_ONLY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp)
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

add_executable(${PROJECT_NAME} 
  ${HEADER_FILE_ONLY}
  ${SOURCE_FILES}
  ${HEADER_FILES}
)
target_link_libraries(${PROJECT_NAME} PUBLIC
 plugin::A
 plugin::B
)
