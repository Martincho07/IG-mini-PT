/*********************************************************************************
 * Image
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
#include "file.hpp"
#include "geometry.hpp"
#include "surface_interaction.hpp"

#include <memory>
#include <vector>

#define EPSILON 0.0000001f

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
    Vector3 n;
    float c;

    Plane(){};
    Plane(Vector3 _n, float _c, std::shared_ptr<Material> _material) : n(_n), c(_c), Shape(_material){};
    ~Plane(){};

    float intersect(const Ray &ray) const override;
    Vector3 normal(const Point3 &p) const override;
    float getU(const Point3 &p) const override;
    float getV(const Point3 &p) const override;
    AABB bounding_box() const override;
};

struct Triangle : public Shape {
    Point3 v1, v2, v3;
    Vector3 n;

    Triangle(){};
    Triangle(Point3 _v1, Point3 _v2, Point3 _v3, std::shared_ptr<Material> _material)
        : v1(_v1), v2(_v2), v3(_v3), n(normalize(cross(_v2 - _v1, _v3 - _v1))), Shape(_material){};
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

    // El cuadrilatero recibe como parametros u_c (upper corner) que es la esquina superior derecha
    // y l_c(lower corner) que es la esquina inferior izquierda
    Quadrilateral(){};
    Quadrilateral(Point3 u_c, Point3 l_c, std::shared_ptr<Material> _material) : Shape(_material) {
        // t1 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(l_c.x, u_c.y, l_c.z), Point3(u_c.x, u_c.y, u_c.z), _brdf);
        // t2 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(u_c.x, l_c.y, u_c.z), Point3(u_c.x, u_c.y, u_c.z), _brdf);

        t1 = Triangle(Point3(l_c.x, l_c.y, l_c.z), Point3(l_c.x, l_c.y, u_c.z), Point3(u_c.x, u_c.y, u_c.z), _material);
        t2 = Triangle(Point3(u_c.x, u_c.y, u_c.z), Point3(u_c.x, u_c.y, l_c.z), Point3(l_c.x, l_c.y, l_c.z), _material);

        // // Corregido
        // t1 = Triangle(Point3(l_c.x, l_c.y, l_c.z), Point3(l_c.x, u_c.y, u_c.z), Point3(u_c.x, l_c.y, l_c.z), _material);
        // t2 = Triangle(Point3(l_c.x, u_c.y, u_c.z), Point3(u_c.x, u_c.y, u_c.z), Point3(u_c.x, l_c.y, l_c.z), _material);

        l_left = l_c;
        l_right = Point3(l_c.x, l_c.y, u_c.z);
        u_left = Point3(u_c.x, u_c.y, l_c.z);
        u_right = u_c;
    };
    ~Quadrilateral(){};

    float intersect(const Ray &ray) const override;
    Vector3 normal(const Point3 &p) const override;
    float getU(const Point3 &p) const override;
    float getV(const Point3 &p) const override;
    AABB bounding_box() const override;
};

std::vector<Triangle> readPLY(const std::string file, const std::shared_ptr<Material> brdf);

struct TriangleMesh : public Shape {
    // Faces
    std::vector<Triangle> faces;

    TriangleMesh(){};

    TriangleMesh(const std::vector<Triangle> &_faces, std::shared_ptr<Material> _brdf, Point3 center, float scale) : Shape(_brdf), faces(_faces) {
        for (Triangle &face : faces) {
            face.material = _brdf;
        }
        reposition(center, scale);
    };

    TriangleMesh(const std::string file, std::shared_ptr<Material> _brdf, const Point3 center, float scale) : Shape(_brdf) {
        faces = readPLY(file, _brdf);
        reposition(center, scale);
    };

    ~TriangleMesh(){};

    float intersect(const Ray &ray) const override;
    Vector3 normal(const Point3 &p) const override;
    float getU(const Point3 &p) const override;
    float getV(const Point3 &p) const override;
    AABB bounding_box() const override;
    Point3 centroid() const;
    void reposition(const Point3 &center, float scale);
};
