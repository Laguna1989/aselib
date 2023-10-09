#ifndef ASEPRITELIB_IMAGE_HPP
#define ASEPRITELIB_IMAGE_HPP

#include <aselib/pixel_data.hpp>
#include <cstdint>
#include <vector>

namespace aseprite_lib {

struct Image {
    std::uint32_t m_width;
    std::uint32_t m_height;

    std::vector<PixelDataRGBA> m_pixels;

    std::size_t posToIndex(std::uint32_t x, std::uint32_t y) const;
};

} // namespace aseprite_lib

#endif // ASEPRITELIB_IMAGE_HPP
