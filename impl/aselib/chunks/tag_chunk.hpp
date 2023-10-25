#ifndef ASELIB_TAG_CHUNK_HPP
#define ASELIB_TAG_CHUNK_HPP

#include <aselib/chunks/chunk_header.hpp>
#include <aselib/chunks/tag_entry.hpp>
#include <vector>

namespace aselib {

struct TagChunk {
    ChunkHeader m_header {};
    std::vector<TagEntry> m_tags {};
};

} // namespace aselib

#endif // ASELIB_TAG_CHUNK_HPP
