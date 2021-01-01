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

RGB Camera::trace_path(float x, float y, const std::vector<std::shared_ptr<Shape>> &scene) const {

    bool success = true;
    float distance, coord_u, coord_v;
    RGB texture_color;

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

        if (distance != INFINITY && distance > 1e-4f) {

            interc_point = ray_orig + direction * distance;
            normal = shape->normal(interc_point);

            normal = dot(direction, normal) ? normal : -normal;

            // Si es emisor se calcula la perdida de lus en el camino
            // y se retorna la intensidad de la luz
            if (shape->material->type == EMISSOR) {
                // std::cout << "emito :) " << std::endl;
                return alpha * shape->material->get_light_power();
                // En caso contrario se usa la ruleta rusa para determinar si
                // se sigue o no
            } else {

                if (shape->material->type == TEXTURE) {

                    coord_u = shape->getU(interc_point);
                    coord_v = shape->getV(interc_point);
                    texture_color = shape->material->getKd(coord_u, coord_v);
                    russianRoulette(texture_color, normal, interc_point, direction, alpha, success);

                } else {

                    if (shape->material->type == DIELECTRIC)
                        set_dielectric_properties(*shape->material, direction, normal);
                    russianRoulette(*shape->material, normal, interc_point, direction, alpha, success);
                }

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
};
