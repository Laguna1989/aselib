#ifndef ASELIB_PIXEL_OPERATIONS_HPP
#define ASELIB_PIXEL_OPERATIONS_HPP

#include <aselib/pixel_data.hpp>

namespace aselib {

struct PaletteChunk;

PixelDataRGBA add_pixel_color(PixelDataRGBA const& pixel_src, PixelDataRGBA const& pixel_orig,
    std::uint8_t layer_opacity = 255);

PixelDataRGBA add_pixel_color(PixelDataGrayscale const& pixel_src, PixelDataRGBA const& pixel_orig,
    std::uint8_t layer_opacity = 255);

PixelDataRGBA add_pixel_color(PixelDataIndexed const& pixel_src, PixelDataRGBA const& pixel_orig,
    PaletteChunk const& palette, std::uint8_t layer_opacity = 255);

} // namespace aselib

#endif // ASELIB_PIXEL_OPERATIONS_HPP
