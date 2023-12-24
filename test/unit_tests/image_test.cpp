#include <aselib/image.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Image Test")
{
    SECTION("const image")
    {
        aselib::Image const image { 2u, 2u,
            std::vector<aselib::PixelDataRGBA> {
                // clang-format off
            aselib::PixelDataRGBA {255u,255u,255u,255u},
            aselib::PixelDataRGBA {255u,255u,255u,255u},
            aselib::PixelDataRGBA {255u,255u,255u,255u},
            aselib::PixelDataRGBA {255u,255u,255u,255u}
                // clang-format on
            } };

        SECTION("getPixelAt valid position")
        {
            auto const x = GENERATE(0, 1);
            auto const y = GENERATE(0, 1);
            REQUIRE(image.getPixelAt(x, y) == aselib::PixelDataRGBA { 255u, 255u, 255u, 255u });
        }

        SECTION("getPixelAt invalid position") { REQUIRE_THROWS(image.getPixelAt(500, 400)); }
    }

    SECTION("mutable image")
    {
        aselib::Image image { 2u, 2u,
            std::vector<aselib::PixelDataRGBA> {
                // clang-format off
                aselib::PixelDataRGBA {255u,255u,255u,255u},
                aselib::PixelDataRGBA {255u,255u,255u,255u},
                aselib::PixelDataRGBA {255u,255u,255u,255u},
                aselib::PixelDataRGBA {255u,255u,255u,255u}
                // clang-format on
            } };

        SECTION("getPixelAt valid position")
        {
            auto const x = GENERATE(0, 1);
            auto const y = GENERATE(0, 1);
            image.getPixelAt(x, y) = aselib::PixelDataRGBA { 100u, 100u, 100u, 255u };
            REQUIRE(image.getPixelAt(x,y) ==aselib::PixelDataRGBA { 100u, 100u, 100u, 255u });
        }

        SECTION("getPixelAt invalid position") { REQUIRE_THROWS(image.getPixelAt(500, 400)); }
    }


}
