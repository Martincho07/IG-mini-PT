/*********************************************************************************
 * Image
 *
 * File: shape.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "shape.hpp"

#include <cfloat>

float Sphere::intersection(Point3 o, Vector3 d) const {
    float a = pow(modulus(d), 2.0f);
    float b = dot(d, o - center) * 2.0f;
    float c = pow(modulus(o - center), 2.0f) - pow(r, 2.0f);
    float delta = pow(b, 2) - 4.0f * a * c;

    if (delta < 0) {
        return -1.0f;
    } else if (delta == 0) {
        return (-b + sqrt(delta)) / (2 * b);
    } else {

        return std::min((-b + sqrt(delta)) / (2 * a),
                        (-b - sqrt(delta)) / (2 * a));
    }
}

float Plane::intersection(Point3 o, Vector3 d) const {
    float dot_d_n = dot(d, n);
    if (dot_d_n == 0) {
        return -1.0f;
    } else {
        return -((dot((Vector3)o, n) + c) / dot_d_n);
    }
};

float Triangle::intersection(Point3 o, Vector3 d) const {

    // Codigo copiado de: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v, t;
    edge1 = v2 - v1;
    edge2 = v3 - v1;

    h = cross(d, edge2);
    a = dot(edge1, h);

    if ((a > -EPSILON) && (a < EPSILON))
        return -1.0f;

    f = 1.0 / a;
    s = o - v1;
    u = f * dot(s, h);

    if (u < 0.0 || u > 1.0)
        return -1.0f;

    q = cross(s, edge1);
    v = f * dot(d, q);

    if (v < 0.0 || u + v > 1.0)
        return -1.0f;

    t = f * dot(edge2, q);

    if (t > EPSILON)
        return t;
    else
        return -1.0f;
};

float Quadrilateral::intersection(Point3 o, Vector3 d) const {

    float t_tri_1, t_tri_2;

    t_tri_1 = t1.intersection(o, d);
    t_tri_2 = t2.intersection(o, d);

    if (t_tri_1 > 0)
        return t_tri_1;

    if (t_tri_2 > 0)
        return t_tri_2;

    return -1.0f;
}

float TriangleMesh::intersection(Point3 o, Vector3 d) const {
    float t_min, aux;
    t_min = FLT_MAX;
    for (const Triangle &t : faces) {
        aux = t.intersection(o, d);
        if (aux >= 0 && aux < t_min) {
            t_min = aux;
        }
    }
    if (t_min == FLT_MAX) {
        t_min = -1;
    }
    return t_min;
}