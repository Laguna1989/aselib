#ifndef ASELIB_TAG_ENTRY_HPP
#define ASELIB_TAG_ENTRY_HPP

#include <aselib/types.hpp>
#include <string>

namespace aselib {

struct TagEntry {
    Word_t m_from_frame {};
    Word_t m_to_frame {};

    /// Loop direction encoding
    ///
    /// (0 = Forward)
    /// (1 = Reverse)
    /// (2 = Ping-pong)
    /// (3 = Ping-pong Reverse)
    Byte_t m_loop_direction {};
    Word_t m_repeat_animation {};
    std::string m_tag_name {};
};

} // namespace aselib

#endif // ASELIB_TAG_ENTRY_HPP
