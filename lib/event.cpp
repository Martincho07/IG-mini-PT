/*********************************************************************************
 * Event
 *
 * File: event.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 1/12/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "event.hpp"
#include "BRDF.hpp"
#include <cmath>
#include <iostream>

EVENT randomEvent(const Material &material) {
    // Russian roulette

    // Elegir número entre 0 - 1
    float rand = random_float();
    // Ver dónde ha caído el punto y devolver ese evento
    if (rand < material.max_kd) {
        return DIFFUSE_EVENT;
        std::cout << "por queee" << std::endl;
    } else if (rand < material.max_kd + material.max_ks) {

        return SPECULAR_EVENT;
    } else if (rand < material.max_kd + material.max_ks + material.max_kt) {

        return REFRACTION_EVENT;
    } else {
        return DEAD_EVENT;
    }
}

EVENT randomEvent(const RGB &texture) {
    // Russian roulette

    // Elegir número entre 0 - 1
    float rand = random_float();
    // Ver dónde ha caído el punto y devolver ese evento
    if (rand < max(texture)) {
        return DIFFUSE_EVENT;

    } else {
        return DEAD_EVENT;
    }
}

void russianRoulette(const Material &material, const Vector3 &normal, const Point3 &point, Vector3 &direction, RGB &albedo, bool &success) {

    success = true;
    int event;
    Vector3 inc;
    event = randomEvent(material);
    float u, v;
    switch (event) {

    case DIFFUSE_EVENT:

        direction = diffuse_reflection(direction, normal, point);
        albedo = (material.kd / material.max_kd);

        break;

    case SPECULAR_EVENT:

        inc = direction;

        if (dot(direction, normal) < 0.0f) {
            direction = specular_reflection(direction, normal);
        } else {

            direction = specular_reflection(direction, -normal);
        }

        if (material.type == PHONG) {

            Vector3 reflected_ray = direction;
            float alpha = material.get_alpha();

            direction = phong_reflection(direction, normal, point, alpha);
            if (dot(direction, normal) < 0.0f) {
                success = false;
                return;
            }

            float cosTh = dot(reflected_ray, direction);

            float sin_r = modulus(cross(reflected_ray, normal)) / (modulus(reflected_ray) * modulus(normal));
            float sin_i = modulus(cross(inc, normal)) / (modulus(inc) * modulus(normal));
            float cos_i = -(dot(inc, normal) / (modulus(inc) * modulus(normal)));
            albedo = ((material.ks / material.max_ks) * ((cos_i * sin_i) / sin_r) * ((alpha + 2.0f) / (alpha + 1.0f)));

        } else {

            albedo = (material.ks / material.max_ks);
        }

        break;

    case REFRACTION_EVENT:

        if (dot(direction, normal) < 0.0f)

            direction = refraction(direction, normal, AIR_N, material.n, success);
        else
            direction = refraction(direction, -normal, material.n, AIR_N, success);

        if (!success)
            return;
        albedo = (material.kt / material.max_kt);

        break;

    default:
        success = false;
        break;
    }
};

void russianRoulette(const RGB &texture, const Vector3 &normal, const Point3 &point, Vector3 &direction, RGB &albedo, bool &success) {

    success = true;
    int event;
    event = randomEvent(texture);
    switch (event) {

    case DIFFUSE_EVENT:

        direction = diffuse_reflection(direction, normal, point);
        albedo = (texture / max(texture));
        break;

    default:
        success = false;
        break;
    }
};
