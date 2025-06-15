cmake_minimum_required(VERSION 3.31)

project(DsaWithC
    DESCRIPTION "Data structures and algorithms implemented in C language."
    LANGUAGES C CXX)

include(CMakeDependentOption)

option(DSA_ENABLE_TESTING "Enable building unit tests for the DSA library" OFF)
cmake_dependent_option(DSA_ENABLE_COVERAGE "Enable code coverage generation for the DSA library" OFF DSA_ENABLE_TESTING OFF)

include(${CMAKE_SOURCE_DIR}/cmake/ProjectBuildFlags.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

if (DSA_ENABLE_TESTING)
    message(STATUS "DSA: Enabled Testing")
    enable_testing()
    include(cmake/Coverage.cmake)
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()
