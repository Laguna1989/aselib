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

## How to use (SFML)

```c++
// parse aseprite file    
aselib::AsepriteData aseData { filename };

// get image date from all layers
auto const aseImage = aselib::makeImageFromAse(aseData);

// create empty sf::Image with correct size
sf::Image sfImgage {};
sf::Color const emptyColor { 0, 0, 0, 0 };
auto const w = aseImage.m_width;
auto const h = aseImage.m_height;
sfImgage.create(w, h, emptyColor);

// set pixels according to aseprite file
for (auto i = 0u; i != w; ++i) {
    for (auto j = 0U; j != h; ++j) {
        auto const& p = aseImage.getPixelAt(i, j);
        sfImgage.setPixel(i, j, sf::Color{p.r, p.g, p.b, p.a});
    }
}

// the following is just normal sfml code

// convert sf::Image to sf::Texture
sf::Texture sfTexture{};
sfTexture.loadFromImage(sfImage);

// use sf::Texture to create a sprite
sf::Sprite sprite{sfTexture};

// use the sprite for drawing
// ...
```

## How to use (SDL2)

In SDL pixel manipulation is a bit more complicated, as some pointer trickery is required. The following function will
help you do this.

```c++
void setPixel(SDL_Surface* surface, int x, int y, uint32_t pixel)
{
    uint8_t* target_pixel = static_cast<uint8_t*>(surface->pixels) + y * surface->pitch + x * 4;
    *(uint32_t*)target_pixel = pixel;
}
```

The `SDL_Surface*` needs to be created using `SDL_PIXELFORMAT_RGBA32`, e.g. with this call:

```c++
SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32)
```

the `uint32_t` pixel value can be obtained by

```c++
auto const pixel = SDL_MapRGBA(image->format, r, g, b, a);
```

where `r`, `g`, `b`, `a` are `std::uint8_t` values, as obtained by `aselib`.

## How to use (other frameworks)

All you need is the option to set pixel data in the framework of your choice.
The snippets above showcase how to obtain image data from `aselib`, but you can also directly access the members
of `aselib::AsepriteData` and obtain the information that you require.

[This page](https://github.com/aseprite/aseprite/blob/main/docs/ase-file-specs.md) from the aseprite documentation
provides a great starting point for understanding what information is available besides the pixel information.

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


