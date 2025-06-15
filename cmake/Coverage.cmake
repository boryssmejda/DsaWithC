include_guard()

if (NOT DSA_ENABLE_TESTING OR NOT DSA_ENABLE_COVERAGE)
    return()
endif()

message(STATUS "DSA: Enabled code coverage build")

include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

check_cxx_compiler_flag("-ftest-coverage" CXX_COMPILER_SUPPORT_TEST_COVERAGE)
check_cxx_compiler_flag("-fprofile-arcs" CXX_COMPILER_SUPPORT_PROFILE_ARCS)

check_c_compiler_flag("-ftest-coverage" C_COMPILER_SUPPORT_TEST_COVERAGE)
check_c_compiler_flag("-fprofile-arcs" C_COMPILER_SUPPORT_PROFILE_ARCS)

check_cxx_compiler_flag("--coverage" CXX_COMPILER_SUPPORTS_COVERAGE)
check_c_compiler_flag("--coverage" C_COMPILER_SUPPORTS_COVERAGE)

if (CXX_COMPILER_SUPPORTS_COVERAGE AND C_COMPILER_SUPPORTS_COVERAGE)
    target_compile_options(build_flags INTERFACE --coverage)
    target_link_options(build_flags INTERFACE --coverage)
    return()
endif()

target_compile_options(build_flags INTERFACE -ftest-coverage)
target_link_options(build_flags INTERFACE -ftest-coverage)
