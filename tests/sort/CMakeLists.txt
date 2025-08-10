add_executable(test_sort
    ${CMAKE_CURRENT_SOURCE_DIR}/test_insertion_sort.cpp
)

target_compile_features(test_sort PRIVATE cxx_std_23)

target_link_libraries(test_sort
    PRIVATE
        dsa::sort
        Catch2::Catch2WithMain
)

add_test(NAME test_sort COMMAND test_sort)
set_tests_properties(test_sort PROPERTIES LABELS "unit_tests")
