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
enum BRDF_TYPE { LAMBERTIAN_DIFUSE,
                 PERFECT_SPECULAR,
                 PHONG_BRDF,
                 EMISOR };
struct BRDF {

    BRDF_TYPE type;
    BRDF(BRDF_TYPE _type) : type(_type){};
    virtual ~BRDF(){};

    virtual RGB light_contribution() const = 0;
    virtual Vector3 output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const = 0;
};

struct LigthEmision : BRDF {

    RGB ligth_power;

    LigthEmision() : BRDF(EMISOR){};
    LigthEmision(RGB _ligth_power) : ligth_power(_ligth_power), BRDF(EMISOR){};
    RGB light_contribution() const override;
    Vector3 output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const override;
};

struct LambertianDifuse : public BRDF {

    RGB kd;

    LambertianDifuse() : BRDF(LAMBERTIAN_DIFUSE){};
    LambertianDifuse(RGB _kd) : kd(_kd), BRDF(LAMBERTIAN_DIFUSE){};
    ~LambertianDifuse(){};

    RGB light_contribution() const override;
    Vector3 output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const override;
};

struct PerfectSpecular : public BRDF {

    PerfectSpecular() : BRDF(PERFECT_SPECULAR){};
    ~PerfectSpecular(){};

    RGB light_contribution() const override;
    Vector3 output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const override;
};
/*
struct PhongBRDF : BRDF {

    PhongBRDF(){};
    ~PhongBRDF(){};
};
*/