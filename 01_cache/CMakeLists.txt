cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(arc_cache)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(HEADERS include/cache.hpp include/ideal_cache.hpp include/arc_cache.hpp)
set(SOURCES src/cache.cpp ${HEADERS})
add_executable(arc_cache ${SOURCES})
target_include_directories(arc_cache PUBLIC include)

set(TEST_SRS test/cache_test.cpp ${HEADERS})
add_executable(run_tests ${TEST_SRS})
target_include_directories(run_tests PUBLIC include)
target_link_libraries(run_tests PUBLIC "-lgtest_main -lgtest")

add_custom_target(test
    COMMAND run_tests
    DEPENDS run_tests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(run
    COMMAND arc_cache
    DEPENDS arc_cache
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
