# Indicate to cmake what version is required to build the 
# project. We should all have a version greater than 3.0
# since the current version is 3.9.
cmake_minimum_required(VERSION 3.0)

# Set our project name
project(lego-sorter)

# Find all dependency packages
find_package(OpenCV REQUIRED)

# Add all the sub projects to the main project
add_subdirectory(classifier)
add_subdirectory(block-in-image)
add_subdirectory(classify-block)
add_subdirectory(camera)

# Add the headers so that they can be edited more easily
add_subdirectory(include)

# Copy trained tf files to output directory
add_custom_target(copy_tf_color_detect
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/../tensorflow_color_detector/tf_files/retrained_graph.pb ${CMAKE_CURRENT_BINARY_DIR}/colour-detect.pb
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/../tensorflow_color_detector/tf_files/retrained_labels.txt ${CMAKE_CURRENT_BINARY_DIR}/colour-labels.txt
)
add_custom_target(copy_tf_block_detect
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/../tensorflow_detect_block/tf_files/retrained_graph.pb ${CMAKE_CURRENT_BINARY_DIR}/block-detect.pb
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/../tensorflow_detect_block/tf_files/retrained_labels.txt ${CMAKE_CURRENT_BINARY_DIR}/block-labels.txt
)
add_custom_target(copy_tf_type_detect
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/../tensorflow_type_detector/tf_files/retrained_graph.pb ${CMAKE_CURRENT_BINARY_DIR}/type-detect.pb
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/../tensorflow_type_detector/tf_files/retrained_labels.txt ${CMAKE_CURRENT_BINARY_DIR}/type-labels.txt
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/package)
add_custom_target(package-app
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/colour-detect.pb ${CMAKE_CURRENT_BINARY_DIR}/package/colour-detect.pb
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/type-detect.pb ${CMAKE_CURRENT_BINARY_DIR}/package/type-detect.pb
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/block-detect.pb ${CMAKE_CURRENT_BINARY_DIR}/package/block-detect.pb
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:classify-block> ${CMAKE_CURRENT_BINARY_DIR}/package/$<TARGET_FILE_NAME:classify-block>
)

add_dependencies(package-app copy_tf_type_detect copy_tf_block_detect copy_tf_color_detect)
