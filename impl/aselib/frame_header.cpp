#include "frame_header.hpp"
#include <aselib/parse_functions.hpp>

std::istream& aseprite_lib::operator>>(std::istream& is, aseprite_lib::FrameHader& header)
{
    header.m_frame_size_in_bytes = parseDword(is);
    header.m_magic_number = parseWord(is);
    header.m_number_of_chunks = parseWord(is);
    header.m_frame_duration = parseWord(is);
    is.ignore(2); // for future use
    auto const number_of_chunks_new = parseDword(is);
    if (number_of_chunks_new != 0) {
        header.m_number_of_chunks = number_of_chunks_new;
    }
    return is;
}
