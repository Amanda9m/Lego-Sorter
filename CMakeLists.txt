cmake_minimum_required(VERSION 3.0)

project(block-recognizer-superproject)

include(ExternalProject)

ExternalProject_Add(opencv
	URL https://github.com/opencv/opencv/archive/3.3.0.zip
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
		-DWITH_CUDA=OFF 
		-DBUILD_opencv_python3=OFF
		-DBUILD_opencv_python2=OFF
		-DBUILD_EXAMPLES=OFF
		-DBUILD_opencv_apps=OFF
		-DBUILD_DOCS=OFF
		-DBUILD_PERF_TESTS=OFF
		-DBUILD_TESTS=OFF
		-DCMAKE_BUILD_TYPE=RELEASE
)

ExternalProject_Add(tensorflow
	URL https://github.com/tensorflow/tensorflow/archive/v1.4.0.zip
	#SOURCE_SUBDIR tensorflow/contrib/cmake
	CONFIGURE_COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
		<SOURCE_DIR>/tensorflow/contrib/cmake
		"-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
		-DCMAKE_BUILD_TYPE=RELEASE
		-Dtensorflow_BUILD_CC_EXAMPLE=OFF
		-Dtensorflow_BUILD_PYTHON_BINDINGS=OFF
		-Dtensorflow_ENABLE_GRPC_SUPPORT=OFF
		-Dtensorflow_ENABLE_SSL_SUPPORT=OFF
		-Dtensorflow_ENABEL_GPU=OFF
)

ExternalProject_Add(lego-sorter
	DEPENDS opencv tensorflow
	DOWNLOAD_COMMAND "" 
	SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/source" 
	BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/lego-sorter"
	CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}" 
	INSTALL_COMMAND ""
)


