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
#include "error.hpp"
#include "geometry.hpp"

#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iostream>

float Plane::intersect(const Ray &ray) const {
    // Ray direction must be normalized

    float dot_d_n = dot(ray.d, n);

    // Check if the ray is perpendicular to the plane normal
    if (fabs(dot_d_n) < EPSILON) {
        return -1.0;
    } else {
        return -((dot((Vector3)ray.o, n) + c) / dot_d_n);
    }
};

float Sphere::intersect(const Ray &ray) const {
    float mod = modulus(ray.d);
    float a = mod * mod;

    float b = dot(ray.d, ray.o - center) * 2;

    mod = modulus(ray.o - center);
    float c = mod * mod - r * r;

    float delta = b * b - 4 * a * c;

    if (delta < EPSILON) {
        return -1.0;
    } else if (delta == EPSILON) {
        return (-b + sqrt(delta)) / (2 * b);
    } else {
        float first = (-b + sqrt(delta)) / (2 * a);
        float second = (-b - sqrt(delta)) / (2 * a);
        float min = std::min(first, second);
        if (min < EPSILON) {
            return std::max(first, second);
        } else {
            return min;
        }
    }
}

float Triangle::intersect(const Ray &ray) const {

    // Codigo adaptado de: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v, t;
    edge1 = v2 - v1;
    edge2 = v3 - v1;

    h = cross(ray.d, edge2);
    a = dot(edge1, h);

    if ((a > -EPSILON_TRIANGLES) && (a < EPSILON_TRIANGLES))
        return -1.0f;

    f = 1.0f / a;
    s = ray.o - v1;
    u = f * dot(s, h);

    // En los siguientes dos if no hay que poner EPSILON

    if (u < 0.0f || u > 1.0f)
        return -1.0f;

    q = cross(s, edge1);
    v = f * dot(ray.d, q);

    if (v < 0.0f || u + v > 1.0f)
        return -1.0f;

    t = f * dot(edge2, q);

    if (t > EPSILON_TRIANGLES)
        return t;
    else
        return -1.0f;
};

float Quadrilateral::intersect(const Ray &ray) const {

    float t_tri_1, t_tri_2;

    t_tri_1 = t1.intersect(ray);
    t_tri_2 = t2.intersect(ray);

    if (t_tri_1 > 0) {
        return t_tri_1;
    }

    if (t_tri_2 > 0) {
        return t_tri_2;
    }
    return -1;
}

float TriangleMesh::intersect(const Ray &ray) const {
    ErrorExit("No intersection");
    return 1.0f;
}

Vector3 Sphere::normal(const Point3 &p) const {

    return normalize(p - center);
};

Vector3 Plane::normal(const Point3 &p) const {

    return n;
};

Vector3 Triangle::normal(const Point3 &p) const {
    if (!smooth) {
        return n1;
    } else {
        // Point3 p = v3;

        Vector3 bary;
        Vector3 e2_1 = v1 - v2;
        Vector3 e2_3 = v3 - v2;
        Vector3 e2_p = p - v2;

        float d00 = dot(e2_1, e2_1);
        float d01 = dot(e2_1, e2_3);
        float d11 = dot(e2_3, e2_3);
        float denom = d00 * d11 - d01 * d01;

        float d20 = dot(e2_p, e2_1);
        float d21 = dot(e2_p, e2_3);

        bary.x = (d11 * d20 - d01 * d21) / denom;
        bary.y = (d00 * d21 - d01 * d20) / denom;
        bary.z = 1.0f - bary.x - bary.y;

        // Error(v1, v2, v3);
        // Error(p);
        // Error(bary);
        // exit(1);

        return normalize(n1 * bary.x + n3 * bary.y + n2 * bary.z);
        // return n1 * bary.x + n3 * bary.y + n2 * bary.z;
        // return normalize(n1 * bary.x + n2 * bary.y + n3 * bary.z);
    }
};

Vector3 Quadrilateral::normal(const Point3 &p) const {

    return t1.normal(p);
};

