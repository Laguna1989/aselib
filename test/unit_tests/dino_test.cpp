#include "catch2/catch.hpp"
#include <aselib/aseprite_data.hpp>

using namespace aselib;

/// test multiple frames but only one layer and only one animation/tag.
TEST_CASE("parse dino aseprite file", "[dino]")
{
    AsepriteData const ase { "assets/test/unit/dino_salto.aseprite" };
    REQUIRE(ase.m_header.m_number_of_frames == 17);
    REQUIRE(ase.m_frames.size() == 17);

    SECTION("first frame")
    {
        auto const& first_frame = ase.m_frames.front();
        SECTION("palette")
        {
            REQUIRE(first_frame.m_chunks.m_palette_chunks.size() == 1);
            REQUIRE(first_frame.m_chunks.m_palette_chunks.front().m_header.m_chunk_type == 0x2019);
            REQUIRE(first_frame.m_chunks.m_palette_chunks.front().m_palette_entries.size() == 22);
            auto const& first_color
                = first_frame.m_chunks.m_palette_chunks.front().m_palette_entries.front();
            REQUIRE(first_color.m_red == 0);
            REQUIRE(first_color.m_green == 0);
            REQUIRE(first_color.m_blue == 0);
            REQUIRE(first_color.m_alpha == 255);

            auto const& middle_color
                = first_frame.m_chunks.m_palette_chunks.front().m_palette_entries.at(6);
            REQUIRE(middle_color.m_red == 40);
            REQUIRE(middle_color.m_green == 87);
            REQUIRE(middle_color.m_blue == 63);
            REQUIRE(middle_color.m_alpha == 255);

            auto const& last_color
                = first_frame.m_chunks.m_palette_chunks.front().m_palette_entries.back();
            REQUIRE(last_color.m_red == 0);
            REQUIRE(last_color.m_green == 0);
            REQUIRE(last_color.m_blue == 0);
            REQUIRE(last_color.m_alpha == 255);
        }

        SECTION("layers")
        {
            REQUIRE(first_frame.m_chunks.m_layers_chunks.size() == 1);
            auto const& layer = first_frame.m_chunks.m_layers_chunks.front();
            REQUIRE(layer.m_header.m_chunk_type == 0x2004);
            REQUIRE(layer.m_layer_flags == 3);
            REQUIRE(layer.m_layer_type == 0);
            REQUIRE(layer.m_blend_mode == 0);
            REQUIRE(layer.m_opacity == 255);
            REQUIRE(layer.m_layer_name == "Layer 1");
        }

        SECTION("cell")
        {
            REQUIRE(first_frame.m_chunks.m_cel_chunks.size() == 1);
            auto const& cel_data = first_frame.m_chunks.m_cel_chunks.front();
            REQUIRE(cel_data.m_header.m_chunk_type == 0x2005);
            REQUIRE(cel_data.m_layer_index == 0);
            REQUIRE(cel_data.m_pos_x == 6);
            REQUIRE(cel_data.m_pos_y == 6);
            REQUIRE(cel_data.m_opacity == 255);
            REQUIRE(cel_data.m_cell_type == 2);
            REQUIRE(cel_data.m_z_index == 0);
            REQUIRE(cel_data.m_cell_width == 11);
            REQUIRE(cel_data.m_cell_height == 12);
            REQUIRE(cel_data.m_pixels_rgba.size() == 132);
            REQUIRE(cel_data.m_pixels_rgba.front().r == 0);
            REQUIRE(cel_data.m_pixels_rgba.front().g == 0);
            REQUIRE(cel_data.m_pixels_rgba.front().b == 0);
            REQUIRE(cel_data.m_pixels_rgba.front().a == 0);
        }

        SECTION("m_tags")
        {
            REQUIRE(first_frame.m_chunks.m_tag_chunks.size() == 1);
            REQUIRE(first_frame.m_chunks.m_tag_chunks.front().m_header.m_chunk_type == 0x2018);
            REQUIRE(first_frame.m_chunks.m_tag_chunks.front().m_tags.size() == 1);
            auto const& tag = first_frame.m_chunks.m_tag_chunks.front().m_tags.front();
            REQUIRE(tag.m_from_frame == 3);
            REQUIRE(tag.m_to_frame == 7);
            REQUIRE(tag.m_repeat_animation == 0);
            REQUIRE(tag.m_tag_name == "InAir");
            REQUIRE(tag.m_loop_direction == 0);
        }

        SECTION("user data")
        {
            REQUIRE(first_frame.m_chunks.m_user_data_chunks.size() == 1);
            auto const& user_data = first_frame.m_chunks.m_user_data_chunks.front();
            REQUIRE(user_data.m_header.m_chunk_type == 0x2020);
            REQUIRE(user_data.m_user_data_flags == 2);
            REQUIRE(user_data.m_color_r == 0);
            REQUIRE(user_data.m_color_g == 0);
            REQUIRE(user_data.m_color_b == 0);
            REQUIRE(user_data.m_color_a == 255);
        }
    }
}
