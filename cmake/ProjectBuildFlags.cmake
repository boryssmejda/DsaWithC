add_library(build_flags INTERFACE)
add_library(dsa::build_flags ALIAS build_flags)

target_compile_features(build_flags
    INTERFACE
        c_std_23)

target_compile_options(build_flags
    INTERFACE
        -Werror
        -Wall
        -Wextra
        -Wshadow
        -Wcast-align
        -Wunused
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -Wimplicit-fallthrough)

