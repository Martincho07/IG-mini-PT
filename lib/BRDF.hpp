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
/*
struct DeltaFunction {

    Vector3 w_r;

    DeltaFunction(){};
    DeltaFunction(Vector3 _w_r) : w_r(_w_r){};
    ~DeltaFunction(){};

    float operator()(Vector3 w_i) const {

        if (w_r.x == w_i.x && w_r.y == w_i.y && w_r.z == w_i.z)
            Vector3(1.0f, 1.0f, 1.0f);
        else
            Vector3(0.0f, 0.0f, 0.0f);
    };
};
*/
enum BRDF_TYPE { LAMBERTIAN_DIFFUSE,
                 PERFECT_SPECULAR,
                 PHONG_BRDF,
                 EMISSOR };
struct BRDF {

    BRDF_TYPE type;
    RGB kd;
    RGB ks;
    RGB ligth_power;

    BRDF(BRDF_TYPE _type) : type(_type) {}
    virtual ~BRDF() {}

    virtual RGB light_contribution() const = 0;
    virtual Vector3 output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const = 0;
};

struct LigthEmission : BRDF {
    // LigthEmission() : BRDF(EMISSOR) {}
    LigthEmission(RGB _ligth_power) : BRDF(EMISSOR) {
        BRDF::light_power = _light_power;
    }
    RGB light_contribution() const override;
    Vector3 output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const override;
};

struct LambertianDiffuse : public BRDF {

    // LambertianDiffuse() : BRDF(LAMBERTIAN_DIFFUSE) {}
    LambertianDiffuse(RGB _kd) : BRDF(LAMBERTIAN_DIFFUSE) {
        kd = _kd
            ks = 0
    }
    ~LambertianDiffuse() {}

    RGB light_contribution() const override;
    Vector3 output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const override;
};

struct PerfectSpecular : public BRDF {

    PerfectSpecular(RGB _ks) : BRDF(PERFECT_SPECULAR) {
        ks = _ks
    }
    ~PerfectSpecular() {}

    RGB light_contribution() const override;
    Vector3 output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const override;
};
/*
struct PhongBRDF : BRDF {

    PhongBRDF(){};
    ~PhongBRDF(){};
};
*/

enum EVENT {
    REFLECTION,
    REFRACTION,
    REFLECTION,
    DIFFUSE,
    DEAD
};

EVENT randomEvent(const Shape &shape, const Point3 &position) {
    // Russian rulette

    // Calcular probabilidad de cada evento a partir de las probabilidades del objeto

    // Elegir número entre 0 - 1

    float random

        // Ver dónde ha caído el punto y devolver ese evento
        if (random)
}

Vector3 output_direction(EVENT event, const Vector &wi, const Vector3 &normal, const Point3 intersection_point) {
}