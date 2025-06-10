include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        2b60af89e23d28eefc081bc930831ee9d45ea58b # v3.8.1
)

FetchContent_MakeAvailable(Catch2)

include(Catch)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/numeric)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/search)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sort)
