#include "aselib/constants.hpp"
#include "catch2/catch.hpp"
#include <aselib/aseprite_data.hpp>
#include <aselib/image_builder.hpp>
#include <fstream>

using namespace aselib;

TEST_CASE("make image from rgba ase with one layer", "[image, rgba]")
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

TEST_CASE("make image from horizontal grayscale ase with one layer", "[image, grayscale]")
{
    AsepriteData const ase { "assets/test/unit/16_bit_8x1_transition.aseprite" };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 8);
    REQUIRE(img.m_height == 1);

    REQUIRE(img.m_pixels[img.posToIndex(0, 0)] == PixelDataRGBA { 0, 0, 0, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(1, 0)] == PixelDataRGBA { 0x55, 0x55, 0x55, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(2, 0)] == PixelDataRGBA { 0x73, 0x73, 0x73, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(3, 0)] == PixelDataRGBA { 0x9b, 0x9b, 0x9b, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(4, 0)] == PixelDataRGBA { 0xb4, 0xb4, 0xb4, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(5, 0)] == PixelDataRGBA { 0xcd, 0xcd, 0xcd, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(6, 0)] == PixelDataRGBA { 0xf0, 0xf0, 0xf0, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(7, 0)] == PixelDataRGBA { 0xff, 0xff, 0xff, 255 });
}

TEST_CASE("make image from vertical grayscale ase with one layer", "[image, grayscale]")
{
    AsepriteData const ase { "assets/test/unit/16_bit_1x8_transition.aseprite" };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 1);
    REQUIRE(img.m_height == 8);

    REQUIRE(img.m_pixels[img.posToIndex(0, 0)] == PixelDataRGBA { 0, 0, 0, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(0, 1)] == PixelDataRGBA { 0x55, 0x55, 0x55, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(0, 2)] == PixelDataRGBA { 0x73, 0x73, 0x73, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(0, 3)] == PixelDataRGBA { 0x9b, 0x9b, 0x9b, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(0, 4)] == PixelDataRGBA { 0xb4, 0xb4, 0xb4, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(0, 5)] == PixelDataRGBA { 0xcd, 0xcd, 0xcd, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(0, 6)] == PixelDataRGBA { 0xf0, 0xf0, 0xf0, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(0, 7)] == PixelDataRGBA { 0xff, 0xff, 0xff, 255 });
}

TEST_CASE("make image from indexed ase with one layer", "[image, indexed]")
{
    AsepriteData const ase { "assets/test/unit/8_bit_4x1_indexed.aseprite" };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 4);
    REQUIRE(img.m_height == 1);

    REQUIRE(img.getPixelAt(0, 0) == PixelDataRGBA { 0, 0, 0, 255 });
    REQUIRE(img.getPixelAt(1, 0) == PixelDataRGBA { 0, 170, 0, 255 });
    REQUIRE(img.getPixelAt(2, 0) == PixelDataRGBA { 170, 0, 0, 255 });
    REQUIRE(img.getPixelAt(3, 0) == PixelDataRGBA { 170, 85, 0, 255 });
}

TEST_CASE("make image from rgba ase with multiple layers", "[image, rgba]")
{
    AsepriteData const ase { "assets/test/unit/miner.aseprite" };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 320);
    REQUIRE(img.m_height == 32);

    REQUIRE(img.getPixelAt(16, 24) == PixelDataRGBA { 248, 192, 144, 255 });
    REQUIRE(img.getPixelAt(14, 15) == PixelDataRGBA { 43, 41, 40, 255 });
}

TEST_CASE("make image from rgba ase with multiple layers and invisible layer", "[image, rgba]")
{
    AsepriteData const ase { "assets/test/unit/miner_transparent_outline.aseprite" };

    auto const img = makeImageFromAse(ase, false);

    REQUIRE(img.m_width == 320);
    REQUIRE(img.m_height == 32);

    REQUIRE(img.m_pixels[img.posToIndex(16, 24)] == PixelDataRGBA { 248, 192, 144, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(14, 15)] == PixelDataRGBA { 0, 0, 0, 0 });
}

TEST_CASE("make image from rgba ase with two layers and opacity", "[image, rgba]")
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

TEST_CASE("make image from ase exception test", "[image, exception]")
{
    AsepriteData ase { "assets/test/unit/32_bit_2x2_white_with_transparent_overlay.aseprite" };

    SECTION("no frames")
    {
        ase.m_frames.clear();
        REQUIRE_THROWS(makeImageFromAse(ase));
    }

    SECTION("invalid color depth")
    {
        ase.m_header.m_color_depth = 7;
        REQUIRE_THROWS(makeImageFromAse(ase));
    }
}
