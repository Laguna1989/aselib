#include <aselib/chunks/palette_chunk.hpp>
#include <aselib/pixel_operations.hpp>
#include <catch2/catch.hpp>

using namespace aselib;

TEST_CASE("pixel operations rgba and rgba", "[PixelData, Pixel Operations, rgba]")
{
    SECTION("No Mixing")
    {
        auto const color_a_r_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
        auto const color_a_g_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
        auto const color_a_b_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);

        auto const color_b_r_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
        auto const color_b_g_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
        auto const color_b_b_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);

        SECTION("full alpha on both colors")
        {
            auto const a = PixelDataRGBA { color_a_r_value, color_a_g_value, color_a_b_value, 255 };
            auto const b = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 255 };

            auto const resulting_pixel = add_pixel_color(a, b);
            REQUIRE(resulting_pixel == a);
        }

        SECTION("full alpha on source, 0 on destination")
        {
            auto const a = PixelDataRGBA { color_a_r_value, color_a_g_value, color_a_b_value, 0 };
            auto const b = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 255 };

            auto const resulting_pixel = add_pixel_color(a, b);
            REQUIRE(resulting_pixel == b);
        }

        SECTION("full alpha on destination, 0 on source")
        {
            auto const a = PixelDataRGBA { color_a_r_value, color_a_g_value, color_a_b_value, 255 };
            auto const b = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 0 };

            auto const resulting_pixel = add_pixel_color(a, b);
            REQUIRE(resulting_pixel == a);
        }
    }
    SECTION("Mixing Colors")
    {
        PixelDataRGBA const a { 255, 200, 200, 255 };
        PixelDataRGBA const b { 255, 100, 0, 100 };

        auto const resulting_pixel = add_pixel_color(b, a);
        auto const expected_color = PixelDataRGBA { 255, 160, 121, 255 };
        REQUIRE(resulting_pixel == expected_color);
    }
}

TEST_CASE("pixel operations grayscale and rgba", "[PixelData, Pixel Operations, grayscale, rgba]")
{
    SECTION("No Mixing")
    {
        auto const color_a_v_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);

        auto const color_b_r_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
        auto const color_b_g_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
        auto const color_b_b_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);

        SECTION("full alpha on both colors")
        {
            auto const a = PixelDataGrayscale { color_a_v_value, 255 };
            auto const b = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 255 };

            auto const resulting_pixel = add_pixel_color(a, b);
            REQUIRE(resulting_pixel
                == PixelDataRGBA { color_a_v_value, color_a_v_value, color_a_v_value, 255 });
        }

        SECTION("full alpha on source, 0 on destination")
        {
            auto const a = PixelDataGrayscale { color_a_v_value, 0 };
            auto const b = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 255 };

            auto const resulting_pixel = add_pixel_color(a, b);
            REQUIRE(resulting_pixel == b);
        }

        SECTION("full alpha on destination, 0 on source")
        {
            auto const a = PixelDataGrayscale { color_a_v_value, 255 };
            auto const b = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 0 };

            auto const resulting_pixel = add_pixel_color(a, b);
            REQUIRE(resulting_pixel
                == PixelDataRGBA { color_a_v_value, color_a_v_value, color_a_v_value, 255 });
        }
    }
    SECTION("Mixing Colors")
    {
        PixelDataGrayscale const a { 100, 100 };
        PixelDataRGBA const b { 255, 100, 0, 255 };

        auto const resulting_pixel = add_pixel_color(a, b);
        auto const expected_color = PixelDataRGBA { 194, 100, 39, 255 };
        REQUIRE(resulting_pixel == expected_color);
    }
}

TEST_CASE("pixel operations indexed and rgba", "[PixelData, Pixel Operations, grayscale, rgba]")
{
    SECTION("With valid palette")
    {
        PaletteChunk palette {};
        palette.m_palette_entries.push_back(PaletteEntry { 0, PixelDataRGBA { 0, 0, 0, 255 }, "" });
        palette.m_palette_entries.push_back(
            PaletteEntry { 0, PixelDataRGBA { 170, 0, 0, 255 }, "" });
        palette.m_palette_entries.push_back(
            PaletteEntry { 0, PixelDataRGBA { 0, 170, 0, 255 }, "" });
        palette.m_palette_entries.push_back(
            PaletteEntry { 0, PixelDataRGBA { 0, 0, 170, 255 }, "" });

        palette.m_palette_entries.push_back(PaletteEntry { 0, PixelDataRGBA { 0, 0, 0, 0 }, "" });
        palette.m_palette_entries.push_back(PaletteEntry { 0, PixelDataRGBA { 170, 0, 0, 0 }, "" });
        palette.m_palette_entries.push_back(PaletteEntry { 0, PixelDataRGBA { 0, 170, 0, 0 }, "" });
        palette.m_palette_entries.push_back(PaletteEntry { 0, PixelDataRGBA { 0, 0, 170, 0 }, "" });

        palette.m_palette_entries.push_back(
            PaletteEntry { 0, PixelDataRGBA { 100, 200, 255, 100 }, "" });

        SECTION("No Mixing")
        {
            auto const color_a_idx_value = GENERATE(
                std::uint8_t { 0u }, std::uint8_t { 1u }, std::uint8_t { 2u }, std::uint8_t { 3u });

            auto const color_b_r_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
            auto const color_b_g_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
            auto const color_b_b_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);

            SECTION("full alpha on both colors")
            {
                auto const a = PixelDataIndexed { color_a_idx_value };
                auto const b
                    = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 255 };

                auto const resulting_pixel = add_pixel_color(a, b, palette);
                REQUIRE(resulting_pixel == palette.m_palette_entries.at(color_a_idx_value).m_color);
            }

            SECTION("full alpha on source, 0 on destination")
            {
                // first 4 colors in palette are full opacity
                // second 4 colors in palette are full transparent
                auto const a = PixelDataIndexed { static_cast<std::uint8_t>(
                    color_a_idx_value + static_cast<std::uint8_t>(4u)) };
                auto const b
                    = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 255 };

                auto const resulting_pixel = add_pixel_color(a, b, palette);
                REQUIRE(resulting_pixel == b);
            }

            SECTION("full alpha on destination, 0 on source")
            {
                auto const a = PixelDataIndexed { color_a_idx_value };
                auto const b
                    = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 0 };

                auto const resulting_pixel = add_pixel_color(a, b, palette);
                REQUIRE(resulting_pixel == palette.m_palette_entries.at(color_a_idx_value).m_color);
            }
        }

        SECTION("Mixing Colors")
        {
            PixelDataIndexed const a { 8u };
            PixelDataRGBA const b { 255, 100, 0, 255 };

            auto const resulting_pixel = add_pixel_color(a, b, palette);
            auto const expected_color = PixelDataRGBA { 194, 139, 100, 255 };
            REQUIRE(resulting_pixel == expected_color);
        }
    }
    SECTION("exceeding palette")
    {
        PaletteChunk palette {};

        auto const color_a_idx_value = GENERATE(
            std::uint8_t { 0u }, std::uint8_t { 1u }, std::uint8_t { 2u }, std::uint8_t { 3u });

        auto const color_b_r_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
        auto const color_b_g_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);
        auto const color_b_b_value = GENERATE(std::uint8_t { 0u }, 1u, 200u, 255u);

        SECTION("add_pixel_color raises exception for index out of palette range")
        {
            auto const a = PixelDataIndexed { color_a_idx_value };
            auto const b = PixelDataRGBA { color_b_r_value, color_b_g_value, color_b_b_value, 255 };

            REQUIRE_THROWS(add_pixel_color(a, b, palette));
        }
    }
}
