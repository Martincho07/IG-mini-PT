/*********************************************************************************
 * Planet
 *
 * File: planet.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 26/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "planet.hpp"

#include <assert.h>
#include <cmath>

bool inSurface(const Planet &planet, const Point3 &p) {
    return (dot((p - planet.center), (p - planet.center)) - pow(modulus(planet.axis) / 2, 2)) == 0;
}

void launch(const Planet &origin, const Planet &destination) {
    Transform canonic = changeBase(Vector3(1.0f, 0.0f, 0.0f),
                                   Vector3(0.0f, 1.0f, 0.0f),
                                   Vector3(0.0f, 0.0f, 1.0f),
                                   Point3(0.0f, 0.0f, 0.0f));

    Point3 p1 = canonic(Point3(0, 0, 0));
    Point3 p2 = canonic(Point3(0, 0, 0));
};
