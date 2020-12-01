/*********************************************************************************
 * Image
 *
 * File: BRDF.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "BRDF.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "random.hpp"
#include "transform.hpp"

#include <cmath>
#include <iostream>

RGB LightEmission::light_contribution() const {
    return light_power;
};

RGB PerfectSpecular::light_contribution() const {
    return RGB(1.0f, 1.0f, 1.0f);
};

RGB LambertianDiffuse::light_contribution() const {
    // return kd;
    return kd / M_PI; // TODO: arreglar la intensidad de la luz
};

RGB Phong::light_contribution() const {
    // TODO
    //
    return RGB();
}

RGB Dielectric::light_contribution() const {
    // TODO
    return RGB();
}

Vector3 specular_reflection(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) {
    // wi rayo en coordenadas del mundo
    // Calcular el rayo de salida con la ley de la reflexión
    // Se devuelve en coordenadas del mundo

    return wi + (normal * 2.0f * (dot(wi, normal)));
};

Vector3 diffuse_reflection(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) {
    // wi rayo en coordenadas del mundo
    // Generar un rayo aleatorio dentro de la hemiesfera
    // Se devuelve en coordenadas del mundo

    // Hay que generar un espacio de coordenadas local al punto de intersección,
    // sabiendo la normal en ese punto
    // Generar una dirección aleatoria en la hemiesfera y cambiarla a coordendas del mundo

    float radious = modulus(normal);
    unsigned int seed = rand() % 100;

    Vector3 Nt, x, y, z;

    if (std::fabs(normal.x) > std::fabs(normal.y))
        Nt = Vector3(normal.z, 0, -normal.x) / sqrtf(normal.x * normal.x + normal.z * normal.z);
    else
        Nt = Vector3(0, -normal.z, normal.y) / sqrtf(normal.y * normal.y + normal.z * normal.z);

    y = normalize(normal);
    z = cross(normal, Nt);
    z = normalize(z);
    x = cross(y, z);

    Vector3 out_dir = uniform_hemisphere_sample();

    return changeBasis(x, y, z, intersection_point)(out_dir);
};

Vector3 refraction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) {
    // TODO
    return Vector3();
};

RGB BRDF::specular_contribution() const {};

RGB BRDF::diffuse_contribution() const {};

RGB BRDF::refraction_contribution() const {};