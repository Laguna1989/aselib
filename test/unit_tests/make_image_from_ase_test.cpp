#include "catch2/catch.hpp"
#include <aselib/aseprite_data.hpp>
#include <aselib/image_builder.hpp>
#include <fstream>

using namespace aselib;

TEST_CASE("make image from ase with one layer", "[image]")
{
    AsepriteData const ase { "assets/test/unit/dino_salto.aseprite" };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 408);
    REQUIRE(img.m_height == 18);

    REQUIRE(img.m_pixels[img.posToIndex(0, 0)] == PixelDataRGBA { 0, 0, 0, 0 });
    REQUIRE(img.m_pixels[img.posToIndex(8, 7)] == PixelDataRGBA { 40, 87, 63, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(32, 6)] == PixelDataRGBA { 40, 87, 63, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(83, 10)] == PixelDataRGBA { 25, 46, 27, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(270, 12)] == PixelDataRGBA { 138, 122, 87, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(401, 14)] == PixelDataRGBA { 40, 87, 63, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(407, 17)] == PixelDataRGBA { 0, 0, 0, 0 });
}

TEST_CASE("make image from ase with multiple layers", "[image]")
{
    AsepriteData const ase { "assets/test/unit/miner.aseprite" };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 320);
    REQUIRE(img.m_height == 32);

    REQUIRE(img.m_pixels[img.posToIndex(16, 24)] == PixelDataRGBA { 248, 192, 144, 255 });
}

TEST_CASE("make image from ase with two layers and opacity", "[image]")
{
    AsepriteData const ase {
        "assets/test/unit/32_bit_2x2_white_with_transparent_overlay.aseprite"
    };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 2);
    REQUIRE(img.m_height == 2);

    REQUIRE(img.getPixelAt(0, 0) == PixelDataRGBA { 255, 155, 155, 255 });
    REQUIRE(img.getPixelAt(1, 0) == PixelDataRGBA { 155, 255, 155, 255 });
    REQUIRE(img.getPixelAt(0, 1) == PixelDataRGBA { 255, 255, 255, 255 });
    REQUIRE(img.getPixelAt(1, 1) == PixelDataRGBA { 155, 155, 255, 255 });
}
