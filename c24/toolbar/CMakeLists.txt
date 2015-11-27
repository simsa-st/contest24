project(toolbar)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(${PROJECT_NAME}_headers
  sfgui.h
  print_variables.h)
set(${PROJECT_NAME}_sources
  sfgui.cpp
  print_variables.cpp)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME} sfgui)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2.3 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
