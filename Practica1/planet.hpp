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

    // Local coordinate system
    Vector3 i, j, k;
    Point3 orig;

    // Constructors
    Planet(){};

    Planet(const Point3 &_center, const Point3 &_refCity, const Vector3 &_axis, float inclination, float azimuth)
        : center(_center), refCity(_refCity), axis(_axis) {

        //  v es normal a la superficie del planeta
        Vector3 v = refCity - center;

        // Test that the parameters are correct
        float radius = modulus(axis) / 2;
        assert(SIMILAR(modulus(v), radius));
        assert(inclination >= 0 && inclination <= M_PI);
        assert(azimuth >= -M_PI && inclination <= M_PI);

        // Rotar v
        std::cout << "v antes: " << v << std::endl;
        v = (rotationZ(inclination) * rotationY(azimuth))(abs(v));
        std::cout << "v rotado: " << v << std::endl;
        orig = Point3(v.x, v.y, v.z) + Vector3(center);
        std::cout << "v sumado: " << orig << std::endl;

        // Calculate local coordinate system
        k = normalize(v);              // Surface normal
        i = normalize(cross(k, axis)); // Longitude tangent direction
        j = normalize(cross(k, i));    // Latitude tangent direction

        std::cout << "Sistema coords: " << k << i << j << std::endl;
    };
};

// Return true if the point p is in the surface of the planet
bool inSurface(const Planet &planet, const Point3 &p);

void launch(const Planet &origin, const Planet &destination);
