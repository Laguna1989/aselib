
#include "pixel_data.hpp"

bool aselib::operator==(PixelDataRGBA const& lhs, PixelDataRGBA const& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}
bool aselib::operator!=(PixelDataRGBA const& lhs, PixelDataRGBA const& rhs)
{
    return !(rhs == lhs);
}

bool aselib::operator==(PixelDataGrayscale const& lhs, PixelDataGrayscale const& rhs)
{
    return lhs.v == rhs.v && lhs.a == rhs.a;
}
bool aselib::operator!=(PixelDataGrayscale const& lhs, PixelDataGrayscale const& rhs)
{
    return !(lhs == rhs);
}
