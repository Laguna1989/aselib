#include "aselib/constants.hpp"
#include "catch2/catch.hpp"
#include <aselib/aseprite_data.hpp>
#include <aselib/image_builder.hpp>
#include <fstream>

using namespace aselib;

TEST_CASE("make image from rgba ase with one layer", "[image]")
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

TEST_CASE("make image from grayscale ase with one layer", "[image]")
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

TEST_CASE("make image from ase with multiple layers", "[image]")
{
    AsepriteData ase { "assets/test/unit/miner.aseprite" };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 320);
    REQUIRE(img.m_height == 32);

    REQUIRE(img.getPixelAt(16, 24) == PixelDataRGBA { 248, 192, 144, 255 });
    REQUIRE(img.getPixelAt(14, 15) == PixelDataRGBA { 43, 41, 40, 255 });
}

TEST_CASE("make image from ase with multiple layers and invisible layer", "[image]")
{
    AsepriteData ase { "assets/test/unit/miner.aseprite" };

    for (auto& layer : ase.m_frames[0].m_chunks.m_layers_chunks) {
        if (layer.m_layer_name == "outline") {
            layer.m_layer_flags
                = aselib::layer_flags::editable | aselib::layer_flags::lock_movement;
            break;
        }
    }

    auto const img = makeImageFromAse(ase, false);

    REQUIRE(img.m_width == 320);
    REQUIRE(img.m_height == 32);

    REQUIRE(img.m_pixels[img.posToIndex(16, 24)] == PixelDataRGBA { 248, 192, 144, 255 });
    REQUIRE(img.m_pixels[img.posToIndex(14, 15)] == PixelDataRGBA { 0, 0, 0, 0 });
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
