#ifndef ASELIB_CHUNK_DATA_HPP
#define ASELIB_CHUNK_DATA_HPP

#include <aselib/chunks/cel_chunk.hpp>
#include <aselib/chunks/chunk_header.hpp>
#include <aselib/chunks/color_profile_chunk.hpp>
#include <aselib/chunks/layer_chunk.hpp>
#include <aselib/chunks/palette_chunk.hpp>
#include <aselib/chunks/tag_chunk.hpp>
#include <aselib/chunks/user_data_chunk.hpp>
#include <istream>
#include <vector>

namespace aselib {

struct AsepriteHeader;

struct ChunksData {
    // TODO think about if vectors are the best way of storing this information for all types
    std::vector<ColorProfileChunk> m_color_profile_chunks {};
    std::vector<PaletteChunk> m_palette_chunks {};
    std::vector<LayerChunk> m_layers_chunks {};
    std::vector<CelChunk> m_cel_chunks {};
    std::vector<TagChunk> m_tag_chunks {};
    std::vector<UserDataChunk> m_user_data_chunks {};
};

ChunkHeader parseChunkHeader(std::istream& is);
void parseNextChunk(std::istream& is, ChunksData& data, AsepriteHeader const& ase_header);
ChunksData parseAllChunks(
    std::istream& is, uint16_t number_of_chunks, AsepriteHeader const& ase_header);

} // namespace aselib

#endif // ASELIB_CHUNK_DATA_HPP
