
file(GLOB sources
	*.c
)

add_executable(driver ${sources})

add_dependencies(driver classifier set_management)

target_link_libraries(driver classifier set_management)
target_include_directories(driver PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)

if (NOT WIN32)
	add_dependencies(driver camera)
	target_link_libraries(driver camera)
endif()
