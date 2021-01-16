#include "lib.h"
#include <catch2/catch.hpp>

TEST_CASE("Product version shouldn't be a zero", "[version]")
{
    REQUIRE(version() != 0U);
}