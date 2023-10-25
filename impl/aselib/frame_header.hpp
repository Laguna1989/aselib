#ifndef ASELIB_FRAME_HEADER_HPP
#define ASELIB_FRAME_HEADER_HPP

#include <aselib/types.hpp>
#include <istream>

namespace aselib {

struct FrameHeader {
    Dword_t m_frame_size_in_bytes {};
    Word_t m_magic_number {};
    Dword_t m_number_of_chunks {};
    Word_t m_frame_duration {};
};

std::istream& operator>>(std::istream& is, FrameHeader& header);

} // namespace aselib

#endif // ASELIB_FRAME_HEADER_HPP
