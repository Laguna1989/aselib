#ifndef ASELIB_COLOR_PROFILE_CHUNK_HPP
#define ASELIB_COLOR_PROFILE_CHUNK_HPP

#include <aselib/chunks/chunk_header.hpp>
#include <aselib/types.hpp>

namespace aselib {

struct ColorProfileChunk {
    ChunkHeader m_header {};
    Word_t m_color_profile_type {};
    Word_t m_color_profile_flags {};
    Word_t gamma {}; // TODO use fixed value instead
};

} // namespace aselib

#endif // ASELIB_COLOR_PROFILE_CHUNK_HPP
