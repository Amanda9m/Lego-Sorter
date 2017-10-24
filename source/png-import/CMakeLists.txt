# CMake project file for png-import

file(GLOB sources
	*.cpp
	*.h
)

add_library(png-import ${sources})

target_link_libraries(png-import ${OpenCV_LIBRARIES})
target_include_directories(png-import PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(png-import PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

