add_library(common STATIC
    error_codes.c
)

target_include_directories(common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

target_link_libraries(common PRIVATE
    dsa::build_flags
)

add_library(dsa::common ALIAS common)
