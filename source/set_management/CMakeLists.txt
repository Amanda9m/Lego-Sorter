
file(GLOB sources
	*.c
	*.h
)

add_library(set_management ${sources})

target_include_directories(set_management PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)
