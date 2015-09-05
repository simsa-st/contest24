project(communication)

set(${PROJECT_NAME}_headers
  stream_backend_interface.h
  stream.h)
set(${PROJECT_NAME}_sources
  stream.cpp)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

include_directories(${CMAKE_SOURCE_DIR}/c24/extern/google-glog-master/src/)
target_link_libraries(${PROJECT_NAME} google-glog)
