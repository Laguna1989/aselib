#ifndef ASELIB_USER_DATA_CHUNK_HPP
#define ASELIB_USER_DATA_CHUNK_HPP

#include <aselib/chunks/chunk_header.hpp>
#include <aselib/types.hpp>
#include <string>

namespace aselib {

struct UserDataChunk {
    ChunkHeader m_header {};
    Dword_t m_user_data_flags {};
    std::string m_text {};

    // TODO use pixel data
    Byte_t m_color_r {};
    Byte_t m_color_g {};
    Byte_t m_color_b {};
    Byte_t m_color_a {};
};

} // namespace aselib

#endif // ASELIB_USER_DATA_CHUNK_HPP
