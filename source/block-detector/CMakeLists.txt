# CMake build file for block-detector

# Grab all source file within the current directory
file (GLOB sources
	*.c 
	*.h 
)

# Create a static library using the source files
# in the current directory
add_library(block-detector ${sources} requirements.txt)

