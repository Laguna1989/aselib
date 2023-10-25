#ifndef ASELIB_PALETTE_ENTRY_HPP
#define ASELIB_PALETTE_ENTRY_HPP

#include <aselib/pixel_data.hpp>
#include <aselib/types.hpp>
#include <string>

namespace aselib {

struct PaletteEntry {
    /// Palette Entry Flags:
    /// 1: Has Name
    Word_t m_entry_flags {};
    PixelDataRGBA m_color {};
    std::string m_name {};
};

} // namespace aselib

#endif // ASELIB_PALETTE_ENTRY_HPP
