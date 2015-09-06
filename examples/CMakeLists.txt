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
