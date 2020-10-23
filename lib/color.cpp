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