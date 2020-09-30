/*********************************************************************************
 * Planet
 *
 * File: planet.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 26/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "geometry.hpp"
#include "transform.hpp"

#include <assert.h>
#include <cmath>

#define MAX_ERROR 1e-6
#define SIMILAR(a, b) ((a <= b + MAX_ERROR) && (a >= b - MAX_ERROR))

struct Planet {
    Point3 center, refCity;
    Vector3 axis;

    // Station local coordinate system
    Point3 orig; // origin in the UCS
    Vector3 i, j, k;

    // Constructors
    Planet(){};
    Planet(const Point3 &_center, const Point3 &_refCity, const Vector3 &_axis, float inclination, float azimuth);
};

// Return true if the point p is in the surface of the planet
bool inSurface(const Planet &planet, const Point3 &p);

// Calculate the trajectory between to stations and show if from the point
// of view of each one
void launch(const Planet &origin, const Planet &destination);
