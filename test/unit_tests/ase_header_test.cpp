#include "catch2/catch.hpp"
#include <aselib/aseprite_header.hpp>
#include <fstream>

using namespace aseprite_lib;

TEST_CASE("parse m_header correctly", "[header]")
{
    std::ifstream in { "assets/test/unit/32_bit_1x1_white.aseprite", std::ios::binary };
    REQUIRE(in.good());
    AsepriteHeader hdr {};
    in >> hdr;

    REQUIRE(hdr.m_file_size == 292);
    REQUIRE(hdr.m_magic_number == 0xA5E0);

    REQUIRE(hdr.m_number_of_frames == 1);

    REQUIRE(hdr.m_width_in_pixel == 1);
    REQUIRE(hdr.m_height_in_pixel == 1);

    REQUIRE(hdr.m_color_depth == 32);
    REQUIRE(hdr.m_flags == 1);
    REQUIRE(hdr.m_index_of_transparent_color == 0);

    REQUIRE(hdr.m_number_of_colors == 2);

    REQUIRE(hdr.m_pixel_width == 1);
    REQUIRE(hdr.m_pixel_height == 1);

    REQUIRE(hdr.m_grid_pos_x == 0);
    REQUIRE(hdr.m_grid_pos_y == 0);

    REQUIRE(hdr.m_grid_width == 16);
    REQUIRE(hdr.m_grid_height == 16);
}

TEST_CASE("parse m_header places read position correctly", "[header]")
{
    std::ifstream in { "assets/test/unit/32_bit_1x1_white.aseprite", std::ios::binary };
    REQUIRE(in.good());
    AsepriteHeader hdr {};
    REQUIRE(in.tellg() == 0);
    in >> hdr;
    REQUIRE(in.tellg() == 128);
}
