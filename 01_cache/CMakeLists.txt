cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(cache)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_library(base_cache INTERFACE)
target_compile_options(base_cache INTERFACE ${CMAKE_CXX_FLAGS} -Wall -Wextra -O3)
target_include_directories(base_cache INTERFACE include)

set(HEADERS_ARC include/cache.hpp include/arc_cache.hpp)
set(SOURCES_ARC src/arc_cache.cpp ${HEADERS_ARC})
add_library(arc STATIC ${SOURCES_ARC})
target_link_libraries(arc PUBLIC base_cache)
target_include_directories(arc PUBLIC include)
add_executable(arc_cache src/main_arc.cpp)
target_link_libraries(arc_cache arc)

set(HEADERS_IDEAL include/cache.hpp include/ideal_cache.hpp)
set(SOURCES_IDEAL src/ideal_cache.cpp ${HEADERS_IDEAL})
add_library(ideal STATIC ${SOURCES_IDEAL})
target_link_libraries(ideal PUBLIC base_cache)
target_include_directories(ideal PUBLIC include)
add_executable(ideal_cache src/main_ideal.cpp)
target_link_libraries(ideal_cache ideal)

set(TEST_SRS test/cache_test.cpp src/arc_cache.cpp src/ideal_cache.cpp ${HEADERS_ARC} ${HEADERS_IDEAL})
add_executable(run_tests ${TEST_SRS})
target_include_directories(run_tests PUBLIC include)
target_link_libraries(run_tests PUBLIC arc ideal)
target_link_libraries(run_tests PUBLIC -lgtest_main -lgtest)

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
