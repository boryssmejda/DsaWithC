add_library(dsa_build_flags INTERFACE)

target_compile_features(dsa_build_flags
    INTERFACE
        c_std_23)

target_compile_options(dsa_build_flags
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

