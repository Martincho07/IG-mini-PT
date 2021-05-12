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
    float distance = modulus(position - p);

    Ray ray(p, position - p);
    SurfaceInteraction si;
    bool i = scene->first_intersection(ray, si);

    return !i || si.t > distance;
}

Vector3 PointLight::get_incoming_direction(const Point3 &p) const {
    return normalize(p - position);
}

RGB PointLight::get_incoming_light(const Point3 &p) const {
    float mod = modulus(p - position);
    return power / (mod * mod);
}
