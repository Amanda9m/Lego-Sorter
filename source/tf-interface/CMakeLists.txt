
file(GLOB sources
	*.cpp
	*.h
	*.c
)

add_library(tf-interface SHARED ${sources})

target_link_libraries(tf-interface ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow.so)

target_include_directories(tf-interface PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
