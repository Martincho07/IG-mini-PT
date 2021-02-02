/*********************************************************************************
 * Axis-Aligned Bounding Boxes (AABB)
 *
 * File: AABB.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "AABB.hpp"

// Adapted from PBRT
bool AABB::intersect(const Ray &ray) const {
    float tmin = (pmin.x - ray.o.x) / ray.d.x;
    float tmax = (pmax.x - ray.o.x) / ray.d.x;

    if (tmin > tmax)
        std::swap(tmin, tmax);

    float tymin = (pmin.y - ray.o.y) / ray.d.y;
    float tymax = (pmax.y - ray.o.y) / ray.d.y;

    if (tymin > tymax)
        std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (pmin.z - ray.o.z) / ray.d.z;
    float tzmax = (pmax.z - ray.o.z) / ray.d.z;

    if (tzmin > tzmax)
        std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;
}

int AABB::max_axis() const {
    Vector3 size = pmax - pmin;
    float max_dim = size.x;
    int dim = 0;

    if (max_dim < size.y) {
        dim = 1;
        max_dim = size.y;
    }
    if (max_dim < size.z) {
        dim = 2;
        max_dim = size.z;
    }
    return dim;
}

Point3 AABB::center() const {
    Point3 size = Point3(pmax.x + pmin.x,
                         pmax.y + pmin.y,
                         pmax.z + pmin.z);
    return size * .5f;
}

AABB union_box(const AABB &bb1, const AABB &bb2) {
    Point3 pmin(fmin(bb1.pmin.x, bb2.pmin.x),
                fmin(bb1.pmin.y, bb2.pmin.y),
                fmin(bb1.pmin.z, bb2.pmin.z));

    Point3 pmax(fmax(bb1.pmax.x, bb2.pmax.x),
                fmax(bb1.pmax.y, bb2.pmax.y),
                fmax(bb1.pmax.z, bb2.pmax.z));

    return AABB(pmin, pmax);
};
