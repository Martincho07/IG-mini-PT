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

#include "BRDF.hpp"
#include "color.hpp"
#include "geometry.hpp"

#include <memory>
#include <vector>

#define EPSILON 0.0000001f

struct Shape {

    std::shared_ptr<MaterialProperty> material;

    Shape(){};
    Shape(std::shared_ptr<MaterialProperty> _material) : material(_material){};
    virtual ~Shape(){};

    virtual float intersection(Point3 o, Vector3 d) const = 0;
    virtual Vector3 normal(Point3 p) const = 0;
};

struct Sphere : public Shape {

    float r;
    Point3 center;

    Sphere(){};
    Sphere(Point3 _center, float _r, std::shared_ptr<MaterialProperty> _material) : center(_center), r(_r), Shape(_material){};
    ~Sphere(){};

    float intersection(Point3 o, Vector3 d) const override;
    Vector3 normal(Point3 p) const override;
};

struct Plane : public Shape {
    Vector3 n;
    float c;

    Plane(){};
    Plane(Vector3 _n, float _c, std::shared_ptr<MaterialProperty> _material) : n(_n), c(_c), Shape(_material){};
    ~Plane(){};

    float intersection(Point3 o, Vector3 d) const override;
    Vector3 normal(Point3 p) const override;
};

struct Triangle : public Shape {
    Point3 v1, v2, v3;

    Triangle(){};
    Triangle(Point3 _v1, Point3 _v2, Point3 _v3, std::shared_ptr<MaterialProperty> _material) : v1(_v1), v2(_v2), v3(_v3), Shape(_material){};
    ~Triangle(){};

    float intersection(Point3 o, Vector3 d) const override;
    Vector3 normal(Point3 p) const override;
};

struct Quadrilateral : public Shape {
    Triangle t1;
    Triangle t2;

    // El cuadrilatero recibe como parametros u_c (upper corner) que es la esquina superior derecha
    // y l_c(lower corner) que es la esquina inferior izquierda
    Quadrilateral(){};
    Quadrilateral(Point3 u_c, Point3 l_c, std::shared_ptr<MaterialProperty> _material) : Shape(_material) {
        // t1 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(l_c.x, u_c.y, l_c.z), Point3(u_c.x, u_c.y, u_c.z), _brdf);
        // t2 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(u_c.x, l_c.y, u_c.z), Point3(u_c.x, u_c.y, u_c.z), _brdf);
        t1 = Triangle(Point3(l_c.x, l_c.y, l_c.z), Point3(l_c.x, u_c.y, u_c.z), Point3(u_c.x, l_c.y, l_c.z), _material);
        t2 = Triangle(Point3(u_c.x, u_c.y, u_c.z), Point3(l_c.x, u_c.y, u_c.z), Point3(u_c.x, l_c.y, l_c.z), _material);
    };
    ~Quadrilateral(){};

    float intersection(Point3 o, Vector3 d) const override;
    Vector3 normal(Point3 p) const override;
};

struct TriangleMesh : public Shape {
    // Faces
    std::vector<Triangle> faces;

    // El cuadrilatero recibe como parametros u_c (upper corner) que es la esquina superior derecha
    // y l_c(lower corner) que es la esquina inferior izquierda
    TriangleMesh(){};
    TriangleMesh(std::vector<Triangle> _faces, std::shared_ptr<MaterialProperty> _material) : Shape(_material), faces(_faces){};
    ~TriangleMesh(){};

    float intersection(Point3 o, Vector3 d) const override;
    Vector3 normal(Point3 p) const override;
};
