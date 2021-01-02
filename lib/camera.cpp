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
// #define COLORS

#ifndef DEBUG

RGB Camera::trace_path(float x, float y, const Scene &scene) const {

    bool success = true;
    float distance, coord_u, coord_v;
    RGB texture_color;

    RGB alpha(1, 1, 1);

    // Calculate ray direction
    Vector3 xr = r * x;
    Vector3 yu = u * y;
    Vector3 direction = xr + yu + f;

    SurfaceInteraction si;

    Ray ray(o, normalize(direction));

    // Mientras que no se llegue a una luz o la ruleta diga evento DEAD
    while (success) {

        if (scene.first_intersection(ray, si)) {

            // Si es emisor se calcula la perdida de lus en el camino
            // y se retorna la intensidad de la luz
            if (si.shape->material->type == EMISSOR) {
                // std::cout << "emito :) " << std::endl;
                return alpha * si.shape->material->get_light_power();
                // En caso contrario se usa la ruleta rusa para determinar si
                // se sigue o no
            } else {

                /// TODO: La dirección del rayo se modifica directamente en russianRoulette

                if (si.shape->material->type == TEXTURE) {
                    coord_u = si.shape->getU(si.position);
                    coord_v = si.shape->getV(si.position);
                    texture_color = si.shape->material->getKd(coord_u, coord_v);
                    russianRoulette(texture_color, si.normal, si.position, ray.d, alpha, success);

                } else {
                    if (si.shape->material->type == DIELECTRIC)
                        set_dielectric_properties(*si.shape->material, ray.d, si.normal);

                    russianRoulette(*si.shape->material, si.normal, si.position, ray.d, alpha, success);
                }

                ray.o = si.position;
            }
        } else {
            return scene.get_background();
        }
    }
    return scene.get_background();
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
