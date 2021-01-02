/*********************************************************************************
 * BRDF
 *
 * File: BRDF.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "BRDF.hpp"
#include "shape.hpp"

#include <memory>

struct Shape;

struct SurfaceInteraction {

    // Intersected material
    std::shared_ptr<Shape> shape;

    // Distance across the ray
    float t;

    // Intersection point
    Point3 position;

    // *Properly oriented* normal at intersection point
    Vector3 normal;

    // UV parametrization
    // float u, v;

    SurfaceInteraction() {}

    // SurfaceInteraction(const std::shared_ptr<Shape> _shape, Point3 _position, const Vector3 _normal, const float _u, const float _v)
    // : shape(_shape), position(_position), normal(_normal), u(_u), v(_v) {}

    SurfaceInteraction(const std::shared_ptr<Shape> _shape, float _t, Point3 _position, const Vector3 _normal)
        : shape(_shape), t(_t), position(_position), normal(_normal) {}
};
