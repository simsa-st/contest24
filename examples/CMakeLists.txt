# Examples.
project(examples)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# tcp_client
set(tcp_client ${PROJECT_NAME}_tcp_client)
set(${tcp_client}_sources tcp_client.cpp)

add_executable(${tcp_client} ${${tcp_client}_sources})
target_link_libraries(${tcp_client} communication)

target_link_libraries(${tcp_client} gflags-static)

# tcp_server
set(tcp_server ${PROJECT_NAME}_tcp_server)
set(${tcp_server}_sources tcp_server.cpp)

add_executable(${tcp_server} ${${tcp_server}_sources})
target_link_libraries(${tcp_server} communication)

target_link_libraries(${tcp_server} gflags-static)

# add subfolders
# --------------
add_subdirectory(candy_eaters)
