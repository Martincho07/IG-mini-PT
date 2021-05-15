/*********************************************************************************
 * BRDF
 *
 * File: BRDF.cpp
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

// wo ray direction in world coordinates
// Calculates the outgoing ray direction using the reflection law
// The returned direction is in world coordinates
Vector3 specular_reflection(const Vector3 &wo, const Vector3 &normal) {
    return -wo + normal * 2.0f * dot(normal, wo);
};

// Generates a random ray within the hemisphere
// The returned direction is in world coordinates
Vector3 diffuse_reflection(const Vector3 &normal, const Point3 &intersection_point) {
    // Calculate coordinate system local to the intersection point in the direction
    // of the normal
    Vector3 Nt, x, y, z;

    if (std::fabs(normal.x) > std::fabs(normal.y))
        Nt = Vector3(normal.z, 0, -normal.x) / sqrtf(normal.x * normal.x + normal.z * normal.z);
    else
        Nt = Vector3(0, -normal.z, normal.y) / sqrtf(normal.y * normal.y + normal.z * normal.z);

    y = normalize(normal);
    z = cross(normal, Nt);
    z = normalize(z);
    x = cross(y, z);

    // Generate a random direction in the hemisphere
    Vector3 out_dir = uniform_hemisphere_sample();

    // Transform the direction to world coordinates
    return changeBasis(x, y, z, intersection_point)(out_dir);
};

Vector3 phong_reflection(const Vector3 &wr, const Point3 &intersection_point, float alpha) {
    // Generate a coordinate system in the direction of the reflected ray

    Vector3 Nt, x, y, z;

    if (std::fabs(wr.x) > std::fabs(wr.y))
        Nt = Vector3(wr.z, 0, -wr.x) / sqrtf(wr.x * wr.x + wr.z * wr.z);
    else
        Nt = Vector3(0, -wr.z, wr.y) / sqrtf(wr.y * wr.y + wr.z * wr.z);

    y = normalize(wr);
    z = cross(wr, Nt);
    z = normalize(z);
    x = cross(y, z);

    // Phong importance sampling
    Vector3 out_dir = phong_uniform_hemisphere_sample(alpha);

    return changeBasis(x, y, z, intersection_point)(out_dir);
};

Vector3 refraction(const Vector3 &wi, const Vector3 &normal, float n1, float n2) {

    float n = n1 / n2;

    // Compute cosThetaT using Snell's law
    float cosThetaI = dot(normal, wi);
    float sin2ThetaI = std::max(0.0f, 1.0f - cosThetaI * cosThetaI);
    float sin2ThetaT = n * n * sin2ThetaI;

    // Handle total internal reflection for transmission
    assert(sin2ThetaT < 1);

    float cosThetaT = sqrt(1 - sin2ThetaT);

    return -wi * n + normal * (n * cosThetaI - cosThetaT);
};

float fresnel_ks(const Vector3 &wi, const Vector3 &normal, float n1, float n2) {

    float n = n1 / n2;

    float cosThetaI = dot(normal, wi);

    // Compute cosThetaT using Snell's law
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

        float cos_i = dot(wo, si.normal);
        albedo = ((ks / ps) * (cos_i) * ((alpha + 2.0f) / (alpha + 1.0f)));

        return SPECULAR_EVENT;
    }
    default:
        return DEAD_EVENT;
    }
}

EVENT Dielectric::russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const {

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
        wi = specular_reflection(wo, si.normal);
        albedo = ks / ps;
        return SPECULAR_EVENT;
    }
    case REFRACTION_EVENT: {
        if (si.into) {
            wi = refraction(wo, si.normal, AIR_N, n);
        } else {
            wi = refraction(wo, si.normal, n, AIR_N);
        }
        albedo = kt / pt;
        return REFRACTION_EVENT;
    }
    default:
        return DEAD_EVENT;
    }
}
