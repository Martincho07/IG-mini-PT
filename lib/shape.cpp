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
#include <cmath>
#include <cstdlib>
#include <iostream>

float Plane::intersection(Point3 o, Vector3 d) const {
    float dot_d_n = dot(d, n);

    // Check if the ray is perpendicular to the plane normal
    if (fabs(dot_d_n) < EPSILON) {
        return -1.0;
    } else {
        return -((dot((Vector3)o, n) + c) / dot_d_n);
    }
};

float Sphere::intersection(Point3 o, Vector3 d) const {
    float mod = modulus(d);
    float a = mod * mod;

    float b = dot(d, o - center) * 2;

    mod = modulus(o - center);
    float c = mod * mod - r * r;

    float delta = b * b - 4 * a * c;

    if (delta < 0) {
        return -1.0;
    } else if (delta == 0) {
        return (-b + sqrt(delta)) / (2 * b);
    } else {
        float min = std::min((-b + sqrt(delta)) / (2 * a),
                             (-b - sqrt(delta)) / (2 * a));
        return min;
    }
}

float Triangle::intersection(Point3 o, Vector3 d) const {

    // Codigo adaptado de: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v, t;
    edge1 = v2 - v1;
    edge2 = v3 - v1;

    h = cross(d, edge2);
    a = dot(edge1, h);

    if ((a > -EPSILON) && (a < EPSILON))
        return -1.0;

    f = 1.0 / a;
    s = o - v1;
    u = f * dot(s, h);

    if (u < 0.0 || u > 1.0)
        return -1.0;

    q = cross(s, edge1);
    v = f * dot(d, q);

    if (v < 0.0 || u + v > 1.0)
        return -1.0;

    t = f * dot(edge2, q);

    if (t > EPSILON)
        return t;
    else
        return -1.0;
};

float Quadrilateral::intersection(Point3 o, Vector3 d) const {

    float t_tri_1, t_tri_2;

    t_tri_1 = t1.intersection(o, d);
    t_tri_2 = t2.intersection(o, d);

    if (t_tri_1 > 0) {
        return t_tri_1;
    }

    if (t_tri_2 > 0) {
        return t_tri_2;
    }
    return -1;
}

float TriangleMesh::intersection(Point3 o, Vector3 d) const {
    throw("No intersection");
}

Vector3 Sphere::normal(Point3 p) const {

    return normalize(p - center);
};

Vector3 Plane::normal(Point3 p) const {

    return n;
};

Vector3 Triangle::normal(Point3 p) const {
    return n;
};

Vector3 Quadrilateral::normal(Point3 p) const {

    return t1.normal(p);
};

Vector3 TriangleMesh::normal(Point3 p) const {
    throw("No normals here");
};

Point3 TriangleMesh::centroid() const {
    float area_sum = 0.0;
    Point3 centroid = Point3(0.0, 0.0, 0.0);
    for (int i = 0; i < faces.size(); i++) {
        Triangle t = faces[i];

        // Calculate the triangle center. It's the average of its vertices
        Point3 center = Point3(t.v1.x + t.v2.x + t.v3.x,
                               t.v1.y + t.v2.y + t.v3.y,
                               t.v1.z + t.v2.z + t.v3.z);
        center /= 3;

        float area = 0.5 * modulus(cross(t.v2 - t.v1, t.v3 - t.v1));
        centroid += center * area;
        area_sum += area;
    }
    std::cout << "area: " << area_sum << std::endl;
    return centroid / area_sum;
};

void TriangleMesh::reposition(const Point3 &center, float scale) {

    // Buscar el centro de la malla
    Point3 c = centroid();

    // Recolocar el objeto y ajustar la escala
    Vector3 offset = center - c * scale;
    for (Triangle &f : faces) {
        f.v1 = (f.v1 * scale) + offset;
        f.v2 = (f.v2 * scale) + offset;
        f.v3 = (f.v3 * scale) + offset;
    }
}

float Sphere::getU(Point3 p) const {

    Vector3 n = normalize(p - center);

    return 1.0f - (0.5 - asin(n.y) / M_PI);
};

float Plane::getU(Point3 p) const {

    if (p.y < 0.0)
        return 1.0f - abs(p.y - (int)p.y);

    return abs(p.y - (int)p.y);
};

float Triangle::getU(Point3 p) const {
    return -1.0f;
};

float Quadrilateral::getU(Point3 p) const {
    Vector3 r = p - l_right;
    Vector3 q = u_right - l_right;
    float cos = dot(q, r) / (modulus(r) * modulus(q));
    return (modulus(r) * cos) / modulus(q);
};
float TriangleMesh::getU(Point3 p) const {
    return -1.0f;
};

float Sphere::getV(Point3 p) const {

    Vector3 n = normalize(p - center);
    return 0.5 + atan2(n.z, n.x) / (2 * M_PI);
};

float Plane::getV(Point3 p) const {
    if (p.x > 0.0f)
        return 1.0f - abs(p.x - (int)p.x);
    return abs(p.x - (int)p.x);
};

float Triangle::getV(Point3 p) const {
    return -1.0f;
};

float Quadrilateral::getV(Point3 p) const {

    Vector3 r = p - l_right;
    Vector3 q = l_left - l_right;
    float cos = dot(q, r) / (modulus(r) * modulus(q));
    return (modulus(r) * cos) / modulus(q);
};
float TriangleMesh::getV(Point3 p) const {
    return -1.0f;
};
