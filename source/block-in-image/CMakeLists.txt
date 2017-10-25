# CMake build file for block-in-image

file(GLOB sources
	*.c
)

add_executable(block-in-image ${sources})

add_dependencies(block-in-image png-import)
add_dependencies(block-in-image block-detector)
add_dependencies(block-in-image colour-detector)

target_include_directories(block-in-image PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(block-in-image png-import)
target_link_libraries(block-in-image block-detector)
target_link_libraries(block-in-image colour-detector)
