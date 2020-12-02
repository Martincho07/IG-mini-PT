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

/*
Vector3 refraction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) {
    // TODO
    float ior = 1.8; // index of refraction del objeto
    // Coeficientes de refracción
    Vector3 Nrefr = normal;
    float NdotI = dot(Nrefr, wi);
    float etai = 1; // etai is the index of refraction of the medium the ray is in before entering the second medium
    float etat = ior;

    if (NdotI < 0) {
        // we are outside the surface, we want cos(theta) to be positive
        NdotI = -NdotI;
    } else {
        // we are inside the surface, cos(theta) is already positive but reverse normal direction
        Nrefr = -normal;
        // swap the refraction indices
        std::swap(etai, etat);
    }
    float eta = etai / etat; // n_1 / n_2

    float cosi = dot(wi, normal);
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0)
        // total internal reflection. There is no refraction in this case
        return Vector3(0, 0, 0);
    else
        return wi * eta + Nrefr * (eta * NdotI - sqrtf(k));
};
*/

Vector3 refraction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) {
    // TODO
    float ior = 1.5;
    float cosi = dot(wi, normal);

    float etai = 1;
    float etat = ior;

    Vector3 n = normal;

    if (cosi < 0) {
        cosi = -cosi;
    } else {
        std::swap(etai, etat);
        n = -normal;
    }

    float eta = etai / etat;

    float k = 1 - eta * eta * (1 - cosi * cosi);

    // return k < 0 ? Vector3(0, 0, 0) : wi * eta + n * (eta * cosi - sqrtf(k));
    return k < 0 ? Vector3(0, 0, 0) : wi * eta + n * (eta * cosi - sqrtf(k));
};

RGB BRDF::specular_contribution() const {
    // return RGB(1, 1, 1);
    // return ks / max_ks;
    return ks;
};

RGB BRDF::diffuse_contribution() const {
    // TODO
    // return kd / M_PI;
    // return kd / max_kd;
    return kd;
};

RGB BRDF::refraction_contribution() const {
    // return kt / max_kt;
    return kt;
};

RGB BRDF::phong_specular_contribution() const {
    // return kt / max_kt;

    /// TODO
    float alpha = 1;

    // Hay que pasar como parámetros el vector origen y el vector reflejado
    Vector3 wo;
    Vector3 wr;
    return ks * ((alpha + 2) / 2 * M_PI) * fabs(dot(wo, wr));
};