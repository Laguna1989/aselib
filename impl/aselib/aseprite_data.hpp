#ifndef ASELIB_ASEPRITE_DATA_HPP
#define ASELIB_ASEPRITE_DATA_HPP

#include <aselib/aseprite_header.hpp>
#include <aselib/frame_data.hpp>
#include <filesystem>
#include <vector>

namespace aselib {

class AsepriteData {
public:
    explicit AsepriteData(std::filesystem::path const& file_name);

    AsepriteHeader m_header {};
    std::vector<FrameData> m_frames {};
};

} // namespace aselib
#endif // ASELIB_ASEPRITE_DATA_HPP
