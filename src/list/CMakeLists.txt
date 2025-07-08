add_library(list STATIC
    slist.c
)

target_include_directories(list PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

target_link_libraries(list PRIVATE
    dsa::build_flags
)

add_library(dsa::list ALIAS list)
