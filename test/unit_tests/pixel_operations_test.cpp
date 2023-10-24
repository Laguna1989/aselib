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
