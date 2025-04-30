find_package(Catch2 REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sorting)

add_executable(ut
    sorting/test_insertion_sort.cpp
)

target_link_libraries(ut
    PRIVATE
        insertion_sort_algo
        Catch2::Catch2WithMain
)
