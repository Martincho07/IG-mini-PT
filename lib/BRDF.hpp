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
#include "geometry.hpp"
#include "image.hpp"
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
    // Textura del material
    TextureMappingUV texture;
    // Alfa de phong
    float alpha;

    // Máximo valor de cada tupla
    float max_kd, max_ks, max_kt, n;

    MaterialProperty(OBJECT_TYPE _type) : type(_type) {}
    MaterialProperty(){};
    virtual ~MaterialProperty() {}

    RGB get_light_power() {

        return light_power;
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

    RGB getKd(float u, float v) {

        return texture.getUV_color(u, v);
    }

    float get_alpha() const {

        return alpha;
    };
};

struct LightPower : MaterialProperty {

    LightPower(RGB _light_power) : MaterialProperty(EMISSOR) {

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

struct Texture : public MaterialProperty {

    Texture(TextureMappingUV _texture) : MaterialProperty(TEXTURE) {
        kd = RGB(0.0f, 0.0f, 0.0f);
        max_kd = 0.0f;
        max_ks = 0.0f;
        max_kt = 0.0f;
        texture = _texture;
        //std::cout << "sssss h: " << texture.img.height << std::endl;
    }
    ~Texture() {}
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
    Phong(RGB _kd, float _ks, float _alpha) : MaterialProperty(PHONG) {

        alpha = _alpha;
        kd = _kd;
        ks = RGB(_ks, _ks, _ks);
        max_kd = max(kd);
        max_ks = _ks;
        max_kt = 0.0f;
    }
    ~Phong() {}
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
