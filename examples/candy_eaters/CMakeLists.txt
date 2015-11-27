# Candy Eaters full example. Simple game that shows all the features of the library.
project(candy_eaters)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# candy_eaters solution
# ---------------------
set(solution ${PROJECT_NAME})

set(objects_sources
  objects.h
  objects/board.cpp
  objects/cell.cpp
  objects/player.cpp
  objects/pos.cpp
)
set(${solution}_sources
  ${objects_sources}
  game.cpp
  game_stream.cpp
  main.cpp
)

add_executable(${solution} ${${solution}_sources})
target_link_libraries(${solution} communication)
target_link_libraries(${solution} toolbar)

find_package(gflags REQUIRED)
target_link_libraries(${solution} gflags)

find_package(glog REQUIRED)
target_link_libraries(${solution} glog)

target_link_libraries(${solution} sfgui)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${solution} ${SFML_LIBRARIES})
endif()

# candy_eaters server
# -------------------
set(server ${PROJECT_NAME}_server)

set(server_objects_sources
  objects/board.cpp
  objects/player.cpp
  objects/pos.cpp
  objects/server_cell.cpp
  objects/server_move.cpp
  objects/server_player.cpp
  server_objects.h
)
set(${server}_sources
  ${server_objects_sources}
  server_game.cpp
  main_server.cpp
)

add_executable(${server} ${${server}_sources})
target_link_libraries(${server} communication)

find_package(gflags REQUIRED)
target_link_libraries(${server} gflags)

find_package(glog REQUIRED)
target_link_libraries(${server} glog)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${server} ${SFML_LIBRARIES})
endif()
