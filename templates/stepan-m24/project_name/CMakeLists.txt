# The game client
project(__PROJECT_NAME__)
add_definitions(-DELPP_THREAD_SAFE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -pthread")
set(client ${PROJECT_NAME})

set(objects_sources
  objects/board.cpp
  objects/cell.cpp
  objects/direction.cpp
  objects/player.cpp
  objects/pos.cpp
)
set(${client}_sources
  ${objects_sources}
  toolbar_functions.cpp
  game.cpp
  game_stream.cpp
  main.cpp
)

add_executable(${client} ${${client}_sources})
target_link_libraries(${client} communication)
target_link_libraries(${client} toolbar)
target_link_libraries(${client} gflags-static)
target_link_libraries(${client} sfgui)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${client} ${SFML_LIBRARIES})
endif()
