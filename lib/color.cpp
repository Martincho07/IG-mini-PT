/*********************************************************************************
 * Color
 *
 * File: color.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "color.hpp"
#include "math.h"
#include <cfloat>

RGB round(const RGB &c) {
    return RGB(round(c.r), round(c.g), round(c.b));
}

float max(const RGB &c) {
    float max = c.r;
    if (max < c.g)
        max = c.g;
    if (max < c.b)
        max = c.b;
    return max;
}

float min(const RGB &c) {
    float min = c.r;
    if (min > c.g)
        min = c.g;
    if (min > c.b)
        min = c.b;
    return min;
}

RGB pow(const RGB &c, float s) {
    return RGB(pow(c.r, s), pow(c.g, s), pow(c.b, s));
};

void float2rgbe(const RGB &c, unsigned char rgbe[4]) {
    float v;
    int e;
    v = max(c);
    if (v < FLT_MIN) {
        rgbe[0] = rgbe[1] = rgbe[2] = rgbe[3] = 0;
    } else {
        v = frexp(v, &e) * 256.0f / v;
        rgbe[0] = (unsigned char)(c.r * v);
        rgbe[1] = (unsigned char)(c.g * v);
        rgbe[2] = (unsigned char)(c.b * v);
        rgbe[3] = (unsigned char)(e + 128);
    }
}

XYZ rgb2xyz(const RGB &c) {
    float var_R = (c.r / 255.0f);
    float var_G = (c.g / 255.0f);
    float var_B = (c.b / 255.0f);

    if (var_R > 0.04045f)
        var_R = pow((var_R + 0.055f) / 1.055f, 2.4f);
    else
        var_R = var_R / 12.92f;
    if (var_G > 0.04045f)
        var_G = pow((var_G + 0.055f) / 1.055f, 2.4f);
    else
        var_G = var_G / 12.92f;
    if (var_B > 0.04045f)
        var_B = pow((var_B + 0.055f) / 1.055f, 2.4f);
    else
        var_B = var_B / 12.92f;

    var_R = var_R * 100.0f;
    var_G = var_G * 100.0f;
    var_B = var_B * 100.0f;

    return XYZ(var_R * 0.4124f + var_G * 0.3576f + var_B * 0.1805f,
               var_R * 0.2126f + var_G * 0.7152f + var_B * 0.0722f,
               var_R * 0.0193f + var_G * 0.1192f + var_B * 0.9505f);
}

RGB xyz2rgb(const XYZ &c) {
    float var_X = c.x / 100.0f;
    float var_Y = c.y / 100.0f;
    float var_Z = c.z / 100.0f;

    float var_R = var_X * 3.2406f + var_Y * -1.5372f + var_Z * -0.4986f;
    float var_G = var_X * -0.9689f + var_Y * 1.8758f + var_Z * 0.0415f;
    float var_B = var_X * 0.0557f + var_Y * -0.2040f + var_Z * 1.0570f;

    if (var_R > 0.0031308f)
        var_R = 1.055f * pow(var_R, (1.0f / 2.4f)) - 0.055f;
    else
        var_R = 12.92f * var_R;
    if (var_G > 0.0031308f)
        var_G = 1.055f * pow(var_G, (1.0f / 2.4f)) - 0.055f;
    else
        var_G = 12.92f * var_G;
    if (var_B > 0.0031308f)
        var_B = 1.055f * pow(var_B, (1.0f / 2.4f)) - 0.055f;
    else
        var_B = 12.92f * var_B;

    return RGB(var_R <= 0.0 ? 0.0 : var_R * 255.0f,
               var_G <= 0.0 ? 0.0 : var_G * 255.0f,
               var_B <= 0.0 ? 0.0 : var_B * 255.0f);
}

LAB xyz2lab(const XYZ &c) {
    // return LAB(c.y,
    //            c.x / (c.x + c.y + c.z),
    //            c.y / (c.x + c.y + c.z));

    float var_X = c.x / REFERENCE_X;
    float var_Y = c.y / REFERENCE_Y;
    float var_Z = c.z / REFERENCE_Z;

    float delta = 6.0f / 29.0f;

    if (var_X > pow(delta, 3.0f))
        var_X = pow(var_X, (1.0f / 3.0f));
    else
        var_X = ( (1.0f / (3.0f * pow(delta, 2.0f))) * var_X) + (4.0f / 29.0f);

    if (var_Y > pow(delta, 3.0f))
        var_Y = pow(var_Y, (1.0f / 3.0f));
    else
        var_Y = ((1.0f / (3.0f * pow(delta, 2.0f))) * var_Y) + (4.0f / 29.0f);

    if (var_Z > pow(delta, 3.0f))
        var_Z = pow(var_Z, (1.0f / 3.0f));
    else
        var_Z = ((1.0f / (3.0f * pow(delta, 2.0f))) * var_Z) + (4.0f / 29.0f);

    return LAB((116.0f * var_Y) - 16.0f,
               500.0f * (var_X - var_Y),
               200.0f * (var_Y - var_Z));
}

XYZ lab2xyz(const LAB &c) {
    // return XYZ(c.a * (c.l / c.b),
    //            c.l,
    //            (1 - c.a - c.b) * (c.l / c.b));

    float var_Y = (c.l + 16.0f) / 116.0f;
    float var_X = (c.a / 500.0f) + var_Y;
    float var_Z = var_Y - (c.b / 200.0f);

    float delta = 6.0f / 29.0f;

    if (var_Y > delta)
        var_Y = pow(var_Y, 3.0f);
    else
        var_Y = (var_Y - (4.0f / 29.0f)) * (3.0f * pow(delta, 2.0f));

    if (var_Y > delta)
        var_X = pow(var_X, 3.0f);
    else
        var_X = (var_X - (4.0f / 29.0f)) * (3.0f * pow(delta, 2.0f));

    if (var_Y > delta)
        var_Z = pow(var_Z, 3.0f);
    else
        var_Z = (var_Z - (4.0f / 29.0f)) * (3.0f * pow(delta, 2.0f));

    return XYZ(var_X <= 0 ? 0.0 : var_X * REFERENCE_X,
               var_Y <= 0 ? 0.0 : var_Y * REFERENCE_Y,
               var_Z <= 0 ? 0.0 : var_Z * REFERENCE_Z);
}

LAB rgb2lab(const RGB &c) {
    return xyz2lab(rgb2xyz(c));
}
RGB lab2rgb(const LAB &c) {
    return xyz2rgb(lab2xyz(c));
}