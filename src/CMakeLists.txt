add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/list)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/numeric)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/search)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sort)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utility)

add_library(dsa
    $<TARGET_OBJECTS:common>
    $<TARGET_OBJECTS:list>
    $<TARGET_OBJECTS:numeric>
    $<TARGET_OBJECTS:search>
    $<TARGET_OBJECTS:sort>
    $<TARGET_OBJECTS:utility>
)

target_include_directories(dsa PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/>
)

target_link_libraries(dsa
    PRIVATE
        dsa::build_flags
)

add_library(dsa::dsa ALIAS dsa)
