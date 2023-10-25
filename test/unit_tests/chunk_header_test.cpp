#include "catch2/catch.hpp"
#include <aselib/aseprite_header.hpp>
#include <aselib/chunks_data.hpp>
#include <aselib/frame_header.hpp>
#include <aselib/parse_functions.hpp>
#include <fstream>
using namespace aselib;

TEST_CASE("parse first chunk header results in correct stream offset", "[header]")
{
    std::ifstream in { "assets/test/unit/32_bit_1x1_white.aseprite", std::ios::binary };
    REQUIRE(in.good());
    AsepriteHeader hdr {};
    in >> hdr;

    REQUIRE(hdr.m_number_of_frames == 1);

    FrameHeader frameHeader {};
    in >> frameHeader;
    REQUIRE(in.tellg() == 128 + 16);
    (void)parseChunkHeader(in);
    REQUIRE(in.tellg() == 128 + 16 + 6);
}
