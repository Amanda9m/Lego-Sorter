
file(GLOB sources
	*.cpp
	*.h
	*.c
)

add_library(tf-interface SHARED ${sources})
if (WIN32)
	target_link_libraries(tf-interface ${CMAKE_CURRENT_BINARY_DIR}/tensorflow.dll)
else()
	target_link_libraries(tf-interface ${CMAKE_CURRENT_BINARY_DIR}/libtensorflow.so)
endif()

target_include_directories(tf-interface PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
