/*********************************************************************************
 * Shape
 *
 * File: shape.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "AABB.hpp"
#include "BRDF.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "surface_interaction.hpp"
#include "transform.hpp"

#include <memory>
#include <vector>

struct SurfaceInteraction;
struct Material;

#define EPSILON 0.0001f
// #define EPSILON 0.01f
// #define EPSILON 0.0000001f

#define EPSILON_TRIANGLES 0.0000001f

struct Shape {

    std::shared_ptr<Material> material;

    Shape(){};
    Shape(std::shared_ptr<Material> _material) : material(_material){};
    virtual ~Shape(){};

    // Calculate intersection of ray with shape
    virtual float intersect(const Ray &ray) const = 0;

    // Returns normalized normal
    virtual Vector3 normal(const Point3 &p) const = 0;

    // Returns UV parametrization
    virtual float getU(const Point3 &p) const = 0;
    virtual float getV(const Point3 &p) const = 0;

    // Returns the AABB that surrounds the shape
    virtual AABB bounding_box() const = 0;
};

bool shapes_first_intersection(const std::vector<std::shared_ptr<Shape>> &shapes, const Ray &ray, SurfaceInteraction &si);

struct Sphere : public Shape {

    float r;
    Point3 center;

    Sphere(){};
    Sphere(Point3 _center, float _r, std::shared_ptr<Material> _material) : center(_center), r(_r), Shape(_material){};
    ~Sphere(){};

    float intersect(const Ray &ray) const override;
    Vector3 normal(const Point3 &p) const override;
    float getU(const Point3 &p) const override;
    float getV(const Point3 &p) const override;
    AABB bounding_box() const override;
};

struct Plane : public Shape {
    Vector3 n, u, v;
    Point3 o;
    float c;
    Transform world2Plane;

    Plane(){};
    Plane(Vector3 _n, float _c, std::shared_ptr<Material> _material) : n(_n), c(_c), Shape(_material){};
    Plane(Vector3 _n, float _c, std::shared_ptr<Material> _material, Vector3 _u, Vector3 _v, Point3 _o) : n(_n), c(_c), u(_u), v(_v), o(_o), Shape(_material) {

        world2Plane = inverse(Transform(Matrix4x4(u.x, n.x, v.x, o.x,
                                                  u.y, n.y, v.y, o.y,
                                                  u.z, n.z, v.z, o.z,
                                                  0.0f, 0.0f, 0.0f, 1.0f)));
    };
    ~Plane(){};

    float intersect(const Ray &ray) const override;
    Vector3 normal(const Point3 &p) const override;
    float getU(const Point3 &p) const override;
    float getV(const Point3 &p) const override;
    AABB bounding_box() const override;
};

struct Triangle : public Shape {
    Point3 v1, v2, v3;
    Vector3 n1, n2, n3;
    bool smooth;

    Triangle(){};

    Triangle(Point3 _v1, Point3 _v2, Point3 _v3, std::shared_ptr<Material> _material)
        : v1(_v1), v2(_v2), v3(_v3), n1(normalize(cross(_v2 - _v1, _v3 - _v1))), smooth(false), Shape(_material){};

    Triangle(Point3 _v1, Point3 _v2, Point3 _v3, Vector3 _n1, Vector3 _n2, Vector3 _n3, std::shared_ptr<Material> _material)
        : v1(_v1), v2(_v2), v3(_v3), n1(_n1), n2(_n2), n3(_n3), smooth(true), Shape(_material){};

    ~Triangle(){};

    float intersect(const Ray &ray) const override;
    Vector3 normal(const Point3 &p) const override;
    float getU(const Point3 &p) const override;
    float getV(const Point3 &p) const override;
    AABB bounding_box() const override;
};

struct Quadrilateral : public Shape {
    Triangle t1;
    Triangle t2;
    Point3 l_left, l_right, u_left, u_right;

    // u_c (upper right corner)
    // l_c (lower right corner)
    // u_left (upper left corner)
    Quadrilateral(){};
    Quadrilateral(Point3 u_c, Point3 l_c, Point3 u_left, std::shared_ptr<Material> _material) : Shape(_material) {
        // t1 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(l_c.x, u_c.y, l_c.z), Point3(u_c.x, u_c.y, u_c.z), _brdf);
        // t2 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(u_c.x, l_c.y, u_c.z), Point3(u_c.x, u_c.y, u_c.z), _brdf);

        l_left = l_c;
        this->u_left = u_left;
        Vector3 v1 = l_c - u_left;
        Vector3 v2 = u_c - u_left;
        Vector3 v3 = v1 + v2;
        l_right = this->u_left + v3;
        u_right = u_c;

        t1 = Triangle(l_c, this->u_left, u_c, _material);
        t2 = Triangle(u_c, this->l_right, l_c, _material);

    };
    Quadrilateral(Point3 p10, Point3 p00, Point3 p01, Point3 p11, std::shared_ptr<Material> _material) : Shape(_material) {
        t1 = Triangle(p10, p00, p01, _material);
        t2 = Triangle(p01, p11, p10, _material);
    };
    ~Quadrilateral(){};

    float intersect(const Ray &ray) const override;
    Vector3 normal(const Point3 &p) const override;
    float getU(const Point3 &p) const override;
    float getV(const Point3 &p) const override;
    AABB bounding_box() const override;
};

struct TriangleMesh : public Shape {
    // Faces
    std::vector<Triangle> faces;

    TriangleMesh(){};

    TriangleMesh(const std::vector<Triangle> &_faces, std::shared_ptr<Material> _brdf, Point3 center, float scale, bool zflip = false) : Shape(_brdf), faces(_faces) {
        for (Triangle &face : faces) {
            face.material = _brdf;
            if (zflip) {
                face.v1.z = -face.v1.z;
                face.v2.z = -face.v2.z;
                face.v3.z = -face.v3.z;
                face.n1.z = -face.n1.z;
                face.n2.z = -face.n2.z;
                face.n3.z = -face.n3.z;
            }
        }
        reposition(center, scale);
    };

    // TriangleMesh(const std::string file, std::shared_ptr<Material> _brdf, const Point3 center, float scale) : Shape(_brdf) {
    //     faces = readPLY(file, _brdf);
    //     reposition(center, scale);
    // };

    ~TriangleMesh(){};

    float intersect(const Ray &ray) const override;
    Vector3 normal(const Point3 &p) const override;
    float getU(const Point3 &p) const override;
    float getV(const Point3 &p) const override;
    AABB bounding_box() const override;
    Point3 centroid() const;
    void reposition(const Point3 &center, float scale);
};
