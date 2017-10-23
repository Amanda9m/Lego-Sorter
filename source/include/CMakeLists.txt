# Interface headers CMake file

file(GLOB sources
	*.h
)

add_library(include-headers STATIC ${sources})
set_target_properties(include-headers PROPERTIES LINKER_LANGUAGE CXX)


