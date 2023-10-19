[![Build Status](https://github.com/Laguna1989/aselib/actions/workflows/test_verification.yml/badge.svg)](https://github.com/Laguna1989/aselib/actions/workflows/unittests.yml)

# About

This is a c++17 library to parse `*.aseprite` files. Please check out and
support [this awesome pixelart program](https://www.aseprite.org/)!

# Limitations

* No support for grayscale or indexed image types. Only RGBA files are supported.
    * Grayscale and indexed files will not parse.
* Only "Normal" Blend Mode is supported.
    * Blend mode is effectively ignored.
* No support of user data properties.
    * Files with user data properties will not prase.

# Dependencies

* zlib (for cel chunk decompression)
* catch2 (for testing only)

All dependencies are obtained via cmake.

# How to use this library

## CMake

CMake integration into your own project is done via `FetchContent`.

include in your `CMakeLists.txt`

```cmake
include(FetchContent)
message(STATUS "Fetching aselib")
FetchContent_Declare(
        aselib
        GIT_REPOSITORY https://github.com/Laguna1989/aseprite_lib.git
        GIT_TAG master
)

set(ASE_LIB_ENABLE_UNIT_TESTS OFF)
FetchContent_MakeAvailable(aselib)

## .... Adding your own library and executable projects

FetchContent_GetProperties(aselib)
target_link_libraries(MyTarget aselib)
```

## Build and run tests locally (on linux)

```shell
git clone https://github.com/Laguna1989/aselib.git
cd aselib
mkdir build
cd build
cmake ..
cmake --build .

cd test/unit_test
./aselib_test
```
