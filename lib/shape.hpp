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

#include "color.hpp"
#include "geometry.hpp"

struct Shape {

    RGB color;

    Shape(RGB _color) : color(_color){};
    virtual ~Shape(){};

    virtual float intersection(Point3 o, Vector3 d) const = 0;
};

struct Sphere : public Shape {

    float r;
    Point3 center;

    Sphere(RGB _color, Point3 _center, float _r) : center(_center), r(_r), Shape(_color){};
    ~Sphere(){};

    float intersection(Point3 o, Vector3 d) const override;
};

struct Plane : public Shape {
    Vector3 n;
    float c;

    Plane(RGB _color, Vector3 _n, float _c) : n(_n), c(_c), Shape(_color){};
    ~Plane(){};

    float intersection(Point3 o, Vector3 d) const override;
};
