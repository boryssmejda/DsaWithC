cmake_minimum_required(VERSION 3.31)

project(DsaWithC
    DESCRIPTION "Data structures and algorithms implemented in C language."
    LANGUAGES C CXX)

include(${CMAKE_SOURCE_DIR}/cmake/ProjectBuildFlags.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

