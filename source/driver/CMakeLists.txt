
file(GLOB sources
	*.c
	LED.py
)

add_executable(driver ${sources})

add_dependencies(driver classifier set_management)

target_link_libraries(driver classifier set_management)
target_include_directories(driver PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)

configure_file(LED.py ${CMAKE_CURRENT_BINARY_DIR}/LED.py COPYONLY)
configure_file(${CMAKE_CURRENT_LIST_DIR}/../set_management/user_input ${CMAKE_CURRENT_BINARY_DIR}/user_input COPYONLY)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/../colour-detect.pb ${CMAKE_CURRENT_BINARY_DIR}/colour-detect.pb COPYONLY)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/../block-detect.pb ${CMAKE_CURRENT_BINARY_DIR}/block-detect.pb COPYONLY)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/../type-detect.pb ${CMAKE_CURRENT_BINARY_DIR}/type-detect.pb COPYONLY)

if (NOT WIN32)
	add_dependencies(driver camera)
	target_link_libraries(driver camera)
endif()
