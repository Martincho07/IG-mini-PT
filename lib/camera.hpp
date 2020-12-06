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

#include "color.hpp"
#include "geometry.hpp"
#include "shape.hpp"
#include "transform.hpp"
#include <math.h>
#include <memory>
#include <vector>

struct Camera {

    Point3 o;
    Vector3 r, u, f;
    Transform camera2world;

    Camera(){};

    Camera(Point3 _o, Vector3 _r, Vector3 _u, Vector3 _f) : o(_o), r(_r), u(_u), f(_f) {

        camera2world = Transform(Matrix4x4(r.x, u.x, f.x, o.x,
                                           r.y, u.y, f.y, o.y,
                                           r.z, u.z, f.z, o.z,
                                           0.0f, 0.0f, 0.0f, 1.0f));
    };

    Camera(float fov, const Point3 &target, float distance, float aspect_ratio) {
        // grados a radianes
        fov = fov * M_PI / 180;

        r = Vector3(1, 0, 0);
        u = Vector3(0, 1, 0);
        f = Vector3(0, 0, 1);

        o = target - f + Vector3(0, 0, distance);

        u = u * tanf(fov / 2);
        r = r * aspect_ratio * modulus(u);

        std::cout << "o " << o << " r " << r << " u " << u << " f " << f << std::endl;

        camera2world = Transform(Matrix4x4(r.x, u.x, f.x, o.x,
                                           r.y, u.y, f.y, o.y,
                                           r.z, u.z, f.z, o.z,
                                           0.0f, 0.0f, 0.0f, 1.0f));
    };

    RGB generateRay(Vector3 d, const std::vector<std::shared_ptr<Shape>> &shapes) const;

    RGB generateRay2(float u, float v, const std::vector<std::shared_ptr<Shape>> &shapes) const;
};
