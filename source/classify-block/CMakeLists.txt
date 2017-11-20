# classify-block

add_executable(classify-block main.c)

add_dependencies(classify-block classifier)

target_include_directories(classify-block PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(classify-block classifier)


