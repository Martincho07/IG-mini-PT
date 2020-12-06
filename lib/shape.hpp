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

    std::shared_ptr<BRDF> brdf;

    Shape(){};
    Shape(std::shared_ptr<BRDF> _brdf) : brdf(_brdf){};
    virtual ~Shape(){};

    virtual float intersection(Point3 o, Vector3 d) const = 0;
    virtual Vector3 normal(Point3 p) const = 0;
};

struct Sphere : public Shape {

    float r;
    Point3 center;

    Sphere(){};
    Sphere(RGB _color, Point3 _center, float _r, std::shared_ptr<BRDF> _brdf) : center(_center), r(_r), Shape(_brdf){};
    ~Sphere(){};

    float intersection(Point3 o, Vector3 d) const override;
    Vector3 normal(Point3 p) const override;
};

struct Plane : public Shape {
    Vector3 n;
    float c;

    Plane(){};
    Plane(RGB _color, Vector3 _n, float _c, std::shared_ptr<BRDF> _brdf) : n(_n), c(_c), Shape(_brdf){};
    ~Plane(){};

    float intersection(Point3 o, Vector3 d) const override;
    Vector3 normal(Point3 p) const override;
};

struct Triangle : public Shape {
    Point3 v1, v2, v3;

    Triangle(){};
    Triangle(RGB _color, Point3 _v1, Point3 _v2, Point3 _v3, std::shared_ptr<BRDF> _brdf) : v1(_v1), v2(_v2), v3(_v3), Shape(_brdf){};
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
    Quadrilateral(RGB _color, Point3 u_c, Point3 l_c, std::shared_ptr<BRDF> _brdf) : Shape(_brdf) {
        // t1 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(l_c.x, u_c.y, l_c.z), Point3(u_c.x, u_c.y, u_c.z), _brdf);
        // t2 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(u_c.x, l_c.y, u_c.z), Point3(u_c.x, u_c.y, u_c.z), _brdf);
        t1 = Triangle(_color, Point3(l_c.x, l_c.y, l_c.z), Point3(l_c.x, u_c.y, u_c.z), Point3(u_c.x, l_c.y, l_c.z), _brdf);
        t2 = Triangle(_color, Point3(u_c.x, u_c.y, u_c.z), Point3(l_c.x, u_c.y, u_c.z), Point3(u_c.x, l_c.y, l_c.z), _brdf);
    };
    ~Quadrilateral(){};

    float intersection(Point3 o, Vector3 d) const override;
    Vector3 normal(Point3 p) const override;
};

struct TriangleMesh : public Shape {
    // Faces
    std::vector<Triangle> faces;

    int last_intersection;

    TriangleMesh(){};
    TriangleMesh(RGB _color, std::vector<Triangle> _faces, std::shared_ptr<BRDF> _brdf, Point3 center, float scale) : Shape(_brdf), faces(_faces) {
        int last_intersection = 0;

        // Buscar el centro de la malla
        Point3 c = centroid();

        std::cout << "centroid: " << c << std::endl;

        // Recolocar el objeto y ajustar la escala
        Vector3 offset = center - c * scale;
        for (Triangle &f : faces) {
            f.v1 = (f.v1 * scale) + offset;
            f.v2 = (f.v2 * scale) + offset;
            f.v3 = (f.v3 * scale) + offset;

            // Copiar brdf en los triángulos
            f.brdf = brdf;
        }
    };
    ~TriangleMesh(){};

    float intersection(Point3 o, Vector3 d) const override;
    void recalculateNormals();
    Vector3 normal(Point3 p) const override;
    Point3 centroid() const;
};
