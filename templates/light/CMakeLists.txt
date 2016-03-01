cmake_minimum_required(VERSION 2.6)

# Building should happen in build/ directory. Add this options before PROJECT
# keyword.
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# about this project
# --------------
project(contest24___PROJECT_NAME__)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")

# set env
# --------------
include_directories("${PROJECT_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# The game client
project(__PROJECT_NAME__)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(client ${PROJECT_NAME})

set(${client}_sources
  main.cpp
)

add_executable(${client} ${${client}_sources})
target_link_libraries(${client} communication)
target_link_libraries(${client} toolbar)

find_package(gflags REQUIRED)
target_link_libraries(${client} gflags)

find_package(glog REQUIRED)
target_link_libraries(${client} glog)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${client} ${SFML_LIBRARIES})
endif()

# add subfolders
# --------------
add_subdirectory(c24)
