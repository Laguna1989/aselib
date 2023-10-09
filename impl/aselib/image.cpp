#include "image.hpp"

std::size_t aseprite_lib::Image::posToIndex(std::uint32_t x, std::uint32_t y) const
{
    return y * m_width + x;
}
aseprite_lib::PixelDataRGBA& aseprite_lib::Image::getPixelAt(std::uint32_t x, std::uint32_t y)
{
    return m_pixels[posToIndex(x, y)];
}
aseprite_lib::PixelDataRGBA const& aseprite_lib::Image::getPixelAt(
    std::uint32_t x, std::uint32_t y) const
{
    return m_pixels[posToIndex(x, y)];
}
