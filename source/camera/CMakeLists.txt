
if ("${CMAKE_SYSTEM}" STREQUAL "Linux")
	add_library(camera STATIC camera.c)

	target_include_directories(camera PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
endif()
