message(STATUS "Fetching catch2")

file(GLOB TESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(aseprite_lib_test ${TESTFILES})
target_link_libraries(aseprite_lib_test PRIVATE
        aseprite_lib
        Catch2::Catch2
)

FetchContent_GetProperties(catch2)
target_include_directories(aseprite_lib_test PUBLIC ${catch2_SOURCE_DIR}/include)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(aseprite_lib_test PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(aseprite_lib_test PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()
