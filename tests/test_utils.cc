#include <catch.hpp>

#include <pixl/types.h>
#include <pixl/utils.h>

TEST_CASE("Swapping arrays", "[aswap]") {
    pixl::u8 a[] = {1, 2, 3};
    pixl::u8 b[] = {4, 5, 6};
    pixl::aswap(a, b, 2);

    REQUIRE(a[0] == 4);
    REQUIRE(a[1] == 5);
    REQUIRE(a[2] == 3);
    REQUIRE(b[0] == 1);
    REQUIRE(b[1] == 2);
    REQUIRE(b[2] == 6);
}