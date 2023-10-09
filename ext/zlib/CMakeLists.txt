message(STATUS "Fetching zlib")

# Like `FetchContent_MakeAvailable` but passes EXCLUDE_FROM_ALL to `add_subdirectory`.
# This is needed because zlib examples assumes it is the top level cmake file, which
# is not the case when using FetchContent
macro(FetchContent_MakeAvailableExcludeFromAll)
    foreach (contentName IN ITEMS ${ARGV})
        string(TOLOWER ${contentName} contentNameLower)
        FetchContent_GetProperties(${contentName})
        if (NOT ${contentNameLower}_POPULATED)
            FetchContent_Populate(${contentName})
            if (EXISTS ${${contentNameLower}_SOURCE_DIR}/CMakeLists.txt)
                add_subdirectory(${${contentNameLower}_SOURCE_DIR}
                        ${${contentNameLower}_BINARY_DIR} EXCLUDE_FROM_ALL)
            endif ()
        endif ()
    endforeach ()
endmacro()

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0135 OLD)
include(FetchContent)

file(WRITE "${CMAKE_BINARY_DIR}/_deps/zlib-patch.cmake" "
    file(READ \"${CMAKE_BINARY_DIR}/_deps/zlib-src/CMakeLists.txt\" _content)
    string(REPLACE \"cmake_minimum_required(VERSION 2.4.4)\"
        \"cmake_minimum_required(VERSION 3.24)\" _content \"\${_content}\")
    file(WRITE \"${CMAKE_BINARY_DIR}/_deps/zlib-src/CMakeLists.txt\" \"\${_content}\")
")

FetchContent_Declare(zlib
    URL https://www.zlib.net/zlib-1.2.13.tar.gz
    https://www.zlib.net/fossils/zlib-1.2.13.tar.gz
    https://github.com/madler/zlib/releases/download/v1.2.13/zlib-1.2.13.tar.gz
    URL_HASH MD5=9b8aa094c4e5765dabf4da391f00d15c
    PATCH_COMMAND ${CMAKE_COMMAND} -P "${CMAKE_BINARY_DIR}/_deps/zlib-patch.cmake"
)
FetchContent_MakeAvailableExcludeFromAll(zlib)

add_library(ZLIB::ZLIB ALIAS zlibstatic)
target_include_directories(zlibstatic INTERFACE ${zlib_BINARY_DIR} ${zlib_SOURCE_DIR})

# 1. Set the variables that are usually set by FindZLIB.cmake.
# 2. Add the module that stubs out `find_package(ZLIB ...)` calls.
set(ZLIB_FOUND ON PARENT_SCOPE)
set(ZLIB_LIBRARY ZLIB::ZLIB PARENT_SCOPE)
set(ZLIB_LIBRARIES ZLIB::ZLIB PARENT_SCOPE)
set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR} PARENT_SCOPE)
set(ZLIB_INCLUDE_DIRS ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR} PARENT_SCOPE)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/CMake" PARENT_SCOPE)
