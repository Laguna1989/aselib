#include "image.hpp"

std::size_t aseprite_lib::Image::posToIndex(std::uint32_t x, std::uint32_t y) const
{
    return y * m_width + x;
}
