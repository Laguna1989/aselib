#ifndef ASELIB_CONSTANTS_HPP
#define ASELIB_CONSTANTS_HPP

namespace aselib {

namespace magic_numbers {
} // namespace magic_numbers

namespace chunk_type_constants {

inline constexpr auto color_profile = 0x2007;
inline constexpr auto palette = 0x2019;
inline constexpr auto layer = 0x2004;
inline constexpr auto cel = 0x2005;
inline constexpr auto tag = 0x2018;
inline constexpr auto user_data = 0x2020;

} // namespace chunk_type_constants

namespace layer_flags {

inline constexpr auto visible = 1u;
inline constexpr auto editable = 2u;
inline constexpr auto lock_movement = 4u;
inline constexpr auto background = 8u;
inline constexpr auto prefer_linked_cells = 16u;
inline constexpr auto displayed_collapsed = 32u;
inline constexpr auto is_reference_layer = 64u;

} // namespace layer_flags

} // namespace aselib

#endif // ASELIB_CONSTANTS_HPP
