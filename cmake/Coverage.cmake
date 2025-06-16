include_guard()

if (NOT DSA_ENABLE_TESTING OR NOT DSA_ENABLE_COVERAGE)
    return()
endif()

message(STATUS "DSA: Enabled code coverage build")

target_compile_options(build_flags INTERFACE --coverage)
target_link_options(build_flags INTERFACE --coverage)
