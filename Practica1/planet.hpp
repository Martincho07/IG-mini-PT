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

struct Planet {
    Point3 center, refCity;
    Vector3 axis;

    // Local coordinate system
    Vector3 i, j, k;

    // Constructor
    Planet(const Point3 &_center, const Point3 &_refCity, const Vector3 &_axis, float inclination, float azimuth)
        : center(_center), refCity(_refCity), axis(_axis) {

        Vector3 n = refCity - center;

        // Test that the parameters are correct
        float radius = modulus(axis) / 2;
        assert(modulus(n) == radius);
        assert(inclination >= 0 && inclination <= M_PI);
        assert(azimuth >= -M_PI && inclination <= M_PI);

        // Calculate local coordinate system
        k = normalize((rotationZ(inclination) * rotationY(azimuth))(n)); // Surface normal
        i = normalize(cross(k, axis));                                   // Longitude tangent direction
        j = normalize(cross(k, i));                                      // Latitude tangent direction
    };
};

// Return true if the point p is in the surface of the planet
bool inSurface(const Planet &planet, const Point3 &p);

void launch(const Planet &origin, const Planet &destination);
