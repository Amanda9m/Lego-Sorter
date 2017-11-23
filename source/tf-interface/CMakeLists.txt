
file(GLOB sources
	*.cpp
	*.h
	*.c
)

add_library(tf-interface ${sources})

find_package(TensorflowCC)

if (${TENSORFLOWCC_FOUND})
	target_link_libraries(tf-interface ${TENSORFLOWCC_LIBRARIES})
	target_include_directories(tf-interface PRIVATE ${TENSORFLOWCC_INCLUDE_DIRS})
	message(STATUS ${TENSORFLOWCC_INCLUDE_DIRS})
else()
	target_include_directories(tf-interface PRIVATE 
		d:/Projects/install/se101-project-linux/include/tensorflow 
		/mnt/d/Projects/install/se101-project-linux/include/tensorflow)
	message(STATUS "Using hardcoded tf include dirs")
endif()

target_include_directories(tf-interface PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
