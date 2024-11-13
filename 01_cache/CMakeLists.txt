cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(arc_cache)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -ffast-math -gdwarf-4 -msse -msse2 -mfpmath=sse -march=native")

set(HEADERS_ARC include/cache.hpp include/arc_cache.hpp)
set(SOURCES_ARC src/main_arc.cpp src/arc_cache.cpp ${HEADERS_ARC})
add_executable(arc_cache ${SOURCES_ARC})
target_include_directories(arc_cache PUBLIC include)

set(HEADERS_IDEAL include/cache.hpp include/ideal_cache.hpp)
set(SOURCES_IDEAL src/main_ideal.cpp src/ideal_cache.cpp ${HEADERS_IDEAL})
add_executable(ideal_cache ${SOURCES_IDEAL})
target_include_directories(ideal_cache PUBLIC include)

set(TEST_SRS test/cache_test.cpp src/arc_cache.cpp src/ideal_cache.cpp ${HEADERS_ARC} ${HEADERS_IDEAL})
add_executable(run_tests ${TEST_SRS})
target_include_directories(run_tests PUBLIC include)
target_link_libraries(run_tests PUBLIC "-lgtest_main -lgtest")

add_custom_target(test
    COMMAND run_tests
    DEPENDS run_tests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(run_arc
    COMMAND arc_cache
    DEPENDS arc_cache
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(run_ideal
    COMMAND ideal_cache
    DEPENDS ideal_cache
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
