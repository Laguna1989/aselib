#include "catch2/catch.hpp"
#include <aselib/aseprite_data.hpp>
#include <aselib/image_builder.hpp>
#include <fstream>

using namespace aseprite_lib;

TEST_CASE("makeImageFromAse", "[image]")
{
    AsepriteData const ase { "assets/test/unit/dino_salto.aseprite" };

    auto const img = makeImageFromAse(ase);

    REQUIRE(img.m_width == 408);
    REQUIRE(img.m_height == 18);

    REQUIRE(img.m_pixels[img.posToIndex(0, 0)].r == 0);
    REQUIRE(img.m_pixels[img.posToIndex(0, 0)].g == 0);
    REQUIRE(img.m_pixels[img.posToIndex(0, 0)].b == 0);
    REQUIRE(img.m_pixels[img.posToIndex(0, 0)].a == 0);

    REQUIRE(img.m_pixels[img.posToIndex(8, 7)].r == 40);
    REQUIRE(img.m_pixels[img.posToIndex(8, 7)].g == 87);
    REQUIRE(img.m_pixels[img.posToIndex(8, 7)].b == 63);
    REQUIRE(img.m_pixels[img.posToIndex(8, 7)].a == 255);

    REQUIRE(img.m_pixels[img.posToIndex(32, 6)].r == 40);
    REQUIRE(img.m_pixels[img.posToIndex(32, 6)].g == 87);
    REQUIRE(img.m_pixels[img.posToIndex(32, 6)].b == 63);
    REQUIRE(img.m_pixels[img.posToIndex(32, 6)].a == 255);

    REQUIRE(img.m_pixels[img.posToIndex(83, 10)].r == 25);
    REQUIRE(img.m_pixels[img.posToIndex(83, 10)].g == 46);
    REQUIRE(img.m_pixels[img.posToIndex(83, 10)].b == 27);
    REQUIRE(img.m_pixels[img.posToIndex(83, 10)].a == 255);

    REQUIRE(img.m_pixels[img.posToIndex(270, 12)].r == 138);
    REQUIRE(img.m_pixels[img.posToIndex(270, 12)].g == 122);
    REQUIRE(img.m_pixels[img.posToIndex(270, 12)].b == 87);
    REQUIRE(img.m_pixels[img.posToIndex(270, 12)].a == 255);

    REQUIRE(img.m_pixels[img.posToIndex(401, 14)].r == 40);
    REQUIRE(img.m_pixels[img.posToIndex(401, 14)].g == 87);
    REQUIRE(img.m_pixels[img.posToIndex(401, 14)].b == 63);
    REQUIRE(img.m_pixels[img.posToIndex(401, 14)].a == 255);

    REQUIRE(img.m_pixels[img.posToIndex(407, 17)].r == 0);
    REQUIRE(img.m_pixels[img.posToIndex(407, 17)].g == 0);
    REQUIRE(img.m_pixels[img.posToIndex(407, 17)].b == 0);
    REQUIRE(img.m_pixels[img.posToIndex(407, 17)].a == 0);
}
