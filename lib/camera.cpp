/*********************************************************************************
 * Image
 *
 * File: camera.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/
#include <cmath>
#include <iostream>
#include <memory>

#include "BRDF.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "shape.hpp"

// #define DEBUG
// #define COLORES

#ifndef DEBUG
RGB Camera::generateRay(Vector3 d, const std::vector<std::shared_ptr<Shape>> &shapes) const {

    RGB color(0, 0, 0);
    RGB alpha(1, 1, 1);
    float t = INFINITY;
    float shape_t = 0.0f;
    Vector3 normal;
    PerfectSpecular spec;
    std::shared_ptr<Shape> object;
    Point3 p;
    Point3 _o = o;

    d = camera2world(d);
    for (int i = 0; i < 20; i++) {
        t = INFINITY;
        shape_t = 0.0f;

        for (const std::shared_ptr<Shape> &s : shapes) {
            shape_t = s->intersection(_o, d);

            if (shape_t < t && shape_t > 0.0f) {

                t = shape_t;
                object = s;
            }
        }

        if (t != INFINITY && t > 0.0f) {

            p = o + d * t;
            normal = object->normal(p);

            if (object->brdf->type == EMISSOR) {
                //std::cout << "Llegoo a luz" << std::endl;
                color = alpha * object->brdf->light_contribution();
                return color;
            } else if (object->brdf->type == LAMBERTIAN_DIFFUSE) {

                d = object->brdf->output_direction(d, normal, p);
                _o = p;
                alpha = alpha * (object->brdf->light_contribution() * dot(d, normal));

            } else if (object->brdf->type == PERFECT_SPECULAR) {

                d = object->brdf->output_direction(-d, normal, p);
                _o = p;
                alpha = alpha * object->brdf->light_contribution();
            }
        }
    };

    return color;
};

RGB Camera::generateRay2(float x, float y, const std::vector<std::shared_ptr<Shape>> &shapes) const {

    RGB color(0, 0, 0);
    RGB alpha(1, 1, 1);
    float t = INFINITY;
    float shape_t = 0.0f;
    Vector3 normal;
    PerfectSpecular spec;
    std::shared_ptr<Shape> object;

    Point3 p;
    Point3 _o = o;

    Vector3 xr = r * x;
    Vector3 yu = u * y;

    Vector3 d = xr + yu + f;
    normalize(d);

    for (int i = 0; i < 20; i++) {
        t = INFINITY;
        shape_t = 0.0f;

        for (const std::shared_ptr<Shape> &s : shapes) {
            shape_t = s->intersection(_o, d);

            if (shape_t < t && shape_t > 0.0f) {

                t = shape_t;
                object = s;
            }
        }

        if (t != INFINITY && t > 0.0f) {

            p = o + d * t;
            normal = object->normal(p);

            if (object->brdf->type == EMISSOR) {
                //std::cout << "Llegoo a luz" << std::endl;
                color = alpha * object->brdf->light_contribution();
                return color;
            } else if (object->brdf->type == LAMBERTIAN_DIFFUSE) {

                d = object->brdf->output_direction(d, normal, p);
                _o = p;
                alpha = alpha * (object->brdf->light_contribution() * dot(d, normal));

            } else if (object->brdf->type == PERFECT_SPECULAR) {

                d = object->brdf->output_direction(-d, normal, p);
                _o = p;
                alpha = alpha * object->brdf->light_contribution();
            }
        }
    };

    return color;
};

#else

#ifdef COLORES

RGB Camera::generateRay(Vector3 d, const std::vector<std::shared_ptr<Shape>> &shapes) const {

    RGB colors[8] = {RGB(100, 50, 100), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255), RGB(100, 200, 0)};

    RGB color(255, 255, 255);
    float tmin = INFINITY;
    float t = 0.0f;

    for (int i = 0; i < shapes.size(); i++) {
        t = shapes[i]->intersection(o, camera2world(d));

        if (t < tmin && t > 0.0f) {
            color = colors[i];
            tmin = t;
        }
    }

    return color;
};

#else

// Definir el color en base a la normal del objeto
RGB Camera::generateRay(Vector3 d, const std::vector<std::shared_ptr<Shape>> &shapes) const {

    RGB color(255, 255, 255);
    float tmin = INFINITY;
    float t = 0.0f;

    Vector3 n;

    // for (std::shared_ptr<Shape> s : shapes) {
    //     t = s->intersection(o, camera2world(d));

    //     if (t < tmin && t > 0.0f) {
    //         Point3 p = o + camera2world(d) * t;
    //         n = s->normal(p);
    //         tmin = t;
    //     }
    // }

    int imin;

    for (int i = 0; i < shapes.size(); i++) {
        t = shapes[i]->intersection(o, camera2world(d));
        if (t < tmin && t > 0.0f) {
            Point3 p = o + camera2world(d) * t;
            n = shapes[i]->normal(p);
            tmin = t;
            imin = i;
        }
    }

    n = normalize(n);
    n = n * 127.0f;

    // std::cout << n << std::endl;

    // x -> más azul
    // y -> más verde
    // z -> más rojo

    // Coger un color aleatorio
    RGB colors[8] = {RGB(100, 50, 100), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255), RGB(100, 200, 0)};

    color = (RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x) + colors[imin]) / 2;

    // if (n.x < 0) {
    //     std::cout << "menor de 0" << std::endl;
    //     exit(1);
    // }

    // float green = std::abs(n.x * n.y * 255);

    // // Si la normal apunta hacia la cámara, rojo
    // if (n.z < 0) {
    //     color = RGB(255, green, 0);
    // }
    // // Si no, azul
    // else {
    //     color = RGB(0, green, 255);
    // }

    return color;
};

// Definir el color en base a la normal del objeto
RGB Camera::generateRay2(float x, float y, const std::vector<std::shared_ptr<Shape>> &shapes) const {

    RGB color(255, 255, 255);
    float tmin = INFINITY;
    float t = 0.0f;

    Vector3 n;

    Vector3 xr = r * x;
    Vector3 yu = u * y;

    Vector3 d = xr + yu + f;
    normalize(d);

    // for (std::shared_ptr<Shape> s : shapes) {
    //     t = s->intersection(o, camera2world(d));

    //     if (t < tmin && t > 0.0f) {
    //         Point3 p = o + camera2world(d) * t;
    //         n = s->normal(p);
    //         tmin = t;
    //     }
    // }

    int imin;

    for (int i = 0; i < shapes.size(); i++) {
        t = shapes[i]->intersection(o, d);
        if (t < tmin && t > 0.0f) {
            Point3 p = o + d * t;
            n = shapes[i]->normal(p);
            tmin = t;
            imin = i;
        }
    }

    n = normalize(n);
    n = n * 127.0f;

    // std::cout << n << std::endl;

    // x -> más azul
    // y -> más verde
    // z -> más rojo

    // Coger un color aleatorio
    RGB colors[8] = {RGB(100, 50, 100), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255), RGB(100, 200, 0)};

    color = (RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x) + colors[imin]) / 2;

    // if (n.x < 0) {
    //     std::cout << "menor de 0" << std::endl;
    //     exit(1);
    // }

    // float green = std::abs(n.x * n.y * 255);

    // // Si la normal apunta hacia la cámara, rojo
    // if (n.z < 0) {
    //     color = RGB(255, green, 0);
    // }
    // // Si no, azul
    // else {
    //     color = RGB(0, green, 255);
    // }

    return color;
};

#endif

#endif