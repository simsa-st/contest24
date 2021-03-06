project(communication)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(${PROJECT_NAME}_headers
  server_stream.h
  status.h
  stream_backend_interface.h
  stream_tcp.h
  stream_tcp_client.h
  stream_tcp_server.h
  stream.h)
set(${PROJECT_NAME}_sources
  server_stream.cpp
  status.cpp
  stream_tcp.cpp
  stream_tcp_client.cpp
  stream_tcp_server.cpp
  stream.cpp)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
