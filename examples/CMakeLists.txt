# Examples.
project(examples)

# tcp_client
set(tcp_client ${PROJECT_NAME}_tcp_client)
set(${tcp_client}_sources tcp_client.cpp)

add_executable(${tcp_client} ${${tcp_client}_sources})
target_link_libraries(${tcp_client} communication)

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/gfags-master/src/)
target_link_libraries(${tcp_client} gflags)

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/google-glog-master/src/)
target_link_libraries(${tcp_client} google-glog)

# tcp_server
set(tcp_server ${PROJECT_NAME}_tcp_server)
set(${tcp_server}_sources tcp_server.cpp)

add_executable(${tcp_server} ${${tcp_server}_sources})
target_link_libraries(${tcp_server} communication)

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/gfags-master/src/)
target_link_libraries(${tcp_server} gflags)

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/google-glog-master/src/)
target_link_libraries(${tcp_server} google-glog)

# add subfolders
# --------------
add_subdirectory(candy_eaters)
