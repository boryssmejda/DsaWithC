add_executable(test_numeric
    ${CMAKE_CURRENT_SOURCE_DIR}/test_lsqe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_root.cpp
)

target_compile_features(test_numeric PRIVATE cxx_std_23)

target_link_libraries(test_numeric
    PRIVATE
        dsa::numeric
        Catch2::Catch2WithMain
)
