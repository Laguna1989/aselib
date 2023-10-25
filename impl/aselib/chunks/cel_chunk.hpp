#ifndef ASELIB_CEL_CHUNK_HPP
#define ASELIB_CEL_CHUNK_HPP

#include <aselib/chunks/chunk_header.hpp>
#include <aselib/pixel_data.hpp>
#include <aselib/types.hpp>
#include <vector>

namespace aselib {

struct CelChunk {
    ChunkHeader m_header {};
    Word_t m_layer_index {};
    Short_t m_pos_x {};
    Short_t m_pos_y {};
    Byte_t m_opacity {};
    Word_t m_cell_type {};
    Short_t m_z_index {};
    Word_t m_cell_width {};
    Word_t m_cell_height {};
    // Note: the cel chunk contains all three pixel data types, but only one is used.
    std::vector<PixelDataRGBA> m_pixels_rgba {};
    std::vector<PixelDataGrayscale> m_pixels_grayscale {};
    std::vector<PixelDataIndexed> m_pixels_indexed;
};

} // namespace aselib

#endif // ASELIB_CEL_CHUNK_HPP
