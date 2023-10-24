#ifndef ASEPRITELIB_PIXEL_DATA_HPP
#define ASEPRITELIB_PIXEL_DATA_HPP

#include <aselib/types.hpp>
#include <vector>

namespace aselib {

struct PixelDataRGBA {
    Byte_t r { 0u };
    Byte_t g { 0u };
    Byte_t b { 0u };
    Byte_t a { 0u };
};

bool operator==(PixelDataRGBA const& lhs, PixelDataRGBA const& rhs);
bool operator!=(PixelDataRGBA const& lhs, PixelDataRGBA const& rhs);

struct PixelDataGrayscale {
    Byte_t v { 0u };
    Byte_t a { 0u };
};

bool operator==(PixelDataGrayscale const& lhs, PixelDataGrayscale const& rhs);
bool operator!=(PixelDataGrayscale const& lhs, PixelDataGrayscale const& rhs);

} // namespace aselib

#endif // ASEPRITELIB_PIXEL_DATA_HPP
