#include "catch2/catch.hpp"
#include <aselib/aseprite_header.hpp>
#include <aselib/chunk_data.hpp>
#include <aselib/frame_header.hpp>
#include <aselib/parse_functions.hpp>
#include <fstream>
using namespace aselib;

TEST_CASE("parse chunk m_header set correct stream position", "[header]")
{
    std::ifstream in { "assets/test/unit/32_bit_1x1_white.aseprite", std::ios::binary };
    REQUIRE(in.good());
    AsepriteHeader hdr {};
    in >> hdr;

    REQUIRE(hdr.m_number_of_frames == 1);

    FrameHader frameHeader {};
    in >> frameHeader;
    REQUIRE(in.tellg() == 128 + 16);
    REQUIRE(frameHeader.m_number_of_chunks == 5);
    REQUIRE(frameHeader.m_magic_number == 0xF1FA);
    (void)parseChunkHeader(in);
    REQUIRE(in.tellg() == 128 + 16 + 6);
}

TEST_CASE("chunk data", "[header, chunk]")
{
    std::ifstream in { "assets/test/unit/32_bit_1x1_white.aseprite", std::ios::binary };
    REQUIRE(in.good());
    AsepriteHeader header {};
    in >> header;

    REQUIRE(header.m_number_of_frames == 1);

    FrameHader frameHader {};
    in >> frameHader;
    auto const chunks = parseAllChunks(in, frameHader.m_number_of_chunks);

    SECTION("color profile")
    {
        REQUIRE(chunks.m_color_profile_chunks.size() == 1);
        REQUIRE(chunks.m_color_profile_chunks.front().m_header.m_chunk_type == 0x2007);
        REQUIRE(chunks.m_color_profile_chunks.front().m_color_profile_type == 1);
        REQUIRE(chunks.m_color_profile_chunks.front().m_color_profile_flags == 0);
    }
    SECTION(" palette")
    {
        REQUIRE(chunks.m_palette_chunks.size() == 1);
        REQUIRE(chunks.m_palette_chunks.front().m_header.m_chunk_type == 0x2019);
        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.size() == 2);
        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.front().m_red == 0);
        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.front().m_green == 0);
        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.front().m_blue == 0);
        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.front().m_alpha == 255);

        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.back().m_red == 34);
        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.back().m_green == 32);
        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.back().m_blue == 52);
        REQUIRE(chunks.m_palette_chunks.front().m_palette_entries.back().m_alpha == 255);
    }
    SECTION("layers")
    {
        REQUIRE(chunks.m_layers_chunks.size() == 1);
        REQUIRE(chunks.m_layers_chunks.front().m_header.m_chunk_type == 0x2004);
        REQUIRE(chunks.m_layers_chunks.front().m_layer_flags == 15);
        REQUIRE(chunks.m_layers_chunks.front().m_layer_type == 0);
        REQUIRE(chunks.m_layers_chunks.front().m_blend_mode == 0);
        REQUIRE(chunks.m_layers_chunks.front().m_opacity == 255);
        REQUIRE(chunks.m_layers_chunks.front().m_layer_name == "Background");
    }
    SECTION("cel")
    {
        REQUIRE(chunks.m_cel_chunks.size() == 1);
        REQUIRE(chunks.m_cel_chunks.front().m_header.m_chunk_type == 0x2005);
        REQUIRE(chunks.m_cel_chunks.front().m_layer_index == 0);
        REQUIRE(chunks.m_cel_chunks.front().m_pos_x == 0);
        REQUIRE(chunks.m_cel_chunks.front().m_pos_y == 0);
        REQUIRE(chunks.m_cel_chunks.front().m_opacity == 255);
        REQUIRE(chunks.m_cel_chunks.front().m_cell_type == 2);
        REQUIRE(chunks.m_cel_chunks.front().m_z_index == 0);
        REQUIRE(chunks.m_cel_chunks.front().m_cell_width == 1);
        REQUIRE(chunks.m_cel_chunks.front().m_cell_height == 1);
        REQUIRE(chunks.m_cel_chunks.front().m_pixels_rgba.size() == 1);
        REQUIRE(chunks.m_cel_chunks.front().m_pixels_rgba.front().r == 255);
        REQUIRE(chunks.m_cel_chunks.front().m_pixels_rgba.front().g == 255);
        REQUIRE(chunks.m_cel_chunks.front().m_pixels_rgba.front().b == 255);
        REQUIRE(chunks.m_cel_chunks.front().m_pixels_rgba.front().a == 255);
    }

    SECTION("tags") { REQUIRE(chunks.m_tag_chunks.size() == 0); }
    SECTION("user data") { REQUIRE(chunks.m_tag_chunks.size() == 0); }
}
