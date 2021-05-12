/*********************************************************************************
 * Camera
 *
 * File: camera.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "BRDF.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "scene.hpp"
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

    Camera(float fov, const Point3 &target, float distance, float aspect_ratio);

    virtual Ray calculate_ray(float x, float y) const = 0;
};

struct PinholeCamera : public Camera {
    PinholeCamera(Point3 _o, Vector3 _r, Vector3 _u, Vector3 _f) : Camera(_o, _r, _u, _f) {}
    PinholeCamera(float fov, const Point3 &target, float distance, float aspect_ratio) : Camera(fov, target, distance, aspect_ratio) {}

    Ray calculate_ray(float x, float y) const;
};

struct ThinLensCamera : public Camera {
    ThinLensCamera(Point3 _o, Vector3 _r, Vector3 _u, Vector3 _f, float _aperture_radius)
        : Camera(_o, _r, _u, _f), aperture_radius(_aperture_radius) {}
    ThinLensCamera(float fov, const Point3 &target, float distance, float aspect_ratio, float _aperture_radius)
        : Camera(fov, target, distance, aspect_ratio), aperture_radius(_aperture_radius) {}

    Ray calculate_ray(float x, float y) const;

    float aperture_radius;
};
