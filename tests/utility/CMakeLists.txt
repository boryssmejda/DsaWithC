add_executable(test_utility
    ${CMAKE_CURRENT_SOURCE_DIR}/test_for_each.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_max_element.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_min_element.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_reverse.cpp
)

target_compile_features(test_utility PRIVATE cxx_std_23)

target_link_libraries(test_utility
    PRIVATE
        dsa::utility
        Catch2::Catch2WithMain
)

add_test(NAME test_utility COMMAND test_utility)
set_tests_properties(test_utility PROPERTIES LABELS "unit_tests")
