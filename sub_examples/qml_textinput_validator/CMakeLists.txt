cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

get_filename_component(PROJECT_SELECTED_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_SELECTED_NAME ${PROJECT_SELECTED_NAME})
project(${PROJECT_SELECTED_NAME} LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6)
find_package(Qt${QT_VERSION_MAJOR}
	COMPONENTS
		Quick
		Core
		Gui
	REQUIRED
)

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC on)
set(CMAKE_AUTOUIC on)

add_executable(${PROJECT_NAME} main.cc main.qml res.qrc)
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt::Gui
		Qt::Core
		Qt::Quick
)

