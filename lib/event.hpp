/*********************************************************************************
 * Event
 *
 * File: event.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 1/12/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "BRDF.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "random.hpp"
#include "shape.hpp"
#include <cmath>
#include <iostream>
#include <memory>

enum EVENT {
    DIFFUSE_EVENT,
    SPECULAR_EVENT,
    REFRACTION_EVENT,
    DEAD_EVENT
};

EVENT randomEvent(const Material &material);
void russianRoulette(const Material &material, const Vector3 &normal, const Point3 &point, Vector3 &direction, RGB &contribution, bool &success);
EVENT randomEvent(const RGB &texture);
void russianRoulette(const RGB &texture, const Vector3 &normal, const Point3 &point, Vector3 &direction, RGB &contribution, bool &success);
