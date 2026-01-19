cmake_minimum_required (VERSION 3.20)

project(squiggle DESCRIPTION "Vector Library")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE source_list "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
file(GLOB_RECURSE headers_list "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" )

add_library( squiggle INTERFACE )
target_include_directories( squiggle INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include" )


set(SQUIGGLE_TEST ON CACHE BOOL "Build Unit Tests")

if ( SQUIGGLE_TEST )
    if ( NOT TARGET Catch2::Catch2WithMain )
        
        include(FetchContent)
        FetchContent_Declare(
            Catch2
            GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
            GIT_TAG        88abf9bf325c798c33f54f6b9220ef885b267f4f # v3.12.0
        )

        FetchContent_MakeAvailable(Catch2)
        MESSAGE(INFO " [ut-units] Fetching Catch2")
    endif()

    MESSAGE(INFO " [ut-units] Building Unit Tests")

    add_executable(squiggle_test ${source_list})
    set_property(TARGET squiggle_test PROPERTY CXX_STANDARD 23)
    target_link_libraries(squiggle_test PRIVATE Catch2::Catch2WithMain squiggle)
endif()