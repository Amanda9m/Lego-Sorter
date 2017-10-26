# classifier CMake build file

file(GLOB sources
	*.h
	*.c
	*.cpp
)

add_library(classifier ${sources})

target_include_directories(classifier PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(classifier PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(classifier ${OpenCV_LIBRARIES})

