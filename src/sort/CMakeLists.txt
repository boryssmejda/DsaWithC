add_library(sort
    insertion_sort.c
)

target_include_directories(sort PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/>
)

target_link_libraries(sort PRIVATE
    dsa::build_flags
)

add_library(dsa::sort ALIAS sort)
