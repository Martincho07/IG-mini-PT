cmake_minimum_required(VERSION 3.18.0)

add_library(lib geometry.cpp
                transform.cpp
                color.cpp
                image.cpp
                tone_mapping.cpp
                shape.cpp
                camera.cpp
                BRDF.cpp
                file.cpp
                random.cpp
                event.cpp
                parallelization.cpp
                scene.cpp
                AABB.cpp
                BVH.cpp
                integrator.cpp
                light_source.cpp)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lib PUBLIC ${PROJECT_SOURCE_DIR}/external)
