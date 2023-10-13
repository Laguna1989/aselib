#include "catch2/catch.hpp"
#include <aselib/aseprite_data.hpp>
#include <aselib/parse_functions.hpp>

using namespace aselib;

TEST_CASE("chunk data", "[chunk]")
{
    AsepriteData ase { "assets/test/unit/32_bit_1x1_white.aseprite" };

    auto const chunks = ase.m_frames.front().m_chunks;

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

TEST_CASE("UserData Chunk", "[chunk, user data]")
{
    AsepriteData const ase { "assets/test/unit/32bit_1x1_white_with_user_data_string.aseprite" };

    SECTION("text")
    {
        REQUIRE(!ase.m_frames.front().m_chunks.m_user_data_chunks.empty());
        REQUIRE(ase.m_frames.front().m_chunks.m_user_data_chunks.front().m_user_data_flags & 1);
        REQUIRE(ase.m_frames.front().m_chunks.m_user_data_chunks.front().m_text == "abcd");
    }
    SECTION("color")
    {
        REQUIRE(!ase.m_frames.front().m_chunks.m_user_data_chunks.empty());
        REQUIRE(ase.m_frames.front().m_chunks.m_user_data_chunks.front().m_user_data_flags & 2);
        REQUIRE(ase.m_frames.front().m_chunks.m_user_data_chunks.front().m_color_r == 255);
        REQUIRE(ase.m_frames.front().m_chunks.m_user_data_chunks.front().m_color_g == 0);
        REQUIRE(ase.m_frames.front().m_chunks.m_user_data_chunks.front().m_color_b == 0);
        REQUIRE(ase.m_frames.front().m_chunks.m_user_data_chunks.front().m_color_a == 255);
    }
}

TEST_CASE("Tag Chunk", "[chunk, tag]")
{
    AsepriteData const ase { "assets/test/unit/32bit_1x1_white_with_user_data_string.aseprite" };

    REQUIRE(!ase.m_frames.front().m_chunks.m_tag_chunks.empty());
    REQUIRE(ase.m_frames.front().m_chunks.m_tag_chunks.front().m_tags.size() == 1);
    REQUIRE(ase.m_frames.front().m_chunks.m_tag_chunks.front().m_tags.front().m_tag_name == "tag");
    REQUIRE(ase.m_frames.front().m_chunks.m_tag_chunks.front().m_tags.front().m_from_frame == 0);
    REQUIRE(ase.m_frames.front().m_chunks.m_tag_chunks.front().m_tags.front().m_to_frame == 0);
    REQUIRE(
        ase.m_frames.front().m_chunks.m_tag_chunks.front().m_tags.front().m_loop_direction == 0);
    REQUIRE(
        ase.m_frames.front().m_chunks.m_tag_chunks.front().m_tags.front().m_repeat_animation == 0);
}
