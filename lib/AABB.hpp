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

/*
void add(const Vector3 &p) {
    if (p[0] < _min[0])
        _min[0] = p[0];
    if (p[1] < _min[1])
        _min[1] = p[1];
    if (p[2] < _min[2])
        _min[2] = p[2];
    if (p[0] > _max[0])
        _max[0] = p[0];
    if (p[1] > _max[1])
        _max[1] = p[1];
    if (p[2] > _max[2])
        _max[2] = p[2];
}
void add(const AABB &bb) {
    if (bb._min[0] < _min[0])
        _min[0] = bb._min[0];
    if (bb._min[1] < _min[1])
        _min[1] = bb._min[1];
    if (bb._min[2] < _min[2])
        _min[2] = bb._min[2];
    if (bb._max[0] > _max[0])
        _max[0] = bb._max[0];
    if (bb._max[1] > _max[1])
        _max[1] = bb._max[1];
    if (bb._max[2] > _max[2])
        _max[2] = bb._max[2];
}
*/

/*
    * Ray-box intersection from PBRT
    */
/*
bool intersect(const Ray &r, Real &t) const {
    Vector3 origin = r.get_origin();
    Real t0 = -std::numeric_limits<Real>::infinity(),
            t1 = std::numeric_limits<Real>::infinity();
    for (int i = 0; i < 3; ++i) {
        // Update interval for _i_th bounding box slab
        Real invRayDir = 1.f / r.get_direction()[i];
        Real tNear = (_min[i] - origin[i]) * invRayDir;
        Real tFar = (_max[i] - origin[i]) * invRayDir;

        // Update parametric interval from slab intersection $t$s
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return false;
    }
    t = t0;
    return true;
}
*/

// bool intersect(const Ray &r) {
//     float tmin = (min.x - r.orig.x) / r.dir.x;
//     float tmax = (max.x - r.orig.x) / r.dir.x;

//     if (tmin > tmax)
//         swap(tmin, tmax);

//     float tymin = (min.y - r.orig.y) / r.dir.y;
//     float tymax = (max.y - r.orig.y) / r.dir.y;

//     if (tymin > tymax)
//         swap(tymin, tymax);

//     if ((tmin > tymax) || (tymin > tmax))
//         return false;

//     if (tymin > tmin)
//         tmin = tymin;

//     if (tymax < tmax)
//         tmax = tymax;

//     float tzmin = (min.z - r.orig.z) / r.dir.z;
//     float tzmax = (max.z - r.orig.z) / r.dir.z;

//     if (tzmin > tzmax)
//         swap(tzmin, tzmax);

//     if ((tmin > tzmax) || (tzmin > tmax))
//         return false;

//     if (tzmin > tmin)
//         tmin = tzmin;

//     if (tzmax < tmax)
//         tmax = tzmax;

//     return true;
// }

/*
const AABB &operator=(const AABB &bb) {
    _min = bb._min;
    _max = bb._max;
    return *this;
}
*/
