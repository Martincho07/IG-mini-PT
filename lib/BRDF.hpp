/*********************************************************************************
 * Image
 *
 * File: BRDF.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/
#pragma once
#include "color.hpp"
#include "geometry.hpp"

enum BRDF_TYPE { LAMBERTIAN_DIFFUSE,
                 PERFECT_SPECULAR,
                 PHONG,
                 DIELECTRIC,
                 EMISSOR };
struct BRDF {

    BRDF_TYPE type;
    // Coeficiente difuso
    RGB kd;
    // Coeficiente especular
    RGB ks;
    // Coeficiente de refracción
    RGB kt;
    // Luz emitida
    RGB light_power;

    // Máximo valor de cada tupla
    float max_kd, max_ks, max_kt;

    BRDF(BRDF_TYPE _type) : type(_type) {}
    virtual ~BRDF() {}

    virtual RGB light_contribution() const = 0;

    RGB specular_contribution() const;

    RGB diffuse_contribution() const;

    RGB refraction_contribution() const;

    RGB phong_specular_contribution() const;
};

struct LightEmission : public BRDF {
    LightEmission(RGB _light_power) : BRDF(EMISSOR) {
        light_power = _light_power;
        max_kd = 0;
        max_ks = 0;
        max_kt = 0;
    }
    ~LightEmission() {}
    RGB light_contribution() const;
};

struct LambertianDiffuse : public BRDF {
    LambertianDiffuse(RGB _kd) : BRDF(LAMBERTIAN_DIFFUSE) {
        kd = _kd;
        max_kd = max(kd);
        max_ks = 0;
        max_kt = 0;
    }
    ~LambertianDiffuse() {}
    RGB light_contribution() const;
};

struct PerfectSpecular : public BRDF {
    PerfectSpecular(RGB _ks) : BRDF(PERFECT_SPECULAR) {
        ks = _ks;
        max_kd = 0;
        max_ks = max(ks);
        max_kt = 0;
    }
    ~PerfectSpecular() {}
    RGB light_contribution() const;
};

struct Phong : public BRDF {
    // The specular RGB components should be equal (gray-white reflection)
    Phong(RGB _kd, RGB _ks) : BRDF(PHONG) {
        kd = _kd;
        ks = _ks;
        max_kd = max(kd);
        max_ks = max(ks);
        max_kt = 0;
    }
    ~Phong() {}
    RGB light_contribution() const;
};

struct Dielectric : public BRDF {
    Dielectric(RGB _ks, RGB _kt) : BRDF(DIELECTRIC) {
        ks = _ks;
        kt = _kt;
        max_kd = 0;
        max_ks = max(ks);
        max_kt = max(kt);
    }
    ~Dielectric() {}
    RGB light_contribution() const;
};

Vector3 specular_reflection(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point);

Vector3 diffuse_reflection(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point);

Vector3 refraction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point);