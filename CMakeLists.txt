cmake_minimum_required(VERSION 3.18.0)
project(informaticagrafica VERSION 0.1.0 DESCRIPTION "informatica grafica")

set (CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

add_subdirectory(lib)

add_library(planet practica1/planet.cpp)
target_link_libraries(planet LINK_PUBLIC lib)

add_executable(practica1 practica1/main.cpp)
target_link_libraries(practica1 LINK_PUBLIC lib planet)

add_executable(tone_mapper tone_mapper/main.cpp)
target_link_libraries(tone_mapper LINK_PUBLIC lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
