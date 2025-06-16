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

target_compile_options(build_flags INTERFACE --coverage)
target_link_options(build_flags INTERFACE --coverage)

find_program(GCOVR_PATH gcovr REQUIRED)

add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} --build . --target all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND ${CMAKE_COMMAND} -E make_directory coverage-report
    COMMAND ${GCOVR_PATH}
        --root ${CMAKE_SOURCE_DIR}
        --object-directory ${CMAKE_BINARY_DIR}
        --html
        --html-details
        --html-title "DSA Code Coverage Report"
        --html-self-contained
        --output coverage-report/coverage.html
        --delete
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating code coverage report with gcovr"
)
