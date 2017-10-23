# CMake build file for the colour-detector library

# This grabs all c files and headers in the current directory
# and stores them in the sources variable
file(GLOB sources
	*.c
	*.h
)

# This creates a library project using the sources files
add_library(colour-detector ${sources} requirements.txt)

target_include_directories(colour-detector PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
