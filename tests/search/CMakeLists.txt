add_executable(test_search
    ${CMAKE_CURRENT_SOURCE_DIR}/test_binary_search.cpp
)

target_compile_features(test_search PRIVATE cxx_std_23)

target_link_libraries(test_search
    PRIVATE
        dsa::search
        Catch2::Catch2WithMain
)
