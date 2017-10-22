# CMake build file for block-identifier

# Grab all the c source and header files within the
# current directory
file(GLOB sources
	*.c	
	*.h 
)

# Create a static library using the sources
add_library(block-identifier ${sources} requirements.txt)
