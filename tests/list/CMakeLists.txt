add_executable(test_list
    test_slist.cpp
)

target_compile_features(test_list PRIVATE cxx_std_23)

target_link_libraries(test_list
    PRIVATE
        dsa::list
        Catch2::Catch2WithMain
)

catch_discover_tests(test_list PROPERTIES LABELS "unit_tests")
