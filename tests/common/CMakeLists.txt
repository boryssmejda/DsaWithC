add_executable(test_common
    ${CMAKE_CURRENT_SOURCE_DIR}/test_error_codes.cpp
)

target_compile_features(test_common PRIVATE cxx_std_23)

target_link_libraries(test_common
    PRIVATE
        dsa::common
        Catch2::Catch2WithMain
)

catch_discover_tests(test_common PROPERTIES LABELS "unit_tests")
