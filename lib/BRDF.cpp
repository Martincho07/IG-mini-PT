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
#include "error.hpp"
#include "geometry.hpp"
#include "random.hpp"

#include <cmath>
#include <iostream>
#include <memory>

inline Vector3 specular_reflection(const Vector3 &wo, const Vector3 &normal) {
    // wi rayo en coordenadas del mundo
    // Calcular el rayo de salida con la ley de la reflexión
    // Se devuelve en coordenadas del mundo

    /// TODO: Pensar si la normal está ya bien o puede hacer falta darle la vuelta
    // if (dot(wi, normal) < 0.0f) {
    //     return wi + normal * 2.0f * -dot(normal, wi);
    // } else {
    return -wo + normal * 2.0f * dot(normal, wo);
    // return -wo - normal * 2.0f * dot(normal, -wo);
    // return -wo + 2 * Dot(wo, n) * n;
    // Ray reflRay(position, ray.d - normal * 2 * dot(normal, ray.d));
    // }
};

inline Vector3 diffuse_reflection(const Vector3 &normal, const Point3 &intersection_point) {
    // wi rayo en coordenadas del mundo
    // Generar un rayo aleatorio dentro de la hemiesfera
    // Se devuelve en coordenadas del mundo

    // Hay que generar un espacio de coordenadas local al punto de intersección,
    // sabiendo la normal en ese punto
    // Generar una dirección aleatoria en la hemiesfera y cambiarla a coordendas del mundo

    // float radius = modulus(normal);
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

inline Vector3 phong_reflection(const Vector3 &wr, const Point3 &intersection_point, float alpha) {
    // wi rayo en coordenadas del mundo
    // Generar un rayo aleatorio dentro de la hemiesfera
    // Se devuelve en coordenadas del mundo

    // Hay que generar un espacio de coordenadas local al punto de intersección,
    // sabiendo la normal en ese punto
    // Generar una dirección aleatoria en la hemiesfera y cambiarla a coordendas del mundo

    // float radius = modulus(normal);

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

inline Vector3 refraction(const Vector3 &wi, const Vector3 &normal, float n1, float n2) {

    float n = n1 / n2;

    // Compute cosThetaT using Snell's law
    float cosThetaI = dot(normal, wi);
    float sin2ThetaI = std::max(0.0f, 1.0f - cosThetaI * cosThetaI);
    float sin2ThetaT = n * n * sin2ThetaI;

    // Handle total internal reflection for transmission
    assert(sin2ThetaT < 1);
    // if (sin2ThetaT >= 1)
    //     throw("Internal reflection while calculating transmitted direction");
    // return false;

    float cosThetaT = sqrt(1 - sin2ThetaT);

    return -wi * n + normal * (n * cosThetaI - cosThetaT);
};

inline float fresnel_ks(const Vector3 &wi, const Vector3 &normal, float n1, float n2) {

    float n = n1 / n2;

    float cosThetaI = dot(normal, wi);

    // Compute cosThetaT using Shell's law
    float sinThetaI = sqrt(std::max(0.0f, 1 - cosThetaI * cosThetaI));
    float sinThetaT = n * sinThetaI;

    // Handle total internal reflection
    if (sinThetaT >= 1) {
        return 1;
    }

    float cosThetaT = sqrt(std::max(0.0f, 1 - sinThetaT * sinThetaT));

    float rPar = (n2 * cosThetaI - n1 * cosThetaT) /
                 (n2 * cosThetaI + n1 * cosThetaT);
    float rOrth = (n1 * cosThetaI - n2 * cosThetaT) /
                  (n1 * cosThetaI + n2 * cosThetaT);

    return (rOrth * rOrth + rPar * rPar) / 2.0f;
};

/////////////////////////////////
// Russian Roulette functions
/////////////////////////////////

EVENT LambertianDiffuse::russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const {
    switch (random_event(pd, 0, 0)) {
    case DIFFUSE_EVENT: {
        wi = diffuse_reflection(si.normal, si.position);
        albedo = kd / pd;
        return DIFFUSE_EVENT;
    }
    default:
        // albedo = kd / pd;
        return DEAD_EVENT;
    }
}

EVENT Texture::russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const {
    float u = si.shape->getU(si.position);
    float v = si.shape->getV(si.position);
    RGB texture_color = texture.getUV_color(u, v);

    float pd = max(texture_color);

    switch (random_event(pd, 0, 0)) {
    case DIFFUSE_EVENT: {
        wi = diffuse_reflection(si.normal, si.position);
        albedo = texture_color / pd;
        return DIFFUSE_EVENT;
    }
    default:
        return DEAD_EVENT;
    }
}

EVENT PerfectSpecular::russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const {
    // std::cout << "Entrado" << std::endl;
    switch (random_event(0, ps, 0)) {
    case SPECULAR_EVENT: {
        wi = specular_reflection(wo, si.normal);
        albedo = ks / ps;
        return SPECULAR_EVENT;
        break;
    }
    default:
        return DEAD_EVENT;
    }
}

EVENT Plastic::russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const {
    switch (random_event(pd, ps, 0)) {
    case DIFFUSE_EVENT: {
        wi = diffuse_reflection(si.normal, si.position);
        albedo = kd / pd;
        return DIFFUSE_EVENT;
    }
    case SPECULAR_EVENT: {
        wi = specular_reflection(wo, si.normal);
        albedo = ks / ps;
        return SPECULAR_EVENT;
    }
    default:
        return DEAD_EVENT;
    }
}

EVENT Phong::russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const {
    switch (random_event(pd, ps, 0)) {

    case DIFFUSE_EVENT: {
        wi = diffuse_reflection(si.normal, si.position);
        albedo = kd / pd;
        return DIFFUSE_EVENT;
    }
    case SPECULAR_EVENT: {
        Vector3 wr = specular_reflection(wo, si.normal);
        wi = phong_reflection(wr, si.position, alpha);

        if (dot(wi, si.normal) < 0.0f) {
            return DEAD_EVENT;
        }

        // if (dot(wi, si.normal) >= 0.0f) {
        //     return DEAD_EVENT;
        // }

        // if (dot(wi, wr) < 0.0f) {
        //     return DEAD_EVENT;
        // }

        // float cosTh = dot(wi, wo);

        float cos_i = dot(wo, si.normal);
        albedo = ((ks / ps) * (cos_i) * ((alpha + 2.0f) / (alpha + 1.0f)));

        // float sin_r = modulus(cross(wr, si.normal)) / (modulus(wr) * modulus(si.normal));
        // float sin_i = modulus(cross(wi, si.normal)) / (modulus(wi) * modulus(si.normal));
        // float cos_i = dot(wi, si.normal) / (modulus(wi) * modulus(si.normal));

        // albedo = ((ks / ps) * ((cos_i * sin_i) / sin_r) * ((alpha + 2.0f) / (alpha + 1.0f)));
        return SPECULAR_EVENT;
    }
    default:
        return DEAD_EVENT;
    }
}

EVENT Dielectric::russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const {
    // obtener ks y kt

    float coefks;
    if (si.into) {
        coefks = fresnel_ks(wo, si.normal, AIR_N, n);
    } else {
        coefks = fresnel_ks(wo, si.normal, n, AIR_N);
    }
    float coefkt = 1 - coefks;

    coefks = 0.9 * coefks / (coefks + coefkt);
    coefkt = 0.9 * coefkt / (coefks + coefkt);

    RGB ks(coefks, coefks, coefks);
    RGB kt(coefkt, coefkt, coefkt);

    float ps = max(ks);
    float pt = max(kt);

    switch (random_event(0, ps, pt)) {
    case SPECULAR_EVENT: {
        // Error("Specular");
        wi = specular_reflection(wo, si.normal);
        albedo = ks / ps;
        return SPECULAR_EVENT;
    }
    case REFRACTION_EVENT: {
        // Error("Refraction");
        if (si.into) {
            wi = refraction(wo, si.normal, AIR_N, n);
        } else {
            wi = refraction(wo, si.normal, n, AIR_N);
        }
        albedo = kt / pt;
        // albedo = RGB(1, 1, 1);
        return REFRACTION_EVENT;
    }
    default:
        return DEAD_EVENT;
    }
}
