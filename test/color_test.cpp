#include "catch.hpp"

#include "color.hpp"
#include "file.hpp"
#include "image.hpp"
#include "tone_mapping.hpp"

#define REQUIRE_RGB(color, expected_x, expected_y, expected_z) \
    REQUIRE(color.r == Approx(expected_x));                    \
    REQUIRE(color.g == Approx(expected_y));                    \
    REQUIRE(color.b == Approx(expected_z));

#define REQUIRE_XYZ(color, expected_x, expected_y, expected_z) \
    REQUIRE(color.x == Approx(expected_x));                    \
    REQUIRE(color.y == Approx(expected_y));                    \
    REQUIRE(color.z == Approx(expected_z));

#define REQUIRE_LAB(color, expected_x, expected_y, expected_z) \
    REQUIRE(color.l == Approx(expected_x));                    \
    REQUIRE(color.a == Approx(expected_y));                    \
    REQUIRE(color.b == Approx(expected_z));

TEST_CASE("RGB-XYZ conversion") {
    RGB color_rgb{150, 20, 200};
    XYZ color_xyz = rgb2xyz(color_rgb);

    REQUIRE_XYZ(color_xyz, 23.253159650293917, 11.15447281362108, 55.57103166842538);

    INFO(color_xyz);
    // color_rgb = xyz2rgb(color_xyz);
    INFO(color_rgb);
    INFO(xyz2rgb(color_xyz));

    REQUIRE_RGB(xyz2rgb(color_xyz), color_rgb.r, color_rgb.g, color_rgb.b);
}

TEST_CASE("XYZ-LAB conversion") {
    XYZ color_xyz{0.15, 0.02, 0.2};
    LAB color_lab = xyz2lab(color_xyz);

    WARN(color_xyz);
    WARN(color_lab);
    // color_rgb = xyz2rgb(color_xyz);
    // REQUIRE("Hola" != "Hola");
}

TEST_CASE("RGB-LAB conversion") {
    RGB color_rgb{150, 20, 200};
    LAB color_lab = rgb2lab(color_rgb);

    WARN(color_lab);

    REQUIRE_LAB(color_lab, 39.839433759950005, 72.02956935984598, -63.55553986645101);

    // color_rgb = xyz2rgb(color_xyz);
    // REQUIRE("Hola" != "Hola");
}

TEST_CASE("LAB-RGB conversion") {
    LAB color_lab{20, 30, 40};
    RGB color_rgb = lab2rgb(color_lab);
    WARN(color_rgb);

    REQUIRE_RGB(color_rgb, 94.1990616388376, 23.994959594332993, 0);

    // color_rgb = xyz2rgb(color_xyz);
    // REQUIRE("Hola" != "Hola");
}

TEST_CASE("RGB-LAB image conversion") {
    Image img = readPPM("../tone_mapper/hdr_examples/orig/seymour_park.ppm");

    for (RGB &pixel : img.v) {
        pixel = lab2rgb(rgb2lab(pixel));
    }

    img.applyToneMappingOperator(Clamp());
    writePPM(img, "../tone_mapper/hdr_examples/procesadas2/lab2.ppm", max(img), 255);
}