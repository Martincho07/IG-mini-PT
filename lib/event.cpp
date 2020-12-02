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
#include "random.hpp"

EVENT randomEvent(const BRDF &material) {
    // Russian roulette

    // Elegir número entre 0 - 1
    float rand = random_float();

    // std::cout << rand << std::endl;

    // Ver dónde ha caído el punto y devolver ese evento
    if (rand < material.max_kd) {
        return DIFFUSE;
    } else if (rand < material.max_kd + material.max_ks) {
        return SPECULAR;
    } else if (rand < material.max_kd + material.max_ks + material.max_kt) {
        return REFRACTION;
    } else {
        return DEAD;
    }
}

/*
Vector3 output

    Vector3
    output_direction(EVENT event, const Vector &wi, const Vector3 &normal, const Point3 intersection_point) {
}
*/