cmake_minimum_required(VERSION 3.0)

project(block-recognizer-superproject)

include(ExternalProject)

ExternalProject_Add(opencv
	URL https://github.com/opencv/opencv/archive/3.3.0.zip
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}" 
)

ExternalProject_Add(lego-sorter
	DEPENDS opencv
	DOWNLOAD_COMMAND "" 
	SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/source" 
	BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/lego-sorter"
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}" 
	INSTALL_COMMAND ""
)


