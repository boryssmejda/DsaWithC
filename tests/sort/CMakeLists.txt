add_executable(test_sorting
    ${CMAKE_CURRENT_SOURCE_DIR}/test_insertion_sort.cpp
)

target_compile_features(test_sorting PRIVATE cxx_std_23)

target_link_libraries(test_sorting
    PRIVATE
        dsa::sort
        Catch2::Catch2WithMain
)
