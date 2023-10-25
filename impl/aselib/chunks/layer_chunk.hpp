#ifndef ASELIB_LAYER_CHUNK_HPP
#define ASELIB_LAYER_CHUNK_HPP

#include <aselib/chunks/chunk_header.hpp>
#include <aselib/types.hpp>
#include <string>

namespace aselib {

struct LayerChunk {
    ChunkHeader m_header {};
    Word_t m_layer_flags {};
    Word_t m_layer_type {};
    Word_t m_layer_child_level {};
    Word_t m_blend_mode {};
    Byte_t m_opacity {};
    std::string m_layer_name {};
};

} // namespace aselib

#endif // ASELIB_LAYER_CHUNK_HPP
