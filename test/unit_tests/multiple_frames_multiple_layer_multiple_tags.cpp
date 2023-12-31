#include <aselib/aseprite_data.hpp>
#include <aselib/constants.hpp>
#include <catch2/catch.hpp>

using namespace aselib;

/// test multiple frames but only one layer and only one animation/tag.
TEST_CASE("multiple frames multiple layers multiple tags", "[miner, frame, layer, tag]")
{
    AsepriteData const ase { "assets/test/unit/miner.aseprite" };

    REQUIRE(ase.m_header.m_number_of_frames == 10);
    REQUIRE(ase.m_frames.size() == 10);

    SECTION("first frame")
    {
        auto const& first_frame = ase.m_frames.front();
        SECTION("color profile")
        {
            REQUIRE(first_frame.m_chunks.m_color_profile_chunks.size() == 1);
            REQUIRE(first_frame.m_chunks.m_color_profile_chunks.front().m_header.m_chunk_type
                == aselib::chunk_type_constants::color_profile);
            REQUIRE(first_frame.m_chunks.m_color_profile_chunks.front().m_color_profile_type == 1);
            REQUIRE(first_frame.m_chunks.m_color_profile_chunks.front().m_color_profile_flags == 0);
        }
        SECTION("palette")
        {
            REQUIRE(first_frame.m_chunks.m_palette_chunks.size() == 1);
            REQUIRE(first_frame.m_chunks.m_palette_chunks.front().m_header.m_chunk_type
                == aselib::chunk_type_constants::palette);
            REQUIRE(first_frame.m_chunks.m_palette_chunks.front().m_palette_entries.size() == 32);
            auto const& first_color
                = first_frame.m_chunks.m_palette_chunks.front().m_palette_entries.front();
            REQUIRE(first_color.m_color.r == 0);
            REQUIRE(first_color.m_color.g == 0);
            REQUIRE(first_color.m_color.b == 0);
            REQUIRE(first_color.m_color.a == 255);

            auto const& middle_color
                = first_frame.m_chunks.m_palette_chunks.front().m_palette_entries.at(6);
            REQUIRE(middle_color.m_color.r == 217);
            REQUIRE(middle_color.m_color.g == 160);
            REQUIRE(middle_color.m_color.b == 102);
            REQUIRE(middle_color.m_color.a == 255);

            auto const& last_color
                = first_frame.m_chunks.m_palette_chunks.front().m_palette_entries.back();
            REQUIRE(last_color.m_color.r == 138);
            REQUIRE(last_color.m_color.g == 111);
            REQUIRE(last_color.m_color.b == 48);
            REQUIRE(last_color.m_color.a == 255);
        }

        SECTION("layers")
        {
            REQUIRE(first_frame.m_chunks.m_layers_chunks.size() == 4);
            SECTION("main")
            {
                auto const& layer = first_frame.m_chunks.m_layers_chunks.front();
                REQUIRE(layer.m_header.m_chunk_type == aselib::chunk_type_constants::layer);
                REQUIRE(layer.m_layer_flags == 3);
                REQUIRE(layer.m_layer_type == 0);
                REQUIRE(layer.m_blend_mode == 0);
                REQUIRE(layer.m_opacity == 255);
                REQUIRE(layer.m_layer_name == "main");
            }
            SECTION("weapon")
            {
                auto const& layer = first_frame.m_chunks.m_layers_chunks.at(1);
                REQUIRE(layer.m_header.m_chunk_type == aselib::chunk_type_constants::layer);
                REQUIRE(layer.m_layer_flags == 3);
                REQUIRE(layer.m_layer_type == 0);
                REQUIRE(layer.m_blend_mode == 0);
                REQUIRE(layer.m_opacity == 255);
                REQUIRE(layer.m_layer_name == "weapon");
            }
            SECTION("slash")
            {
                auto const& layer = first_frame.m_chunks.m_layers_chunks.at(2);
                REQUIRE(layer.m_header.m_chunk_type == aselib::chunk_type_constants::layer);
                REQUIRE(layer.m_layer_flags == 3);
                REQUIRE(layer.m_layer_type == 0);
                REQUIRE(layer.m_blend_mode == 0);
                REQUIRE(layer.m_opacity == 255);
                REQUIRE(layer.m_layer_name == "slash");
            }
            SECTION("outline")
            {
                auto const& layer = first_frame.m_chunks.m_layers_chunks.at(3);
                REQUIRE(layer.m_header.m_chunk_type == aselib::chunk_type_constants::layer);
                REQUIRE(layer.m_layer_flags == 3);
                REQUIRE(layer.m_layer_type == 0);
                REQUIRE(layer.m_blend_mode == 0);
                REQUIRE(layer.m_opacity == 255);
                REQUIRE(layer.m_layer_name == "outline");
            }
        }

        SECTION("cell")
        {
            REQUIRE(first_frame.m_chunks.m_cel_chunks.size() == 3);
            SECTION("main")
            {
                auto const& cel_data = first_frame.m_chunks.m_cel_chunks.front();
                REQUIRE(cel_data.m_header.m_chunk_type == aselib::chunk_type_constants::cel);
                REQUIRE(cel_data.m_layer_index == 0);

                REQUIRE(cel_data.m_pos_x == 11);
                REQUIRE(cel_data.m_pos_y == 16);

                REQUIRE(cel_data.m_opacity == 255);

                REQUIRE(cel_data.m_cell_type == 2);

                REQUIRE(cel_data.m_z_index == 0);

                REQUIRE(cel_data.m_cell_width == 8);
                REQUIRE(cel_data.m_cell_height == 15);

                REQUIRE(cel_data.m_pixels_rgba.size() == 120);

                REQUIRE(cel_data.m_pixels_rgba.front() == PixelDataRGBA { 0, 0, 0, 0 });
            }

            SECTION("weapon")
            {
                auto const& cel_data = first_frame.m_chunks.m_cel_chunks.at(1);
                REQUIRE(cel_data.m_header.m_chunk_type == aselib::chunk_type_constants::cel);
                REQUIRE(cel_data.m_layer_index == 1);

                REQUIRE(cel_data.m_pos_x == 9);
                REQUIRE(cel_data.m_pos_y == 18);

                REQUIRE(cel_data.m_opacity == 255);

                REQUIRE(cel_data.m_cell_type == 2);

                REQUIRE(cel_data.m_z_index == 0);

                REQUIRE(cel_data.m_cell_width == 12);
                REQUIRE(cel_data.m_cell_height == 13);

                REQUIRE(cel_data.m_pixels_rgba.size() == 156);

                REQUIRE(cel_data.m_pixels_rgba.front() == PixelDataRGBA { 0, 0, 0, 0 });
            }
            SECTION("outline")
            {
                auto const& cel_data = first_frame.m_chunks.m_cel_chunks.at(2);
                REQUIRE(cel_data.m_header.m_chunk_type == aselib::chunk_type_constants::cel);
                REQUIRE(cel_data.m_layer_index == 3);

                REQUIRE(cel_data.m_pos_x == 8);
                REQUIRE(cel_data.m_pos_y == 15);

                REQUIRE(cel_data.m_opacity == 255);

                REQUIRE(cel_data.m_cell_type == 2);

                REQUIRE(cel_data.m_z_index == 0);

                REQUIRE(cel_data.m_cell_width == 14);
                REQUIRE(cel_data.m_cell_height == 16);

                REQUIRE(cel_data.m_pixels_rgba.size() == 224);

                REQUIRE(cel_data.m_pixels_rgba.front() == PixelDataRGBA { 0, 0, 0, 0 });
            }
        }

        SECTION("m_tags")
        {
            REQUIRE(first_frame.m_chunks.m_tag_chunks.size() == 1);
            REQUIRE(first_frame.m_chunks.m_tag_chunks.front().m_header.m_chunk_type
                == aselib::chunk_type_constants::tag);
            REQUIRE(first_frame.m_chunks.m_tag_chunks.front().m_tags.size() == 2);

            SECTION("idle")
            {
                auto const& firstTag = first_frame.m_chunks.m_tag_chunks.front().m_tags.front();
                REQUIRE(firstTag.m_from_frame == 0);
                REQUIRE(firstTag.m_to_frame == 3);
                REQUIRE(firstTag.m_repeat_animation == 0);
                REQUIRE(firstTag.m_tag_name == "idle");
                REQUIRE(firstTag.m_loop_direction == 0);
            }
            SECTION("mine")
            {
                auto const& secondTag = first_frame.m_chunks.m_tag_chunks.front().m_tags.back();
                REQUIRE(secondTag.m_from_frame == 4);
                REQUIRE(secondTag.m_to_frame == 9);
                REQUIRE(secondTag.m_repeat_animation == 0);
                REQUIRE(secondTag.m_tag_name == "mine");
                REQUIRE(secondTag.m_loop_direction == 0);
            }
        }

        SECTION("user data")
        {
            REQUIRE(first_frame.m_chunks.m_user_data_chunks.size() == 2);
            auto const& user_data = first_frame.m_chunks.m_user_data_chunks.front();
            REQUIRE(user_data.m_header.m_chunk_type == aselib::chunk_type_constants::user_data);
            REQUIRE(user_data.m_user_data_flags == 2);
            REQUIRE(user_data.m_color_r == 0);
            REQUIRE(user_data.m_color_g == 0);
            REQUIRE(user_data.m_color_b == 0);
            REQUIRE(user_data.m_color_a == 255);
        }
    }
    SECTION("second frame")
    {
        auto const& second_frame = ase.m_frames.at(1);
        REQUIRE(second_frame.m_chunks.m_color_profile_chunks.empty());
        REQUIRE(second_frame.m_chunks.m_palette_chunks.empty());
        REQUIRE(second_frame.m_chunks.m_tag_chunks.empty());
        REQUIRE(second_frame.m_chunks.m_user_data_chunks.empty());
        REQUIRE(second_frame.m_chunks.m_layers_chunks.empty());

        SECTION("cell")
        {
            REQUIRE(second_frame.m_chunks.m_cel_chunks.size() == 3);
            auto const& cel_data = second_frame.m_chunks.m_cel_chunks.front();
            REQUIRE(cel_data.m_header.m_chunk_type == aselib::chunk_type_constants::cel);
            REQUIRE(cel_data.m_layer_index == 0);

            REQUIRE(cel_data.m_pos_x == 10);
            REQUIRE(cel_data.m_pos_y == 17);

            REQUIRE(cel_data.m_opacity == 255);

            REQUIRE(cel_data.m_cell_type == 2);

            REQUIRE(cel_data.m_z_index == 0);

            REQUIRE(cel_data.m_cell_width == 9);
            REQUIRE(cel_data.m_cell_height == 14);

            REQUIRE(cel_data.m_pixels_rgba.size() == 126);

            REQUIRE(cel_data.m_pixels_rgba.front() == PixelDataRGBA { 0, 0, 0, 0 });
        }
    }
}
