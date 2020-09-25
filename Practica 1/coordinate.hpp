/*********************************************************************************
 * Representation of homogeneous coordinates
 *
 * File: coordinate.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once
#include <iostream>

struct HCoord
{
    const union
    {
        struct
        {
            float x, y, z, w;
        };
        float c[4];
    };

    // HCoord() {};

    // HCoord(float x, float y, float z, float w)
    // {
    //     this->x = x;
    //     this->y = y;
    //     this->z = z;
    //     this->w = w;
    // };

    // point + point         = ERROR
    // point + direction     = point
    // direction + point     = point
    // direction + direction = direction
    HCoord operator+(const HCoord &right) const;

    // point - point         = direction
    // point - direction     = point
    // direction - point     = ERROR
    // direction - direction = direction
    HCoord operator-(const HCoord &right) const;

    // point * scalar = ERROR
    // direction * scalar = direction
    HCoord operator*(const float right) const;

    // point / scalar = ERROR
    // direction / scalar = direction
    HCoord operator/(const float right) const;

    // inline
    // constexpr
};

HCoord point(float x, float y, float z);
HCoord direction(float x, float y, float z);

// mod(point) = ERROR
// mod(direction) = scalar
float mod(const HCoord hc);

// dot(point, point)         = ERROR
// dot(point, direction)     = ERROR
// dot(direction, point)     = ERROR
// dot(direction, direction) = scalar
float dot(const HCoord &a, const HCoord &b);

// cross(point, point)         = ERROR
// cross(point, direction)     = ERROR
// cross(direction, point)     = ERROR
// cross(direction, direction) = scalar
HCoord cross(const HCoord &a, const HCoord &b);
