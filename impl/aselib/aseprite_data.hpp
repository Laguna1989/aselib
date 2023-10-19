#ifndef ASEPRITELIB_ASEPRITE_DATA_HPP
#define ASEPRITELIB_ASEPRITE_DATA_HPP

#include <aselib/aseprite_header.hpp>
#include <aselib/frame_data.hpp>
#include <vector>

namespace aselib {

class AsepriteData {
public:
    AsepriteData(std::string const& file_name);

    AsepriteHeader m_header {};
    std::vector<FrameData> m_frames {};
};

} // namespace aselib
#endif // ASEPRITELIB_ASEPRITE_DATA_HPP
