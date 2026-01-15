cmake_minimum_required (VERSION 3.20)

project(squiggle DESCRIPTION "Vector Library")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE source_list "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
file(GLOB_RECURSE headers_list "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" )

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ext/Catch2")

add_executable(squiggle_test ${source_list})
set_property(TARGET squiggle_test PROPERTY CXX_STANDARD 23)
target_link_libraries(squiggle_test PRIVATE Catch2::Catch2WithMain)
