/*********************************************************************************
 * Camera
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
#include "error.hpp"
#include "event.hpp"
#include "geometry.hpp"
#include "random.hpp"
#include "shape.hpp"

// debug
// #define DEBUG
// #define REAL_NORMALS

// dof
// #define DOF
#define APERTURE_RADIUS 3

inline Ray Camera::calculate_ray(float x, float y) const {
#ifndef DOF
    Vector3 xr = r * x;
    Vector3 yu = u * y;
    Vector3 direction = xr + yu + f;

    return Ray(o, direction);
#else
    float ua, va;
    float aperture_radius = APERTURE_RADIUS;

    // Rejection sampling
    // float r1, r2;
    // do {
    //     r1 = random_float();
    //     r2 = random_float();
    // } while (r1 * r1 + r2 * r2 <= 1);
    // float max = aperture_radius;
    // float min = -aperture_radius;
    // ua = (max - min) * r1 + min;
    // va = (max - min) * r2 + min;

    // https://stackoverflow.com/questions/5837572/generate-a-random-point-within-a-circle-uniformly
    float arand = aperture_radius * sqrt(random_float());
    float theta = random_float() * 2 * M_PI;
    ua = arand * cos(theta);
    va = arand * sin(theta);

    // // Random
    // ua = random_float(-aperture_radius, aperture_radius);
    // va = random_float(-aperture_radius, aperture_radius);

    Point3 oray = o + (r / (2 * modulus(r))) * ua + (u / (2 * modulus(u))) * va;
    Point3 center = o + r * x + u * y + f;

    Vector3 direction = normalize(center - oray);

    return Ray(oray, direction);
#endif
}

#ifndef DEBUG

RGB Camera::trace_path(float x, float y, const Scene &scene) const {

    bool success = true;
    float distance;
    RGB texture_color;

    // Albedo after all the interactions
    RGB total_albedo(1, 1, 1);

    RGB point_light_contribution(0, 0, 0);

    SurfaceInteraction si;
    Ray ray = calculate_ray(x, y);

    Vector3 wi;
    EVENT event;

    // Mientras que no se llegue a una luz de área o la ruleta diga evento DEAD
    while (success) {
        RGB albedo(1, 1, 1);
        if (scene.first_intersection(ray, si)) {
            event = si.shape->material->russian_roulette(si, -ray.d, wi, albedo);

            // Si es emisor se calcula la perdida de lus en el camino
            // y se retorna la intensidad de la luz
            if (event == EMISSION_EVENT) {
                return total_albedo * std::static_pointer_cast<LightPower>(si.shape->material)->light_power + point_light_contribution;

            } else if (event != DEAD_EVENT) {
                // En caso contrario se usa la ruleta rusa para determinar si
                // se sigue o no
                ray = Ray(si.position, wi);
                total_albedo = total_albedo * albedo;

                if (event == DIFFUSE_EVENT) {
                    for (int i = 0; i < scene.get_num_lights(); i++) {
                        std::shared_ptr<LightSource> light = scene.get_light(i);
                        if (light->is_visible(si.position)) {
                            point_light_contribution = point_light_contribution + total_albedo * light->get_incoming_light(si.position) * fabs(dot(si.normal, -light->get_incoming_direction(si.position)));
                        }
                    }
                }
            } else {
                success = false;
            }
        } else {
            success = false;
        }
    }

    if (max(point_light_contribution) > 0) {
        return point_light_contribution;
    } else {
        return scene.get_background();
    }
};

#else

// Definir el color en base a la normal del objeto
RGB Camera::trace_path(float x, float y, const Scene &scene) const {

    Ray ray = calculate_ray(x, y);
    SurfaceInteraction si;

    if (scene.first_intersection(ray, si)) {

#ifdef REAL_NORMALS
        Vector3 n = si.into ? si.normal : -si.normal;
#else
        Vector3 n = si.normal;
#endif
        n = n * 127.0f;
        // x -> más azul
        // y -> más verde
        // z -> más rojo

        return RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x);
        return RGB(n.x, n.y, n.z);
    }

    return scene.get_background();
};

#endif
