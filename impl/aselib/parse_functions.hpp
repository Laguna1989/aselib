#ifndef ASELIB_PARSE_FUNCTIONS_HPP
#define ASELIB_PARSE_FUNCTIONS_HPP

#include <cstdint>
#include <istream>

namespace aselib {

std::uint8_t parseByte(std::istream& is);

std::uint16_t parseWord(std::istream& is);

std::int16_t parseShort(std::istream& is);

std::uint32_t parseDword(std::istream& is);

std::string parseString(std::istream& is);

} // namespace aselib

#endif // ASELIB_PARSE_FUNCTIONS_HPP
