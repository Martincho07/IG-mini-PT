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

#include <iostream>

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
};

inline std::istream &operator>>(std::istream &in, RGB &c) {
    in >> c.r >> c.g >> c.b;
    return in;
};

inline std::ostream &operator<<(std::ostream &out, const RGB &c) {
    out << c.r << " " << c.g << " " << c.b;
    return out;
};
