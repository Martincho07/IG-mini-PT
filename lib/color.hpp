/*********************************************************************************
 * Color
 *
 * File: color.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "math.h"
#include <algorithm>
#include <initializer_list>
#include <iostream>

// Reinhard constants for pixel luminity
#define LUMINANCE_R 0.27f
#define LUMINANCE_G 0.67f
#define LUMINANCE_B 0.06f

struct RGB {
    float r, g, b;

    // Constructors
    RGB(){};

    RGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b){};

    // Operators

    RGB operator+(const RGB c) const {
        return RGB(r + c.r, g + c.g, b + c.b);
    };

    RGB operator*(const RGB c) const {
        return RGB(r * c.r, g * c.g, b * c.b);
    };

    RGB operator*(float s) const {
        return RGB(r * s, g * s, b * s);
    };

    RGB operator/(float s) const {
        return RGB(r / s, g / s, b / s);
    };

    float L() const {
        return (LUMINANCE_R * r) + (LUMINANCE_G * g) + (LUMINANCE_B * b);
    };
};

inline std::istream &operator>>(std::istream &in, RGB &c) {
    in >> c.r >> c.g >> c.b;
    return in;
};

inline std::ostream &operator<<(std::ostream &out, const RGB &c) {
    out << c.r << " " << c.g << " " << c.b;
    return out;
};

RGB round(const RGB &c);

float max(const RGB &c);
float min(const RGB &c);

RGB pow(const RGB &c, float s);

/*
 *
 * Convert float pixel to rgbe
 */
void float2rgbe(const RGB &c, unsigned char rgbe[4]);
