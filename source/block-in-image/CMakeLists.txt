# CMake build file for block-in-image

file(GLOB sources
	*.c
)

add_executable(block-in-image ${sources})

add_dependencies(block-in-image classifier)

target_include_directories(block-in-image PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(block-in-image classifier)
