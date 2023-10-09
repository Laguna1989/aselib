#ifndef ASEPRITELIB_PIXEL_DATA_HPP
#define ASEPRITELIB_PIXEL_DATA_HPP

#include <aselib/types.hpp>
#include <vector>

namespace aseprite_lib {

struct PixelDataRGBA {
    aseprite_lib::Byte_t r;
    aseprite_lib::Byte_t g;
    aseprite_lib::Byte_t b;
    aseprite_lib::Byte_t a;
};

} // namespace aseprite_lib

#endif // ASEPRITELIB_PIXEL_DATA_HPP
