# Interface headers CMake file

file(GLOB sources
	*.h
)

add_library(include-headers INTERFACE)

target_sources(include-headers ${sources})


