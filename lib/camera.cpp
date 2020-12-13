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
#include "event.hpp"
#include "geometry.hpp"
#include "shape.hpp"

// #define DEBUG
// #define COLORES

#ifndef DEBUG

/*
RGB Camera::generateRay(Vector3 d, const std::vector<std::shared_ptr<Shape>> &shapes) const {

    RGB color(0, 0, 0);
    RGB alpha(1, 1, 1);
    float t = INFINITY;
    float shape_t = 0.0f;
    Vector3 normal;
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
                color = alpha * object->brdf->light_contribution();
                return color;
            } else if (object->brdf->type == LAMBERTIAN_DIFFUSE) {

                d = diffuse_reflection(d, normal, p);
                _o = p;
                alpha = alpha * (object->brdf->light_contribution() * dot(d, normal));

            } else if (object->brdf->type == PERFECT_SPECULAR) {

                d = specular_reflection(-d, normal, p);
                _o = p;
                alpha = alpha * object->brdf->light_contribution();
            }
        }
    };

    return color;
};
*/
RGB Camera::generateRay2(float x, float y, const std::vector<std::shared_ptr<Shape>> &scene) const {

    bool success = true;
    float distance;
    RGB alpha(1.0f, 1.0f, 1.0f);
    Vector3 normal;
    Point3 interc_point, ray_orig;
    ray_orig = o;
    std::shared_ptr<Shape> shape;

    // Calculate ray direction
    Vector3 xr = r * x;
    Vector3 yu = u * y;
    Vector3 direction = xr + yu + f;
    normalize(direction);

    // Mientras que no se llegue a una luz o la ruleta diga evento DEAD
    while (success) {

        distance = intersection(scene, shape, ray_orig, direction);
        //std::cout << "t: " << t << std::endl;
        if (distance != INFINITY && distance > 1e-4f) {

            interc_point = ray_orig + direction * distance;
            normal = shape->normal(interc_point);

            // Si es emisor se calcula la perdida de lus en el camino
            // y se retorna la intensidad de la luz
            if (shape->material->type == EMISSOR) {
                //if (shape->material->type == PLASTIC)
                //std::cout << "power: " << shape->material->get_light_power() << std::endl;
                //std::cout << "alpha: " << alpha << std::endl;
                //std::cout << "alpha ret: " << alpha * shape->material->get_light_power() << std::endl;
                return alpha * shape->material->get_light_power();

                // En caso contrario se usa la ruleta rusa para determinar si
                // se sigue o no
            } else {

                if (shape->material->type == DIELECTRIC)
                    set_dielectric_properties(*shape->material, direction, normal);

                RussianRoulette(*shape->material, normal, interc_point, direction, alpha, success);
                ray_orig = interc_point;
            }
        } else {

            return RGB(0.0f, 0.0f, 0.0f);
        }
    }
    return RGB(0.0f, 0.0f, 0.0f);
};

float intersection(const std::vector<std::shared_ptr<Shape>> &scene, std::shared_ptr<Shape> &shape, const Point3 &ray_orig, const Vector3 &direction) {

    float distance = INFINITY;
    float shape_t = 0.0f;

    for (const std::shared_ptr<Shape> &s : scene) {
        shape_t = s->intersection(ray_orig, direction);

        if (shape_t < distance && shape_t > 1e-4f) {
            distance = shape_t;
            shape = s;
        }
    }

    return distance;
}

#else

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

    // Coger un color dependiendo de la posición

#ifdef COLORES
    RGB colors[8] = {RGB(100, 50, 100), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255), RGB(100, 200, 0)};
    color = (RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x) + colors[imin % 8]) / 2;
#else
    color = RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x);
#endif

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
