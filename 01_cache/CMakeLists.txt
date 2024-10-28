cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(arc_cache)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCES src/cache.cpp include/cache.hpp include/ideal_cache.hpp)
add_executable(arc_cache ${SOURCES})
target_include_directories(arc_cache PUBLIC include)
