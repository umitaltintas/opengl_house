cmake_minimum_required(VERSION 3.10)
project(graph_hw1)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)


set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)


set(PROJECT_SOURCES
        src/main.cpp
        src/imageloader.cpp)

set(PROJECT_HEADERS
        ${PROJECT_INCLUDE_DIR}/imageloader.hpp
        )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${PROJECT_INCLUDE_DIR} )

add_executable(app ${PROJECT_SOURCES})
target_link_libraries(app ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )


















