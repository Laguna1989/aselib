#ifndef ASEPRITELIB_PARSE_FUNCTIONS_HPP
#define ASEPRITELIB_PARSE_FUNCTIONS_HPP

#include <cstdint>
#include <istream>

namespace aseprite_lib {

std::uint8_t parseByte(std::istream& is);

std::uint16_t parseWord(std::istream& is);

std::uint32_t parseDword(std::istream& is);

std::string parseString(std::istream& is);

} // namespace aseprite_lib

#endif // ASEPRITELIB_PARSE_FUNCTIONS_HPP
