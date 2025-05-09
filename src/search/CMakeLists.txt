add_library(search STATIC
    binary_search.c
)

target_include_directories(search PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

target_link_libraries(search PRIVATE
    dsa::build_flags
)

add_library(dsa::search ALIAS search)
