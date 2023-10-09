cmake_minimum_required(VERSION 3.19)
project(AsepriteLib VERSION 0.0.1 LANGUAGES CXX)

option(ASE_LIB_ENABLE_UNIT_TESTS "Enable unit tests" ON)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD 17)

# speed up fetchcontent on consecutive runs
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
add_subdirectory(ext)
add_subdirectory(impl)
add_subdirectory(test)

## copy .clang-format to build directory
#####################################################
configure_file(${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/ COPYONLY)
