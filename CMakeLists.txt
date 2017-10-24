cmake_minimum_required(VERSION 3.0)

project(block-recognizer-superproject)

include(ExternalProject)

ExternalProject_Add(opencv
	URL https://github.com/opencv/opencv/archive/3.3.0.zip
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}" 
)

ExternalProject_Add(zlib
	URL https://github.com/madler/zlib/archive/v1.2.11.tar.gz
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(libpng
	DEPENDS zlib
	URL https://github.com/glennrp/libpng/archive/v1.6.33.tar.gz
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(lego-sorter
	DEPENDS opencv
	DOWNLOAD_COMMAND "" 
	SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/source" 
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}" 
	INSTALL_COMMAND ""
)


