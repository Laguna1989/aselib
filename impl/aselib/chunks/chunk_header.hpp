#ifndef ASELIB_CHUNK_HEADER_HPP
#define ASELIB_CHUNK_HEADER_HPP

#include <aselib/types.hpp>
namespace aselib {

struct ChunkHeader {
    Dword_t m_chunk_size {};
    Word_t m_chunk_type {};
};

} // namespace aselib

#endif // ASELIB_CHUNK_HEADER_HPP
