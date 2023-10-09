file(GLOB TESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(aselib_test ${TESTFILES})
target_link_libraries(aselib_test PRIVATE
        aselib
        Catch2::Catch2
)

FetchContent_GetProperties(catch2)
target_include_directories(aselib_test PUBLIC ${catch2_SOURCE_DIR}/include)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(aselib_test PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(aselib_test PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()
