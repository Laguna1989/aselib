#include "catch2/catch.hpp"
#include <aselib/aseprite_header.hpp>
#include <aselib/frame_header.hpp>
#include <fstream>

using namespace aseprite_lib;

TEST_CASE("parse frame header data correctly", "[header]")
{
    std::ifstream in { "assets/test/unit/32_bit_1x1_white.aseprite", std::ios::binary };
    REQUIRE(in.good());
    AsepriteHeader header {};
    in >> header;

    REQUIRE(header.m_number_of_frames == 1);

    FrameHader frameHader {};
    in >> frameHader;

    REQUIRE(frameHader.m_number_of_chunks == 5);
    REQUIRE(frameHader.m_frame_duration == 100);
}

TEST_CASE("parse frame header size correctly", "[header]")
{
    std::ifstream in { "assets/test/unit/32_bit_1x1_white.aseprite", std::ios::binary };
    REQUIRE(in.good());
    AsepriteHeader header {};
    in >> header;

    FrameHader frameHader;
    in >> frameHader;

    REQUIRE(in.tellg() == 128 + 16);
}
