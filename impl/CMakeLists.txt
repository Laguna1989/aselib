file(GLOB_RECURSE ALLFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(aseprite_lib ${ALLFILES})

if (MSVC)
    target_compile_options(aseprite_lib PRIVATE "/W3")
    target_compile_options(aseprite_lib PUBLIC "/EHsc")
elseif (EMSCRIPTEN)
    target_compile_options(aseprite_lib PRIVATE "-Wall")
    target_compile_options(aseprite_lib PRIVATE "-Wextra")
    target_compile_options(aseprite_lib PRIVATE "-fpermissive")
else ()
    target_compile_options(aseprite_lib PRIVATE "-Wall")
    target_compile_options(aseprite_lib PRIVATE "-Wextra")
    target_compile_options(aseprite_lib PRIVATE "-fpermissive")
endif ()

FetchContent_GetProperties(zlib)
target_link_libraries(aseprite_lib PUBLIC zlibstatic)

target_include_directories(aseprite_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
