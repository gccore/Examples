cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

find_package(SDL2 REQUIRED)

file(GLOB HEADER_ONLY_FILES source/*.hpp)
file(GLOB SOURCE_FILES source/*.cpp)
file(GLOB HEADER_FILES source/*.h)
file(GLOB UTILITY_FILES utils/*.*)

add_executable(${PROJECT_NAME} 
  ${HEADER_ONLY_FILES}
  ${SOURCE_FILES}
  ${HEADER_FILES}
  ${UTILITY_FILES}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${SDL2_LIBRARIES}
  SDL2_image
  pthread
)
target_include_directories(${PROJECT_NAME} PRIVATE
  utils
)
target_compile_definitions(${PROJECT_NAME}
 PUBLIC PROJECT_BINARY_PATH="${CMAKE_CURRENT_BINARY_DIR}")
file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
