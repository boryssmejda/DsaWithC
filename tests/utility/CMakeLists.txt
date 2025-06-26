add_executable(test_utility
    test_count_if.cpp
    test_find_if_not.cpp
    test_for_each.cpp
    test_max_element.cpp
    test_min_element.cpp
    test_reverse.cpp
)

target_compile_features(test_utility PRIVATE cxx_std_23)

target_link_libraries(test_utility
    PRIVATE
        dsa::utility
        Catch2::Catch2WithMain
)

catch_discover_tests(test_utility PROPERTIES LABELS "unit_tests")
