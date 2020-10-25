/*********************************************************************************
 * Image
 *
 * File: camera.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "geometry.hpp"
#include "transform.hpp"
#include "color.hpp"
#include "shape.hpp"
#include <vector>

struct Camera {


    Point3 o;
    Vector3 u, l, f;
    Transform Camera2World;

    Camera(Point3 _o, Vector3 _u, Vector3 _l, Vector3 _f) : 
    o(_o), u(_u) , l (_l), f(_f) {

        Camera2World = Transform( Matrix4x4 (l.x, u.x, f.x,o.x,
                                             l.y, u.y, f.y, o.y,
                                             l.z, u.z, f.z, o.z,
                                             0.0f, 0.0f, 0.0f, 1.0f));


    };

    RGB GenerateRay(const Vector3 &d, const std::vector<Shape> &shapes);

};



