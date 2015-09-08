# Candy Eaters full example. Simple game that shows all the features of the library.
project(candy_eaters)

# candy_eaters solution
# ---------------------
set(solution ${PROJECT_NAME})

set(objects_sources
  objects.h
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

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/gfags-master/src/)
target_link_libraries(${solution} gflags)

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/google-glog-master/src/)
target_link_libraries(${solution} google-glog)

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

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/gfags-master/src/)
target_link_libraries(${server} gflags)

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/google-glog-master/src/)
target_link_libraries(${server} google-glog)
