#ifndef ASEPRITELIB_FRAME_DATA_HPP
#define ASEPRITELIB_FRAME_DATA_HPP

#include <aselib/chunk_data.hpp>
#include <aselib/frame_header.hpp>
namespace aseprite_lib {

struct FrameData {
    FrameHader m_frame_header;
    ChunksData m_chunks;
};

} // namespace aseprite_lib

#endif // ASEPRITELIB_FRAME_DATA_HPP
