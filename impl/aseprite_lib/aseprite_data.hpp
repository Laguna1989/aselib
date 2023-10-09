#ifndef ASEPRITELIB_ASEPRITE_DATA_HPP
#define ASEPRITELIB_ASEPRITE_DATA_HPP

#include <aseprite_lib/aseprite_header.hpp>
#include <aseprite_lib/frame_data.hpp>
#include <vector>

namespace aseprite_lib {

class AsepriteData {
public:
    AsepriteData(std::string const& file_name);

    AsepriteHeader m_header;
    std::vector<FrameData> m_frames;
};

} // namespace aseprite_lib
#endif // ASEPRITELIB_ASEPRITE_DATA_HPP
