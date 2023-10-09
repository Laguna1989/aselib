#include "aseprite_header.hpp"
#include <aselib/parse_functions.hpp>

std::istream& aseprite_lib::operator>>(std::istream& is, aseprite_lib::AsepriteHeader& header)
{
    header.m_file_size = parseDword(is);
    header.m_magic_number = parseWord(is);
    header.m_number_of_frames = parseWord(is);
    header.m_width_in_pixel = parseWord(is);
    header.m_height_in_pixel = parseWord(is);
    header.m_color_depth = parseWord(is);

    header.m_flags = parseDword(is);
    is.ignore(10);
    // speed
    // set 0
    // set 0
    header.m_index_of_transparent_color = parseByte(is);
    is.ignore(3);
    // ignore 3 bytes
    header.m_number_of_colors = parseWord(is);

    header.m_pixel_width = parseByte(is);
    header.m_pixel_height = parseByte(is);

    header.m_grid_pos_x = parseWord(is); // TODO actually parse an int8_t
    header.m_grid_pos_y = parseWord(is); // TODO actually parse an int8_t
    header.m_grid_width = parseWord(is);
    header.m_grid_height = parseWord(is);

    is.ignore(84);
    // unused
    return is;
}
