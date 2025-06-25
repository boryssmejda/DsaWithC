add_library(utility STATIC
    find_if.c
    for_each.c
    max_element.c
    min_element.c
    reverse.c
)

target_include_directories(utility PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

target_link_libraries(utility PRIVATE
    dsa::build_flags
)

add_library(dsa::utility ALIAS utility)
