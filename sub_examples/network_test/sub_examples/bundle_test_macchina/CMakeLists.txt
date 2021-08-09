cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

set(POCO_MODULE "/home/ghasem/Documents/src/poco/ghasem/install/lib/cmake/Poco")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} ${POCO_MODULE}")

file(GLOB HEADER_ONLY_FILES source/*.hpp)
file(GLOB SOURCE_FILES source/*.cpp)
file(GLOB HEADER_FILES source/*.h)
file(GLOB BUNDLE_FILES bundle/*.xml)

add_library(${PROJECT_NAME} SHARED
  ${HEADER_ONLY_FILES}
  ${SOURCE_FILES}
  ${HEADER_FILES}
  ${BUNDLE_FILES}
)
target_include_directories(${PROJECT_NAME} PRIVATE
  /home/ghasem/Documents/src/poco/ghasem/install/include
  /home/ghasem/Documents/src/macchina.io/ghasem/install/include
)
target_link_directories(${PROJECT_NAME} PRIVATE
  /home/ghasem/Documents/src/poco/ghasem/install/lib
  /home/ghasem/Documents/src/macchina.io/ghasem/install/lib
)
target_link_libraries(${PROJECT_NAME} PRIVATE
 PocoOSP PocoZip PocoUtil PocoXML PocoJSON PocoFoundation
)
