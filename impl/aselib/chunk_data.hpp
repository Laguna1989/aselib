#ifndef ASEPRITELIB_CHUNK_DATA_HPP
#define ASEPRITELIB_CHUNK_DATA_HPP

#include <aselib/pixel_data.hpp>
#include <aselib/types.hpp>
#include <istream>
#include <vector>

namespace aselib {

struct ChunkHeader {
    Dword_t m_chunk_size;
    Word_t m_chunk_type;
};

struct ColorProfileChunk {
    ChunkHeader m_header;
    Word_t m_color_profile_type;
    Word_t m_color_profile_flags;
    Word_t gamma; // TODO use fixed value instead
};

struct PaletteEntry {
    Word_t m_entry_flags;
    // TODO use pixeldata
    Byte_t m_red;
    Byte_t m_green;
    Byte_t m_blue;
    Byte_t m_alpha;
    std::string m_name;
};

struct PaletteChunk {
    ChunkHeader m_header;
    Dword_t m_first_color_index_to_change;
    Dword_t m_last_color_index_to_change;
    std::vector<PaletteEntry> m_palette_entries;
};

struct LayersChunk {
    ChunkHeader m_header;
    Word_t m_layer_flags;
    Word_t m_layer_type;
    Word_t m_layer_child_level;
    Word_t m_blend_mode;
    Byte_t m_opacity;
    std::string m_layer_name;
};

struct CelChunk {
    ChunkHeader m_header;
    Word_t m_layer_index;
    Short_t m_pos_x;
    Short_t m_pos_y;
    Byte_t m_opacity;
    Word_t m_cell_type;
    Short_t m_z_index;
    Word_t m_cell_width;
    Word_t m_cell_height;
    std::vector<PixelDataRGBA> m_pixels_rgba;
    // TODO implement grayscale and indexed cells
};

struct TagEntry {
    Word_t m_from_frame;
    Word_t m_to_frame;
    Byte_t m_loop_direction;
    Word_t m_repeat_animation;
    std::string m_tag_name;
};

struct TagChunk {
    ChunkHeader m_header;
    std::vector<TagEntry> m_tags;
};

struct UserDataChunk {
    ChunkHeader m_header;
    Dword_t m_user_data_flags;
    std::string m_text;

    // TODO use pixel data
    Byte_t m_color_r;
    Byte_t m_color_g;
    Byte_t m_color_b;
    Byte_t m_color_a;
};

struct ChunksData {
    // TODO think about if vectors are the best way of storing this information for all types
    std::vector<ColorProfileChunk> m_color_profile_chunks;
    std::vector<PaletteChunk> m_palette_chunks;
    std::vector<LayersChunk> m_layers_chunks;
    std::vector<CelChunk> m_cel_chunks;
    std::vector<TagChunk> m_tag_chunks;
    std::vector<UserDataChunk> m_user_data_chunks;
};

ChunkHeader parseChunkHeader(std::istream& is);
void parseNextChunk(std::istream& is, ChunksData& data);
ChunksData parseAllChunks(std::istream& is, std::uint16_t number_of_chunks);

} // namespace aselib

#endif // ASEPRITELIB_CHUNK_DATA_HPP
