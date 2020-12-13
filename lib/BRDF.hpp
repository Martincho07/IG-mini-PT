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
#include <cmath>
#include <iostream>

#define AIR_N 1.000293f

enum OBJECT_TYPE { DIFFUSE,
                   PERFECT_SPECULAR,
                   PHONG,
                   DIELECTRIC,
                   EMISSOR,
                   PLASTIC };
struct MaterialProperty {

    OBJECT_TYPE type;
    // Coeficiente difuso
    RGB kd;
    // Coeficiente especular
    RGB ks;
    // Coeficiente de refracción
    RGB kt;
    // Luz emitida
    RGB light_power;

    // Máximo valor de cada tupla
    float max_kd, max_ks, max_kt, n;

    MaterialProperty(OBJECT_TYPE _type) : type(_type) {}
    virtual ~MaterialProperty() {}

    RGB specular_contribution() const;

    RGB diffuse_contribution() const;

    RGB refraction_contribution() const;

    RGB phong_specular_contribution() const;

    RGB get_light_power() {

        return light_power;
    };

    RGB Diffuse_lobe() const {

        return kd / M_PI; // TODO: arreglar la intensidad de la luz
    };

    RGB PerfectSpecular_lobe() const {
        return RGB(1.0f, 1.0f, 1.0f);
    };

    RGB Phong_lobe(const Vector3 &normal, const Vector3 &wr) const {
        float alpha = 50;
        return ks * ((2.0f + alpha) / (2.0f * M_PI)) * pow(abs(dot(normal, wr)), alpha);
    }

    RGB Reflection_lobe() const {

        // TODO
        return RGB();
    }

    RGB BRDF() {

        return RGB();
    };

    void set_ks(RGB _ks) {

        ks = _ks;
    };

    void set_kt(RGB _kt) {

        kt = _kt;
    };

    void set_max_ks(float _ks) {

        max_ks = _ks;
    };

    void set_max_kt(float _kt) {

        max_kt = _kt;
    };
};

struct LightPower : MaterialProperty {

    LightPower(RGB _light_power) : MaterialProperty(EMISSOR) {
        std::cout << "light: " << _light_power << std::endl;
        light_power = _light_power;
    }
};

struct PuntualLight : MaterialProperty {

    Point3 coordenates;

    PuntualLight(Point3 _coordenates, RGB _light_power) : coordenates(_coordenates), MaterialProperty(EMISSOR) {
        light_power = _light_power;
    }
};

struct LambertianDiffuse : public MaterialProperty {
    LambertianDiffuse(RGB _kd) : MaterialProperty(DIFFUSE) {
        kd = _kd;
        max_kd = max(kd);
        max_ks = 0.0f;
        max_kt = 0.0f;
    }
    ~LambertianDiffuse() {}
};

struct PerfectSpecular : public MaterialProperty {
    PerfectSpecular(float _ks) : MaterialProperty(PERFECT_SPECULAR) {
        ks = RGB(_ks, _ks, _ks);
        max_kd = 0.0f;
        max_ks = _ks;
        max_kt = 0.0f;
    }
    ~PerfectSpecular() {}
};

struct Plastic : public MaterialProperty {
    // The specular RGB components should be equal (gray-white reflection)
    Plastic(RGB _kd, float _ks) : MaterialProperty(PLASTIC) {
        kd = _kd;
        ks = RGB(_ks, _ks, _ks);
        max_kd = max(kd);
        max_ks = _ks;
        max_kt = 0.0f;
    }
    ~Plastic() {}
};

struct Phong : public MaterialProperty {
    // The specular RGB components should be equal (gray-white reflection)
    float alpha;
    Phong(RGB _kd, float _ks, float _alpha) : MaterialProperty(PHONG) {
        std::cout << "AAA: " << _alpha << std::endl;
        alpha = _alpha;
        std::cout << "AAA: " << alpha << std::endl;
        kd = _kd;
        ks = RGB(_ks, _ks, _ks);
        max_kd = max(kd);
        max_ks = _ks;
        max_kt = 0.0f;
    }
    ~Phong() {}
    float get_alpha() {
        ///std::cout << alpha << std::endl;
        return 10.0f;
    };
};

struct Dielectric : public MaterialProperty {

    Dielectric(float _n) : MaterialProperty(DIELECTRIC) {
        n = _n;
        max_kd = 0.0f;
    }
    ~Dielectric() {}
};

Vector3 specular_reflection(const Vector3 &wi, const Vector3 &normal);

Vector3 diffuse_reflection(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point);

Vector3 phong_reflection(const Vector3 &wr, const Vector3 &normal, const Point3 intersection_point, float alpha);

Vector3 reflection(const Vector3 &wi, const Vector3 &normal);

Vector3 refraction(const Vector3 &wi, const Vector3 &normal, float n1, float n2, bool &suscesfull);

float Fresnel_ks(Vector3 const &wi, const Vector3 &normal, float n1, float n2);

void set_dielectric_properties(MaterialProperty &material, const Vector3 direccion, const Vector3 normal);
