#ifndef ASELIB_FRAME_DATA_HPP
#define ASELIB_FRAME_DATA_HPP

#include <aselib/chunks_data.hpp>
#include <aselib/frame_header.hpp>

namespace aselib {

struct FrameData {
    FrameHeader m_frame_header {};
    ChunksData m_chunks {};
};

} // namespace aselib

#endif // ASELIB_FRAME_DATA_HPP
