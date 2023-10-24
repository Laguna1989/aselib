#ifndef ASELIB_PIXEL_OPERATIONS_HPP
#define ASELIB_PIXEL_OPERATIONS_HPP

#include <aselib/pixel_data.hpp>

namespace aselib {

aselib::PixelDataRGBA add_pixel_color(aselib::PixelDataRGBA const& pixel_src,
    aselib::PixelDataRGBA const& pixel_orig, std::uint8_t layer_opacity = 255);

aselib::PixelDataRGBA add_pixel_color(aselib::PixelDataGrayscale const& pixel_src,
    aselib::PixelDataRGBA const& pixel_orig, std::uint8_t layer_opacity = 255);

} // namespace aselib

#endif // ASELIB_PIXEL_OPERATIONS_HPP
