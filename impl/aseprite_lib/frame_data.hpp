#ifndef ASEPRITELIB_FRAME_DATA_HPP
#define ASEPRITELIB_FRAME_DATA_HPP

#include <aseprite_lib/chunk_data.hpp>
#include <aseprite_lib/frame_header.hpp>
namespace aseprite_lib {

struct FrameData {
    FrameHader m_frame_header;
    ChunksData m_chunks;
};

} // namespace aseprite_lib

#endif // ASEPRITELIB_FRAME_DATA_HPP
