/*********************************************************************************
 * Light Sources
 *
 * File: light_source.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "light_source.hpp"

Point3 PointLight::get_position() const {
    return position;
}

bool PointLight::is_visible(const Point3 &p) const {
    // return true;
    // std::cout << "\npunto interseccion " << p << std::endl;
    // std::cout << "Posicion luz " << position << std::endl;
    float distance = modulus(position - p);
    // std::cout << "Distancia " << distance << std::endl;

    Ray ray(p, position - p);
    // std::cout << "Direccion " << ray.d << std::endl;
    SurfaceInteraction si;
    bool i = scene->first_intersection(ray, si);

    // std::cout << si.normal << std::endl;

    // if (i)
    //     std::cout << "Intersecado: t " << si.t << ", distance " << distance << std::endl;
    // else
    //     std::cout << "No Intersecado: t " << si.t << ", distance " << distance << std::endl;

    // if (si.t > distance) {
    //     std::cout << "Es visible" << std::endl;
    // }

    // return !i || si.t > distance;
    return !i || si.t > distance;
}

Vector3 PointLight::get_incoming_direction(const Point3 &p) const {
    return normalize(p - position);
}

RGB PointLight::get_incoming_light(const Point3 &p) const {
    float mod = modulus(p - position);
    return power / (mod * mod);
}
