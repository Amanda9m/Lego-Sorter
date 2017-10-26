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

# Add the headers so that they can be edited more easily
add_subdirectory(include)
