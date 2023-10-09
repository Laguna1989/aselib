#ifndef ASEPRITELIB_FRAME_HEADER_HPP
#define ASEPRITELIB_FRAME_HEADER_HPP

#include <aselib/types.hpp>
#include <istream>

namespace aseprite_lib {

struct FrameHader {
    Dword_t m_frame_size_in_bytes;
    Word_t m_magic_number;
    Dword_t m_number_of_chunks;
    Word_t m_frame_duration;

    friend std::istream& operator>>(std::istream& is, FrameHader& header);
};

} // namespace aseprite_lib

#endif // ASEPRITELIB_FRAME_HEADER_HPP
