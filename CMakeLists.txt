cmake_minimum_required(VERSION 3.18.0)
project(informaticagrafica VERSION 0.1.0 DESCRIPTION "informatica grafica")

set (CMAKE_CXX_STANDARD 11)
# set (CMAKE_CXX_FLAGS "-pthread -ffast-math -O3")
set (CMAKE_CXX_FLAGS "-pthread -O3")

include(CTest)
enable_testing()


# Add lib libray
add_subdirectory(lib)


# Catch2 testing
add_executable(unit_tests test/main.cpp
                          test/test_factorial.cpp
                          test/test_hello.cpp
                          test/geometry_test.cpp
                          test/color_test.cpp)
target_link_libraries(unit_tests LINK_PUBLIC lib)

# Practica 1
add_library(planet practica1/planet.cpp)
target_link_libraries(planet LINK_PUBLIC lib)

add_executable(practica1 practica1/main.cpp)
target_link_libraries(practica1 LINK_PUBLIC lib planet)

# Tone mapper
add_executable(tone_mapper tone_mapper/main.cpp)
target_link_libraries(tone_mapper LINK_PUBLIC lib)

# Ray Tracer
add_executable(ray_tracer ray_tracer/main.cpp)
target_link_libraries(ray_tracer LINK_PUBLIC lib)

# Path Tracer
add_executable(path_tracer path_tracer/main.cpp)
target_link_libraries(path_tracer LINK_PUBLIC lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
