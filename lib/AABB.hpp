/*********************************************************************************
 * Axis-Aligned Bounding Boxes (AABB)
 *
 * File: AABB.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "geometry.hpp"
#include <cfloat>

struct AABB {
    // Invariant: min.x <= max.x
    Point3 pmin, pmax;

    // The default constructor creates an invalid AABB
    AABB() : pmin(Point3(FLT_MAX, FLT_MAX, FLT_MAX)),
             pmax(Point3(-FLT_MAX, -FLT_MAX, -FLT_MAX)) {}

    // Bounding box enclosing a single point
    AABB(const Point3 &p) : pmin(p), pmax(p) {}

    // Bounding box given two points
    AABB(const Point3 &p1, const Point3 &p2)
        : pmin(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)),
          pmax(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)) {}

    // Implementación de https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
    bool intersect(const Ray &ray) const;

    // Return the biggest axis
    int max_axis() const;

    // Return the bounding box center
    Point3 center() const;
};

AABB union_box(const AABB &bb1, const AABB &bb2);
