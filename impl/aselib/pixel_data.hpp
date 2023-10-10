#ifndef ASEPRITELIB_PIXEL_DATA_HPP
#define ASEPRITELIB_PIXEL_DATA_HPP

#include <aselib/types.hpp>
#include <vector>

namespace aselib {

struct PixelDataRGBA {
    aselib::Byte_t r;
    aselib::Byte_t g;
    aselib::Byte_t b;
    aselib::Byte_t a;
};

} // namespace aselib

#endif // ASEPRITELIB_PIXEL_DATA_HPP
