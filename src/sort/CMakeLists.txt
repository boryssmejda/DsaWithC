add_library(sort STATIC
    insertion_sort.c
)

target_include_directories(sort PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

target_link_libraries(sort PRIVATE
    dsa::build_flags
)

add_library(dsa::sort ALIAS sort)
