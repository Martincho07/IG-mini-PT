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
#include "shape.hpp"

// #define DEBUG
// #define COLORS

#ifndef DEBUG

RGB Camera::trace_path(float x, float y, const Scene &scene) const {

    bool success = true;
    float distance, coord_u, coord_v;
    RGB texture_color;

    // Albedo after all the interactions
    RGB total_albedo(1, 1, 1);

    RGB point_light_contribution(0, 0, 0);

    // Calculate ray direction
    Vector3 xr = r * x;
    Vector3 yu = u * y;
    Vector3 direction = xr + yu + f;

    SurfaceInteraction si;

    /// TODO:
    // Ray ray(o, normalize(direction));
    Ray ray(o, direction);

    // std::cout << "Inicio albedo " << total_albedo << std::endl;

    // Mientras que no se llegue a una luz o la ruleta diga evento DEAD
    while (success) {

        if (scene.first_intersection(ray, si)) {

            // std::cout << si.position << std::endl;

            // Si es emisor se calcula la perdida de lus en el camino
            // y se retorna la intensidad de la luz
            if (si.shape->material->type == EMISSOR) {
                // std::cout << "emito :) " << std::endl;
                return total_albedo * si.shape->material->get_light_power() + point_light_contribution;
                // En caso contrario se usa la ruleta rusa para determinar si
                // se sigue o no
            } else {

                /// TODO: La dirección del rayo se modifica directamente en russianRoulette
                RGB albedo(1, 1, 1);

                if (si.shape->material->type == TEXTURE) {
                    coord_u = si.shape->getU(si.position);
                    coord_v = si.shape->getV(si.position);
                    texture_color = si.shape->material->getKd(coord_u, coord_v);
                    russianRoulette(texture_color, si.normal, si.position, ray.d, albedo, success);
                    total_albedo = total_albedo * albedo;

                } else {
                    if (si.shape->material->type == DIELECTRIC) {
                        set_dielectric_properties(*si.shape->material, ray.d, si.normal);
                    }

                    russianRoulette(*si.shape->material, si.normal, si.position, ray.d, albedo, success);
                    total_albedo = total_albedo * albedo;

                    if (si.shape->material->type == DIFFUSE) {
                        // std::cout << "albedo antes " << albedo << std::endl;
                        // std::cout << "num lights " << scene.get_num_lights() << std::endl;
                        // Calculate point light contribution
                        for (int i = 0; i < scene.get_num_lights(); i++) {
                            std::shared_ptr<LightSource> light = scene.get_light(i);
                            if (light->is_visible(si.position)) {
                                // std::cout << "albedo después " << albedo << std::endl;
                                // std::cout << "albedo total después " << total_albedo << std::endl;
                                // exit(1);
                                point_light_contribution = point_light_contribution + total_albedo * light->get_incoming_light(si.position) * dot(si.normal, -light->get_incoming_direction(si.position));
                            }
                            // std::cout << point_light_contribution << std::endl;
                        }
                    }
                }

                // std::cout << "albedo encontrado " << albedo << std::endl;
                // std::cout << "nuevo albedo total " << total_albedo << std::endl;

                // return point_light_contribution;

                // Normalizar la nueva dirección del rayo por si acaso
                // std::cout << std::this_thread::get_id() << " llegado antes" << std::endl;
                ray.d = normalize(ray.d);
                // if (modulus(ray.d) == 0) {
                //     Error("Modulo!!!!");
                // }
                // std::cout << std::this_thread::get_id() << " llegado despues" << std::endl;
                // Actualizar la posición del rayo
                ray.o = si.position;
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

    bool success = true;

    float distance;
    RGB alpha(1, 1, 1);

    // Calculate ray direction
    Vector3 xr = r * x;
    Vector3 yu = u * y;
    Vector3 direction = xr + yu + f;

    Ray ray(o, normalize(direction));

    SurfaceInteraction si;

    if (scene.first_intersection(ray, si)) {

        Vector3 n = si.normal;
        n = n * 127.0f;

        // x -> más azul
        // y -> más verde
        // z -> más rojo

#ifdef COLORS
        RGB colors[8] = {RGB(100, 50, 100), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255), RGB(100, 200, 0)};
        return (RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x) + colors[imin % 8]) / 2;
#else
        return RGB(128.0f + n.z, 128.0f + n.y, 128.0f + n.x);
#endif
    }

    return scene.get_background();
};

#endif
