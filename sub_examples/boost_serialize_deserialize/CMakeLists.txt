cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

file(GLOB HEADER_ONLY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp)
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

add_executable(${PROJECT_NAME} 
  ${HEADER_FILE_ONLY}
  ${SOURCE_FILES}
  ${HEADER_FILES}
)
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED on
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    boost_iostreams
    boost_serialization
    stdc++fs
)
