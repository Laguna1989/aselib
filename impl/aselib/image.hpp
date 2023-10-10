#ifndef ASEPRITELIB_IMAGE_HPP
#define ASEPRITELIB_IMAGE_HPP

#include <aselib/pixel_data.hpp>
#include <cstdint>
#include <vector>

namespace aselib {

struct Image {
    std::uint32_t m_width {};
    std::uint32_t m_height {};

    std::vector<PixelDataRGBA> m_pixels {};

    PixelDataRGBA& getPixelAt(std::uint32_t x, std::uint32_t y);
    [[nodiscard]] PixelDataRGBA const& getPixelAt(std::uint32_t x, std::uint32_t y) const;

    [[nodiscard]] std::size_t posToIndex(std::uint32_t x, std::uint32_t y) const;
};

} // namespace aselib

#endif // ASEPRITELIB_IMAGE_HPP
