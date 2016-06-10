cmake_minimum_required(VERSION 2.6)

add_definitions(-DELPP_THREAD_SAFE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# Building should happen in build/ directory. Add this options before PROJECT
# keyword.
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# about this project
# --------------
project(contest24)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")

# set env
# --------------
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/c24/extern")
include_directories("${PROJECT_SOURCE_DIR}/c24/extern/SFGUI-0.3.0/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add subfolders
# --------------
add_subdirectory(c24)
add_subdirectory(examples)
