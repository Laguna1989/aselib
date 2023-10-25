#ifndef ASELIB_PALETTE_CHUNK_HPP
#define ASELIB_PALETTE_CHUNK_HPP

#include <aselib/chunks/chunk_header.hpp>
#include <aselib/chunks/palette_entry.hpp>
#include <aselib/types.hpp>
#include <vector>

namespace aselib {

struct PaletteChunk {
    ChunkHeader m_header {};
    Dword_t m_first_color_index_to_change {};
    Dword_t m_last_color_index_to_change {};
    std::vector<PaletteEntry> m_palette_entries {};
};

} // namespace aselib

#endif // ASELIB_PALETTE_CHUNK_HPP
