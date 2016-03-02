cmake_minimum_required(VERSION 2.6)

# Building should happen in build/ directory. Add this options before PROJECT
# keyword.
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# about this project
# --------------
project(contest24___PROJECT_NAME__)

# set env
# --------------
include_directories("${PROJECT_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# --------------
add_subdirectory(c24)
add_subdirectory(__PROJECT_NAME__)
