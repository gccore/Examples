cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB HEADER_ONLY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp)
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

add_executable(${PROJECT_NAME} 
  ${HEADER_FILE_ONLY}
  ${SOURCE_FILES}
  ${HEADER_FILES}
)
target_link_directories(${PROJECT_NAME} PUBLIC
  third-party/gmp-6.2.1/lib
)
target_link_libraries(${PROJECT_NAME} PUBLIC
#  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/gmp-6.2.1/lib/libgmp.so
  gmp
)
target_include_directories(${PROJECT_NAME} PUBLIC
  third-party/gmp-6.2.1/include
)
