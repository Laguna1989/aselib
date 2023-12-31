#include <aselib/pixel_data.hpp>
#include <catch2/catch.hpp>

using namespace aselib;

TEST_CASE("pixel data rgba comparison", "[PixelDataRGBA]")
{
    PixelDataRGBA p1 { 255, 255, 255, 255 };
    PixelDataRGBA p2 { 255, 255, 255, 255 };

    PixelDataRGBA q1 { 100, 255, 255, 255 };
    PixelDataRGBA q2 { 255, 100, 255, 255 };
    PixelDataRGBA q3 { 255, 255, 100, 255 };
    PixelDataRGBA q4 { 255, 255, 255, 100 };

    SECTION("operator==")
    {
        REQUIRE(p1 == p2);
        REQUIRE(p2 == p1);

        REQUIRE(!(p1 == q1));
        REQUIRE(!(p1 == q2));
        REQUIRE(!(p1 == q3));
        REQUIRE(!(p1 == q4));
    }

    SECTION("operator!=")
    {
        REQUIRE(!(p1 != p2));
        REQUIRE(!(p2 != p1));

        REQUIRE(p1 != q1);
        REQUIRE(p1 != q2);
        REQUIRE(p1 != q3);
        REQUIRE(p1 != q4);
    }
}

TEST_CASE("pixel data grayscale comparison", "[PixelDataGrayscale]")
{
    PixelDataGrayscale p1 { 255, 255 };
    PixelDataGrayscale p2 { 255, 255 };

    PixelDataGrayscale q1 { 100, 255 };
    PixelDataGrayscale q2 { 255, 100 };

    SECTION("operator==")
    {
        REQUIRE(p1 == p2);
        REQUIRE(p2 == p1);

        REQUIRE(!(p1 == q1));
        REQUIRE(!(p1 == q2));
    }

    SECTION("operator!=")
    {
        REQUIRE(!(p1 != p2));
        REQUIRE(!(p2 != p1));

        REQUIRE(p1 != q1);
        REQUIRE(p1 != q2);
    }
}
