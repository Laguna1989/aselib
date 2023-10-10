#include "image.hpp"

std::size_t aselib::Image::posToIndex(std::uint32_t x, std::uint32_t y) const
{
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
