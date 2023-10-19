#ifndef ASEPRITELIB_FRAME_DATA_HPP
#define ASEPRITELIB_FRAME_DATA_HPP

#include <aselib/chunk_data.hpp>
#include <aselib/frame_header.hpp>
namespace aselib {

struct FrameData {
    FrameHeader m_frame_header {};
    ChunksData m_chunks {};
};

} // namespace aselib

#endif // ASEPRITELIB_FRAME_DATA_HPP
