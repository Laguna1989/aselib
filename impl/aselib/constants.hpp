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

} // namespace aselib

#endif // ASELIB_CONSTANTS_HPP
