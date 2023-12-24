#include "image.hpp"
#include <stdexcept>
#include <string>

std::size_t aselib::Image::posToIndex(std::uint32_t x, std::uint32_t y) const
{
    if (x >= m_width || y >= m_height) [[unlikely]] {
        throw std::invalid_argument { "invalid pixel position in image: " + std::to_string(x) + ", "
            + std::to_string(y) };
    }
    return y * m_width + x;
}
aselib::PixelDataRGBA& aselib::Image::getPixelAt(std::uint32_t x, std::uint32_t y)
{
    return m_pixels[posToIndex(x, y)];
}
aselib::PixelDataRGBA const& aselib::Image::getPixelAt(std::uint32_t x, std::uint32_t y) const
{
    return m_pixels[posToIndex(x, y)];
}
