#include "parse_functions.hpp"

std::uint8_t aseprite_lib::parseByte(std::istream& is)
{
    char b1;
    is.read(&b1, 1);
    if (is.good()) {
        return static_cast<std::uint8_t>(b1);
    }
    return 0u;
}

std::uint16_t aseprite_lib::parseWord(std::istream& is)
{
    char b[2];

    is.read(b, 2);

    if (is.good()) {
        return ((b[1] << 8) | b[0]); // Little endian
    }
    return 0u;
}

std::uint32_t aseprite_lib::parseDword(std::istream& is)
{
    char b[4];
    is.read(b, 4);
    if (is.good()) {
        return ((b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0]);
    }
    return 0u;
}

std::string aseprite_lib::parseString(std::istream& is)
{
    auto const size = parseWord(is);
    std::string str {};
    str.resize(size);
    for (auto i = 0u; i != size; ++i) {
        str[i] = parseByte(is);
    }
    return str;
}
