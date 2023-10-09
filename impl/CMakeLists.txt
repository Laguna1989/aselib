file(GLOB_RECURSE ALLFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(aselib ${ALLFILES})

if (MSVC)
    target_compile_options(aselib PRIVATE "/W3")
    target_compile_options(aselib PUBLIC "/EHsc")
else ()
    target_compile_options(aselib PRIVATE "-Wall")
    target_compile_options(aselib PRIVATE "-Wextra")
    target_compile_options(aselib PRIVATE "-fpermissive")
endif ()

FetchContent_GetProperties(zlib)
target_link_libraries(aselib PUBLIC zlibstatic)

target_include_directories(aselib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