Vector3 TriangleMesh::normal(const Point3 &p) const {
    ErrorExit("No normals here");
    return Vector3(0, 0, 0);
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

float Sphere::getU(const Point3 &p) const {

    Vector3 n = normalize(p - center);

    return 1.0f - (0.5 - asin(n.y) / M_PI);
};

float Plane::getU(const Point3 &p) const {

    Point3 p2plane = world2Plane(p);

    return abs(p2plane.x) - abs((int)p2plane.x);
};

float Triangle::getU(const Point3 &p) const {
    return -1.0f;
};

float Quadrilateral::getU(const Point3 &p) const {
    Vector3 r = p - l_right;
    Vector3 q = u_right - l_right;
    float cos = dot(q, r) / (modulus(r) * modulus(q));
    return (modulus(r) * cos) / modulus(q);
};
float TriangleMesh::getU(const Point3 &p) const {
    return -1.0f;
};

float Sphere::getV(const Point3 &p) const {
    Vector3 n = normalize(p - center);
    return 0.5 + atan2(n.z, n.x) / (2 * M_PI);
};

float Plane::getV(const Point3 &p) const {
    //std::cout << p << std::endl;
    Point3 p2plane = world2Plane(p);
    //std::cout << p2plane << std::endl;
    //exit(1);
    return p2plane.z - (int)p2plane.z;
};

float Triangle::getV(const Point3 &p) const {
    return -1;
};

float Quadrilateral::getV(const Point3 &p) const {

    Vector3 r = p - l_left;
    Vector3 q = l_right - l_left;
    float cos = dot(q, r) / (modulus(r) * modulus(q));
    return (modulus(r) * cos) / modulus(q);
};
float TriangleMesh::getV(const Point3 &p) const {
    return -1.0f;
};

AABB Plane::bounding_box() const {
    /// TODO: No se si hay que poner todas las componentes infinitas
    // return AABB(Point3(-FLT_MAX, 0, -FLT_MAX), Point3(FLT_MAX, 0, FLT_MAX));
    return AABB(Point3(-FLT_MAX, -FLT_MAX, -FLT_MAX), Point3(FLT_MAX, FLT_MAX, FLT_MAX));
    ErrorExit("No bounding box for infinite planes");
}

AABB Sphere::bounding_box() const {
    return AABB(center - Vector3(r, r, r),
                center + Vector3(r, r, r));
}

AABB Triangle::bounding_box() const {
    return union_box(AABB(v1, v2), AABB(v3));
}

AABB Quadrilateral::bounding_box() const {
    return union_box(t1.bounding_box(), t2.bounding_box());
}

AABB TriangleMesh::bounding_box() const {
    AABB bb;
    for (const Triangle &t : faces) {
        bb = union_box(bb, t.bounding_box());
    }
    return bb;
}

bool shapes_first_intersection(const std::vector<std::shared_ptr<Shape>> &shapes, Ray &ray, SurfaceInteraction &si) {
    float t_min = FLT_MAX;
    float t = 0;
    std::shared_ptr<Shape> shape;

    // ray.shift();

    for (const std::shared_ptr<Shape> &s : shapes) {
        t = s->intersect(ray);

        if (t < t_min && t > EPSILON) {
            t_min = t;
            shape = s;
        }
    }

    if (t_min == FLT_MAX) {
        return false;
    } else {
        // Surface interaction point
        Point3 si_point = ray.get_point(t_min);

        // Calculate propely oriented normal
        Vector3 si_normal = shape->normal(si_point);

        // Determine if ray is entering the shape
        bool into = true;
        if (dot(ray.d, si_normal) >= 0.0) {
            // Error("into", shape->material->type);
            into = false;
            si_normal = -si_normal;
        }

        // si_normal = dot(ray.d, si_normal) < 0.0 ? si_normal : -si_normal;

        si = SurfaceInteraction(shape, t_min, si_point, si_normal, into);
        return true;
    }
}
