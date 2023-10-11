#include "catch2/catch.hpp"
#include <aselib/pixel_data.hpp>

using namespace aselib;

TEST_CASE("pixel data comparison", "[PixelData]")
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
