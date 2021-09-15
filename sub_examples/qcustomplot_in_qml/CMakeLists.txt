cmake_minimum_required(VERSION 3.5)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 COMPONENTS PrintSupport Widgets Charts Qml Quick Gui Core REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport Widgets Charts Qml Quick Gui Core REQUIRED)
find_package(Qt5 COMPONENTS PrintSupport Widgets Charts Qml Quick Gui Core REQUIRED)

file(GLOB HEADER_ONLY_FILES source/*.hpp)
file(GLOB SOURCE_FILES      source/*.cpp)
file(GLOB HEADER_FILES      source/*.h)
file(GLOB QML_FILES         source/*.qml)
file(GLOB QRC_FILES         source/*.qrc)

add_executable(${PROJECT_NAME} 
	${HEADER_FILE_ONLY}
	${SOURCE_FILES}
	${HEADER_FILES}
	${QRC_FILES}
	${QML_FILES}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt5::PrintSupport
	Qt5::Widgets
	Qt5::Charts
	Qt5::Quick
	Qt5::Core
	Qt5::Qml
	Qt5::Gui
)
