
file(GLOB sources
	*.c
)

add_executable(driver ${sources})

add_dependencies(driver classifier camera set_management)

target_link_libraries(driver classifier camera set_management)
target_include_directories(driver PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)
