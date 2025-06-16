include_guard()

if (NOT DSA_ENABLE_TESTING OR NOT DSA_ENABLE_COVERAGE)
    return()
endif()

message(STATUS "DSA: Enabled code coverage build")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
elseif(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(FATAL_ERROR "Code coverage requires Debug build type")
endif()

if (NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Code coverage is only supported with GCC. Try setting -DCMAKE_C_COMPILER=gcc")
endif()

target_compile_options(build_flags INTERFACE --coverage)
target_link_options(build_flags INTERFACE --coverage)

find_program(GCOVR_PATH NAMES gcovr REQUIRED)

set(COVERAGE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/coverage-report/)

add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} --build . --target all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND ${CMAKE_COMMAND} -E make_directory ${COVERAGE_OUTPUT_DIR}
    COMMAND ${GCOVR_PATH}
        --root ${CMAKE_SOURCE_DIR}
        --object-directory ${CMAKE_BINARY_DIR}
        --html
        --html-details
        --html-title "DSA Code Coverage Report"
        --html-self-contained
        --output ${COVERAGE_OUTPUT_DIR}/coverage.html
        --delete
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating code coverage report with gcovr"
)
