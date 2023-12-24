#ifndef ASELIB_ASEPRITEHEADER_GUARD
#define ASELIB_ASEPRITEHEADER_GUARD

#include <aselib/types.hpp>
#include <istream>
#include <ostream>

namespace aselib {

struct AsepriteHeader {
    Dword_t m_file_size {};
    Word_t m_magic_number {};
    Word_t m_number_of_frames {};
    Word_t m_width_in_pixel {};
    Word_t m_height_in_pixel {};
    Word_t m_color_depth {};

    Dword_t m_flags {};

    Byte_t m_index_of_transparent_color {};
    Word_t m_number_of_colors {};
    Byte_t m_pixel_width {};
    Byte_t m_pixel_height {};

    Short_t m_grid_pos_x {};
    Short_t m_grid_pos_y {};
    Word_t m_grid_width {};
    Word_t m_grid_height {};
};

std::istream& operator>>(std::istream& is, AsepriteHeader& header);

} // namespace aselib

#endif // ASELIB_ASEPRITEHEADER_GUARD
