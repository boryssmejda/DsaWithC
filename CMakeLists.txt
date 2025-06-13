cmake_minimum_required(VERSION 3.31)

project(DsaWithC
    DESCRIPTION "Data structures and algorithms implemented in C language."
    LANGUAGES C CXX)

option(DSA_ENABLE_TESTING "Enable building unit tests for the DSA library" OFF)

include(${CMAKE_SOURCE_DIR}/cmake/ProjectBuildFlags.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

if (DSA_ENABLE_TESTING)
    message(STATUS "DSA: Enabled Testing")
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()
