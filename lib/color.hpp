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

#include "geometry.hpp"

#include <algorithm>
#include <cmath>
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

struct XYZ {
    float x, y, z;
    XYZ(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
        if (isnan(x) || isnan(y) || isnan(z)) {
            std::cout << x << " " << y << " " << z << std::endl;
            exit(1);
        }
    }
};
inline std::ostream &operator<<(std::ostream &out, const XYZ &c) {
    out << c.x << " " << c.y << " " << c.z;
    return out;
};

struct LAB {
    float l, a, b;
    LAB(float _l, float _a, float _b) : l(_l), a(_a), b(_b) {
        if (isnan(l) || isnan(a) || isnan(b)) {
            std::cout << l << " " << a << " " << b << std::endl;
            exit(1);
        }
    }
};
inline std::ostream &operator<<(std::ostream &out, const LAB &c) {
    out << c.l << " " << c.a << " " << c.b;
    return out;
};

/*
 *
 * Convert float pixel to rgbe
 */
void float2rgbe(const RGB &c, unsigned char rgbe[4]);

/*
 * Color conversions. Adapted from http://www.easyrgb.com
 * Standard-RGB. X, Y and Z input refer to a D65/2o standard illuminant
 */
#define REFERENCE_X 96.0489f
#define REFERENCE_Y 100.0f
#define REFERENCE_Z 108.8840f

XYZ rgb2xyz(const RGB &c);
RGB xyz2rgb(const XYZ &c);

LAB xyz2lab(const XYZ &c);
XYZ lab2xyz(const LAB &c);

LAB rgb2lab(const RGB &c);
RGB lab2rgb(const LAB &c);