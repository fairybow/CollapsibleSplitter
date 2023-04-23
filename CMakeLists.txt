cmake_minimum_required(VERSION 3.16)

project(CollapsibleSplitter VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS WebChannel WebEngineCore WebEngineWidgets Widgets)

qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(CollapsibleSplitter

	Layout.hpp
	MainWindow.hpp
	Preview.hpp
	Splitter.hpp
	SplitterHandle.hpp
	TrueSplitter.hpp

	Main.cpp

	Preview.qrc
)

target_link_libraries(CollapsibleSplitter PRIVATE Qt6::WebChannel)
target_link_libraries(CollapsibleSplitter PRIVATE Qt6::WebEngineCore)
target_link_libraries(CollapsibleSplitter PRIVATE Qt6::WebEngineWidgets)
target_link_libraries(CollapsibleSplitter PRIVATE Qt6::Widgets)

install(TARGETS CollapsibleSplitter RUNTIME)
