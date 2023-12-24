#ifndef ASELIB_PIXEL_DATA_HPP
#define ASELIB_PIXEL_DATA_HPP

#include <aselib/types.hpp>

namespace aselib {

struct PixelDataRGBA {
    Byte_t r { 0u };
    Byte_t g { 0u };
    Byte_t b { 0u };
    Byte_t a { 0u };

    constexpr bool operator==(PixelDataRGBA const& other) const = default;
    constexpr bool operator!=(PixelDataRGBA const& other) const = default;
};

struct PixelDataGrayscale {
    Byte_t v { 0u };
    Byte_t a { 0u };

    constexpr bool operator==(PixelDataGrayscale const& other) const = default;
    constexpr bool operator!=(PixelDataGrayscale const& other) const = default;
};

struct PixelDataIndexed {
    std::uint8_t idx {};

    constexpr bool operator==(PixelDataIndexed const& other) const = default;
    constexpr bool operator!=(PixelDataIndexed const& other) const = default;
};

} // namespace aselib

#endif // ASELIB_PIXEL_DATA_HPP
