add_library(sorting
    insertion_sort.c
)

target_include_directories(sorting PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/>
)

target_link_libraries(sorting PRIVATE
    dsa_build_flags
)

add_library(dsa::sorting ALIAS sorting)
