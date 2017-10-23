# CMake build file for block-detector

# Grab all source file within the current directory
file (GLOB sources
	*.c 
	*.h 
	*.cpp 
)

# Create a static library using the source files
# in the current directory
add_library(block-detector ${sources} requirements.txt)

target_include_directories(block-detector PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_include_directories(block-detector PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(block-detector ${OPENCV_LIBRARIES})
