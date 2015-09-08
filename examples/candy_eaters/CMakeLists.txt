# Candy Eaters full example. Simple game that shows all the features of the library.
project(candy_eaters)

set(objects_sources
  objects.h
  objects/player.cpp
  objects/pos.cpp
)

# candy_eaters solution
set(solution ${PROJECT_NAME})
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
