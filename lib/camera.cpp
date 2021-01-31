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
#include "error.hpp"
#include "event.hpp"
#include "geometry.hpp"
#include "random.hpp"
#include "shape.hpp"

// debug
// #define DEBUG
// #define REAL_NORMALS
// #define COLORS

// dof
// #define DOF
#define APERTURE_RADIUS 1

#ifndef DEBUG

RGB Camera::trace_path(float x, float y, const Scene &scene) const {

    bool success = true;
    float distance;
    RGB texture_color;

    // Albedo after all the interactions
    RGB total_albedo(1, 1, 1);

    RGB point_light_contribution(0, 0, 0);

    // Sumar aleatoriamente a x e y un número

    SurfaceInteraction si;

    // Calculate ray direction
#ifndef DOF
    Vector3 xr = r * x;
    Vector3 yu = u * y;
    Vector3 direction = xr + yu + f;

    Ray ray(o, direction);
#else
    float aperture_radius = APERTURE_RADIUS;

    float ua = random_float(-aperture_radius, aperture_radius);
    float va = random_float(-aperture_radius, aperture_radius);

    Point3 oray = o + (r / (2 * modulus(r))) * ua + (u / (2 * modulus(u))) * va;
    Point3 center = o + r * x + u * y + f;

    Vector3 direction = normalize(center - oray);

    Ray ray(oray, direction);
#endif

    // std::cout << "Inicio albedo " << total_albedo << std::endl;

    // Mientras que no se llegue a una luz o la ruleta diga evento DEAD
    Vector3 wi;
    EVENT event;

    while (success) {

        // success = si.shape->material->russian_roulette(si, -ray.d, wi, albedo);

        RGB albedo(1, 1, 1);
        if (scene.first_intersection(ray, si)) {
            event = si.shape->material->russian_roulette(si, -ray.d, wi, albedo);

            // std::cout << si.position << std::endl;

            // Si es emisor se calcula la perdida de lus en el camino
            // y se retorna la intensidad de la luz
            if (event == EMISSION_EVENT) {
                // std::cout << "emito :) " << std::endl;
                return total_albedo * std::static_pointer_cast<LightPower>(si.shape->material)->light_power + point_light_contribution;
                // En caso contrario se usa la ruleta rusa para determinar si
                // se sigue o no
            } else if (event != DEAD_EVENT) {

                // RGB albedo(1, 1, 1);
                // success = si.shape->material->russian_roulette(si, -ray.d, wi, albedo);

                // Error(wi);

                // if (!success) {
                //     continue;
                // }

                // if (success) {
                //     ray = Ray(si.position, wi);
                // }

                ray = Ray(si.position, wi);
                total_albedo = total_albedo * albedo;
                /*
                switch (random_event(0.8, 0, 0)) {
                case DIFFUSE_EVENT: {
                    Vector3 wi = diffuse_reflection(direction, si.normal, si.position);
                    // out_ray = Ray(si.position, direction);
                    albedo = std::static_pointer_cast<LambertianDiffuse>(si.shape->material)->kd / std::static_pointer_cast<LambertianDiffuse>(si.shape->material)->pd;
                    ray.o = si.position;
                    ray.d = normalize(wi);
                    success = true;
                    break;
                }
                default:
                    success = false;
                }
                */

                if (event == DIFFUSE_EVENT) {
                    // std::cout << "albedo antes " << albedo << std::endl;
                    // std::cout << "num lights " << scene.get_num_lights() << std::endl;
                    // Calculate point light contribution
                    for (int i = 0; i < scene.get_num_lights(); i++) {
                        std::shared_ptr<LightSource> light = scene.get_light(i);
                        if (light->is_visible(si.position)) {
                            // std::cout << "albedo después " << albedo << std::endl;
                            // std::cout << "albedo total después " << total_albedo << std::endl;
                            // exit(1);
                            point_light_contribution = point_light_contribution + total_albedo * light->get_incoming_light(si.position) * fabs(dot(si.normal, -light->get_incoming_direction(si.position)));
                        }
                        // std::cout << point_light_contribution << std::endl;
                    }
                }

                // std::cout << "albedo encontrado " << albedo << std::endl;
                // std::cout << "nuevo albedo total " << total_albedo << std::endl;

                // return point_light_contribution;

                // Normalizar la nueva dirección del rayo por si acaso
                // std::cout << std::this_thread::get_id() << " llegado antes" << std::endl;
                // ray.d = normalize(ray.d);
                // if (modulus(ray.d) == 0) {
                //     Error("Modulo!!!!");
                // }
                // std::cout << std::this_thread::get_id() << " llegado despues" << std::endl;
                // Actualizar la posición del rayo
                // ray.o = si.position;
            } else {
                success = false;
            }
        } else {
            success = false;
        }
    }

    // std::cout << "salgo de la ruleta " << std::endl;

    if (max(point_light_contribution) > 0) {
        // std::cout << "Hay luz" << std::endl;
        return point_light_contribution;
    } else {
        return scene.get_background();
    }
};

#else

// Definir el color en base a la normal del objeto
RGB Camera::trace_path(float x, float y, const Scene &scene) const {

    // bool success = true;

    // float distance;
    // RGB alpha(1, 1, 1);

#ifndef DOF
    // // Calculate ray direction
    Vector3 xr = r * x;
    Vector3 yu = u * y;
    Vector3 direction = xr + yu + f;

    Ray ray(o, direction);

#else

    // Rejection sampling
    float r1, r2;
    float aperture_radius = APERTURE_RADIUS;

    // do {
    //     r1 = random_float();
    //     r2 = random_float();
    // } while (r1 * r1 + r2 * r2 <= 1);

    // float max = aperture_radius;
    // float min = -aperture_radius;

    // float ua = (max - min) * r1 + min;
    // float va = (max - min) * r2 + min;

    // do {
    //     r1 = random_float(-aperture_radius, aperture_radius);
    //     r2 = random_float(-aperture_radius, aperture_radius);
    // } while (r1 * r1 + r2 * r2 <= aperture_radius);

    // float ua = r1;
    // float va = r2;

    // u v samplear punto en la apertura
    float ua = random_float(-aperture_radius, aperture_radius);
    float va = random_float(-aperture_radius, aperture_radius);

    Point3 oray = o + (r / (2 * modulus(r))) * ua + (u / (2 * modulus(u))) * va;
    Point3 center = o + r * x + u * y + f;

    Vector3 direction = normalize(center - oray);
    Ray ray(oray, direction);

#endif

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

#ifdef COLORS
        RGB colors[8] = {RGB(100, 50, 100), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255), RGB(100, 200, 0)};
        return (RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x) + colors[min_p % 8]) / 2;
#else
        return RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x);
#endif
    }

    return scene.get_background();
};

#endif
