#include "catch.hpp"

#include "geometry.cpp"

TEST_CASE("Prueba de vectores 3") {
    REQUIRE(modulus(Vector3(1, 2, 3)) == (float)sqrt(14));
}
