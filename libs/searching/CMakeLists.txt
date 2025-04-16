add_library(binary_search_algo
    binary_search.h
    binary_search.c
)

target_include_directories(binary_search_algo
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(binary_search_algo
    PRIVATE
        build_flags)