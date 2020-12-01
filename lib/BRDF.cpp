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
#include "transform.hpp"
#include <cmath>
#include <iostream>
#include <random>

RGB LigthEmission::light_contribution() const {

    return ligth_power;
};

Vector3 LigthEmission::output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const {

    return Vector3(0, 0, 0);
};
RGB PerfectSpecular::light_contribution() const {

    return RGB(1.0f, 1.0f, 1.0f);
};

Vector3 PerfectSpecular::output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const {

    return wi + (normal * 2.0f * (dot(wi, normal)));
};

RGB LambertianDiffuse::light_contribution() const {

    // return kd;
    return kd / M_PI; // TODO: arreglar la intensidad de la luz
};

Vector3 LambertianDiffuse::output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const {

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

    std::random_device rd;                             // obtain a random number from hardware
    std::mt19937 gen(rd());                            // seed the generator
    std::uniform_int_distribution<> distr1(1, 157079); // define the range
    std::uniform_int_distribution<> distr2(1, 628318); // define the range

    float inclination = (float)distr1(gen) / 100000;
    float azimuth = (float)distr2(gen) / 100000;

    Vector3 output_point(0.0f, 1.0f, 0.0f);

    output_point = (rotationY(azimuth) * rotationZ(inclination))(output_point);

    return changeBasis(x, y, z, intersection_point)(output_point);
};
