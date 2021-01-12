#include "lib.h"
#include <catch2/catch.hpp>

TEST_CASE("Product version shouldn't be a zero")
{
    REQUIRE(version() != 0U);
}