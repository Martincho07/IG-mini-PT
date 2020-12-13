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

Vector3 specular_reflection(const Vector3 &wi, const Vector3 &normal) {
    // wi rayo en coordenadas del mundo
    // Calcular el rayo de salida con la ley de la reflexión
    // Se devuelve en coordenadas del mundo
    float cosI = -dot(wi, normal);

    return wi + normal * 2.0f * cosI;
};

Vector3 diffuse_reflection(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) {
    // wi rayo en coordenadas del mundo
    // Generar un rayo aleatorio dentro de la hemiesfera
    // Se devuelve en coordenadas del mundo

    // Hay que generar un espacio de coordenadas local al punto de intersección,
    // sabiendo la normal en ese punto
    // Generar una dirección aleatoria en la hemiesfera y cambiarla a coordendas del mundo

    float radious = modulus(normal);
    //unsigned int seed = rand() % 100;

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

Vector3 phong_reflection(const Vector3 &wr, const Vector3 &normal, const Point3 intersection_point, float alpha) {
    // wi rayo en coordenadas del mundo
    // Generar un rayo aleatorio dentro de la hemiesfera
    // Se devuelve en coordenadas del mundo

    // Hay que generar un espacio de coordenadas local al punto de intersección,
    // sabiendo la normal en ese punto
    // Generar una dirección aleatoria en la hemiesfera y cambiarla a coordendas del mundo

    float radious = modulus(normal);
    //unsigned int seed = rand() % 100;

    Vector3 Nt, x, y, z;

    if (std::fabs(wr.x) > std::fabs(wr.y))
        Nt = Vector3(wr.z, 0, -wr.x) / sqrtf(wr.x * wr.x + wr.z * wr.z);
    else
        Nt = Vector3(0, -wr.z, wr.y) / sqrtf(wr.y * wr.y + wr.z * wr.z);

    y = normalize(wr);
    z = cross(wr, Nt);
    z = normalize(z);
    x = cross(y, z);

    Vector3 out_dir = phong_uniform_hemisphere_sample(alpha);

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

Vector3 reflection(const Vector3 &wi, const Vector3 &normal) {
    return wi + (normal * (2 * -dot(normal, wi)));
};

Vector3 refraction(const Vector3 &wi, const Vector3 &normal, float n1, float n2, bool &suscesfull) {

    float n = n1 / n2;
    float cosI = -dot(normal, wi);
    float sinT2 = n * n * (1.0f - cosI * cosI);
    if (sinT2 > 1.0f) {
        suscesfull = false;
        return Vector3();
    }

    float cosT = std::sqrt(1.0f - sinT2);
    suscesfull = true;
    return (wi * n) + (normal * (n * cosI - cosT));
};

RGB MaterialProperty::specular_contribution() const {
    // return RGB(1, 1, 1);
    // return ks / max_ks;
    return ks;
};

RGB MaterialProperty::diffuse_contribution() const {
    // TODO
    // return kd / M_PI;
    // return kd / max_kd;
    return kd;
};

RGB MaterialProperty::refraction_contribution() const {
    // return kt / max_kt;
    return kt;
};

RGB MaterialProperty::phong_specular_contribution() const {
    // return kt / max_kt;

    /// TODO
    float alpha = 1;

    // Hay que pasar como parámetros el vector origen y el vector reflejado
    Vector3 wo;
    Vector3 wr;
    return ks * ((alpha + 2) / 2 * M_PI) * fabs(dot(wo, wr));
};

float Fresnel_ks(Vector3 const &wi, const Vector3 &normal, float n1, float n2) {

    float n = n1 / n2;
    float cosI = -dot(normal, wi);
    float sinT2 = n * n * (1.0f - cosI * cosI);
    if (sinT2 > 1.0f)
        return 1.0f;

    float cosT = sqrt(1.0f - sinT2);
    float r0rth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
    float rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);

    return (r0rth * r0rth + rPar * rPar) / 2.0f;
};

void set_dielectric_properties(MaterialProperty &material, const Vector3 direccion, const Vector3 normal) {

    float fresnel_ks, fresnel_kt;

    if (dot(direccion, normal) < 0.0f)

        fresnel_ks = Fresnel_ks(direccion, normal, AIR_N, material.n);
    else

        fresnel_ks = Fresnel_ks(direccion, -normal, material.n, AIR_N);

    fresnel_kt = 1.0f - fresnel_ks;
    fresnel_ks = 0.95f * fresnel_ks;
    fresnel_kt = 0.95f * fresnel_kt;

    material.set_max_ks(fresnel_ks);
    material.set_max_kt(fresnel_kt);

    material.set_ks(RGB(fresnel_ks, fresnel_ks, fresnel_ks));
    material.set_kt(RGB(fresnel_kt, fresnel_kt, fresnel_kt));
}
