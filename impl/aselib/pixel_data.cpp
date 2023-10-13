
#include "pixel_data.hpp"

namespace aselib {

bool operator==(PixelDataRGBA const& lhs, PixelDataRGBA const& rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}
bool operator!=(PixelDataRGBA const& lhs, PixelDataRGBA const& rhs) { return !(rhs == lhs); }

} // namespace aselib
