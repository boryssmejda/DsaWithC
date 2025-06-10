add_library(numeric STATIC
    lsqe.c
    polynomial_interpolation.c
    root.c
)

target_include_directories(numeric PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

target_link_libraries(numeric PRIVATE
    dsa::build_flags
)

add_library(dsa::numeric ALIAS numeric)
