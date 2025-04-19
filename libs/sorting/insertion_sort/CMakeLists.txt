add_library(insertion_sort_algo
    insertion_sort.h
    insertion_sort.c
)

target_include_directories(insertion_sort_algo
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(insertion_sort_algo
    PRIVATE
        build_flags)
