cmake_minimum_required(VERSION 3.18.0)

add_library(lib geometry.cpp
                transform.cpp
                color.cpp
                image.cpp
                file.cpp
                error.cpp
                tone_mapping.cpp)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
