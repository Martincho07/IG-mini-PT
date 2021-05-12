/*********************************************************************************
 * BRDF
 *
 * File: BRDF.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "color.hpp"
#include "event.hpp"
#include "geometry.hpp"
#include "image.hpp"
#include "surface_interaction.hpp"

#include <cmath>
#include <iostream>
#include <memory>

#define AIR_N 1.000293f

enum OBJECT_TYPE { DIFFUSE,
                   TEXTURE,
                   PERFECT_SPECULAR,
                   PHONG,
                   DIELECTRIC,
                   EMISSOR,
                   PLASTIC };

struct Material {

    OBJECT_TYPE type;

    Material(OBJECT_TYPE _type) : type(_type) {}
    Material(){};
    virtual ~Material() {}

    // Performs a Russian roulette for sampling the next ray and the albedo at the intersection
    // Returns false if the Russian roulette chooses DEAD_EVENT
    virtual EVENT russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const = 0;
};

struct LightPower : public Material {
    // Emited light power
    RGB light_power;

    LightPower(RGB _light_power) : Material(EMISSOR) {
        light_power = _light_power;
    }

    EVENT russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const {
        return EMISSION_EVENT;
    };
};

struct LambertianDiffuse : public Material {
    // Diffuse coefficient
    RGB kd;
    float pd;

    LambertianDiffuse(RGB _kd) : Material(DIFFUSE) {
        kd = _kd;
        pd = max(kd);
    }
    ~LambertianDiffuse() {}

    EVENT russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const;
};

struct Texture : public Material {
    // Material texture
    TextureMappingUV texture;

    Texture(TextureMappingUV _texture) : Material(TEXTURE) {
        texture = _texture;
    }
    ~Texture() {}

    EVENT russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const;
};

struct PerfectSpecular : public Material {
    // Specular coefficient
    RGB ks;
    float ps;

    PerfectSpecular(float _ks) : Material(PERFECT_SPECULAR) {
        ks = RGB(_ks, _ks, _ks);
        ps = _ks;
    }
    ~PerfectSpecular() {}

    EVENT russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const;
};

struct Plastic : public Material {
    RGB kd;
    float pd;
    RGB ks;
    float ps;

    // The specular RGB components should be equal (gray-white reflection)
    Plastic(RGB _kd, float _ks) : Material(PLASTIC) {
        kd = _kd;
        ks = RGB(_ks, _ks, _ks);
        pd = max(kd);
        ps = _ks;
    }
    ~Plastic() {}

    EVENT russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const;
};

struct Phong : public Material {
    RGB kd;
    float pd;
    RGB ks;
    float ps;
    float alpha;

    // The specular RGB components should be equal (gray-white reflection)
    Phong(RGB _kd, float _ks, float _alpha) : Material(PHONG) {
        kd = _kd;
        pd = max(_kd);
        ks = RGB(_ks, _ks, _ks);
        ps = _ks;
        alpha = _alpha;
    }
    ~Phong() {}

    EVENT russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const;
};

struct Dielectric : public Material {
    // ks and kt are calculated using Fresnel equations

    // Refraction coefficient
    float n;

    Dielectric(float _n) : Material(DIELECTRIC) {
        n = _n;
    }
    ~Dielectric() {}

    EVENT russian_roulette(const SurfaceInteraction &si, const Vector3 &wo, Vector3 &wi, RGB &albedo) const;
};

Vector3 specular_reflection(const Vector3 &wo, const Vector3 &normal);

Vector3 diffuse_reflection(const Vector3 &normal, const Point3 &intersection_point);

Vector3 phong_reflection(const Vector3 &wr, const Vector3 &normal, const Point3 &intersection_point, float alpha);

Vector3 refraction(const Vector3 &wi, const Vector3 &normal, float n1, float n2);

float fresnel_ks(Vector3 const &wi, const Vector3 &normal, float n1, float n2);
