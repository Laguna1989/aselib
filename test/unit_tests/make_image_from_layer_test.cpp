#include "catch2/catch.hpp"
#include <aselib/aseprite_data.hpp>
#include <aselib/image_builder.hpp>
#include <fstream>

using namespace aselib;

TEST_CASE("make image from layer for aseprite file with one layer", "[image, layer]")
{
    AsepriteData const ase { "assets/test/unit/dino_salto.aseprite" };

    SECTION("throws for non existing layer")
    {
        REQUIRE_THROWS(makeImageFromLayer(ase, "non existing layer"));
    }

    SECTION("results in correct pixels for existing layer")
    {
        auto const img = makeImageFromLayer(ase, "Layer 1");

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
}

TEST_CASE("make image from layer for aseprite file with multiple layers", "[image, layer]")
{
    AsepriteData const ase { "assets/test/unit/miner.aseprite" };

    SECTION("throws for non existing layer")
    {
        REQUIRE_THROWS(makeImageFromLayer(ase, "non existing layer"));
    }

    SECTION("results in correct pixels for main layer")
    {
        auto const img = makeImageFromLayer(ase, "main");

        REQUIRE(img.m_width == 320);
        REQUIRE(img.m_height == 32);

        REQUIRE(img.m_pixels[img.posToIndex(16, 24)] == PixelDataRGBA { 248, 192, 144, 255 });
    }

    SECTION("results in correct pixels for outline layer")
    {
        auto const img = makeImageFromLayer(ase, "outline");

        REQUIRE(img.m_width == 320);
        REQUIRE(img.m_height == 32);

        REQUIRE(img.m_pixels[img.posToIndex(16, 24)] == PixelDataRGBA { 0, 0, 0, 0 });
    }
}
