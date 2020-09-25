/*********************************************************************************
 * Representation of homogeneous coordinates
 *
 * File: coordinate.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, curso 2020-2021
 **********************************************************************************/

#include "coordinate.hpp"

#include <assert.h>

#include <cmath>
#include <iostream>

HCoord point(float x, float y, float z) { return {{x, y, z, 1.0f}}; };

HCoord direction(float x, float y, float z) { return {{x, y, z, 0.0f}}; };

HCoord HCoord::operator+(const HCoord &right) const
{
    assert(w == 0 || right.w == 0);
    return {{x + right.x, y + right.y, z + right.z, w + right.w}};
};

HCoord HCoord::operator-(const HCoord &right) const
{
    assert(w != 0 || right.w == 0);
    return {{x - right.x, y - right.y, z - right.z, w - right.w}};
};

HCoord HCoord::operator*(const float right) const
{
    assert(w == 0);
    return {{x * right, y * right, z * right, w * right}};
};

HCoord HCoord::operator/(const float right) const
{
    assert(w == 0);
    return {{x / right, y / right, z / right, w / right}};
}

float mod(const HCoord hc)
{
    assert(hc.w == 0);
    return sqrt(hc.x + hc.y + hc.z);
};

float dot(const HCoord &a, const HCoord &b)
{
    assert(a.w == 0 && b.w == 0);
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
};

HCoord cross(const HCoord &a, const HCoord &b)
{
    assert(a.w == 0 && b.w == 0);
    return {{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
             a.x * b.y - a.y * b.x, 0.0f}}; // Return a direction
};
