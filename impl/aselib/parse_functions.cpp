#include "parse_functions.hpp"

std::uint8_t aselib::parseByte(std::istream& is)
{
    char b1;
    is.get(b1);
    if (!is.good()) [[unlikely]] {
        return 0u;
    }
    return static_cast<std::uint8_t>(b1);
}

std::uint16_t aselib::parseWord(std::istream& is)
{
    char b[2];

    is.get(b[0]);
    is.get(b[1]);

    if (!is.good()) [[unlikely]] {
        return 0u;
    }

    return (
        // clang-format off
        static_cast<std::uint8_t>(b[1]) << 8 |
        static_cast<std::uint8_t>(b[0])
        // clang-format on
    );
}

std::int16_t aselib::parseShort(std::istream& is)
{
    // TODO signed/unsigned conversion
    char b[2];

    is.get(b[0]);
    is.get(b[1]);

    if (!is.good()) [[unlikely]] {
        return 0u;
    }

    return static_cast<std::int16_t>(
        // clang-format off
            static_cast<std::uint8_t>(b[1]) << 8 |
            static_cast<std::uint8_t>(b[0])
        // clang-format on
    );
}

std::uint32_t aselib::parseDword(std::istream& is)
{
    char b[4] = { 0, 0, 0, 0 };
    is.get(b[0]);
    is.get(b[1]);
    is.get(b[2]);
    is.get(b[3]);
    if (!is.good()) [[unlikely]] {
        return 0;
    }
    return (
        // clang-format off
        static_cast<std::uint8_t>(b[3]) << 24 |
        static_cast<std::uint8_t>(b[2]) << 16 |
        static_cast<std::uint8_t>(b[1]) << 8 |
        static_cast<std::uint8_t>(b[0]) << 0
        // clang-format on
    );
}

std::string aselib::parseString(std::istream& is)
{
    auto const size = parseWord(is);
    std::string str {};
    str.resize(size);
    for (auto i = 0u; i != size; ++i) {
        str[i] = parseByte(is);
    }
    if (!is.good()) [[unlikely]] {
        return "";
    }
    return str;
}
