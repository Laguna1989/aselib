#include "catch2/catch.hpp"
#include <aselib/aseprite_data.hpp>

using namespace aselib;

TEST_CASE(
    "AsepriteData Constructor raises exception when called invalid filepath", "[AsepriteData]")
{
    REQUIRE_THROWS(AsepriteData { "non-existing_file&&++:," });
}
