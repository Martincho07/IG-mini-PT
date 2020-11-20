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

RGB LigthEmision::light_contribution() const {

    return RGB(255.0f, 255.0f, 255.0f);
};

Vector3 LigthEmision::output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const {

    return Vector3(0, 0, 0);
};
RGB PerfectSpecular::light_contribution() const {

    return RGB(1.0f, 1.0f, 1.0f);
};

Vector3 PerfectSpecular::output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const {

    return wi + (normal * 2.0f * (dot(wi, normal)));
};

RGB LambertianDifuse::light_contribution() const {

    return kd / M_PI;
};

Vector3 LambertianDifuse::output_direction(const Vector3 &wi, const Vector3 &normal, const Point3 intersection_point) const {

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

    //std::cout << "x: " << x << std::endl;
    //std::cout << "y: " << y << std::endl;
    //std::cout << "z: " << z << std::endl;

    float inclination = (89.0f - 1.0f) * ((((float)rand_r(&seed)) / (float)RAND_MAX)) + 1.0f;
    float azimuth = (180.0f - 1.0f) * ((((float)rand_r(&seed)) / (float)RAND_MAX)) + 1.0f;

    //std::cout << "PI: " << M_PI << std::endl;
    //std::cout << "deeg In: " << inclination << std::endl;
    //std::cout << "deeg Az: " << azimuth << std::endl;

    inclination = (inclination * M_PI) / 180.0f;
    azimuth = (azimuth * M_PI) / 180.0f;

    //std::cout << "rad In: " << inclination << std::endl;
    //std::cout << "rad Az: " << azimuth << std::endl;

    Vector3 output_point(0.0f, 1.0f, 0.0f);

    output_point = (rotationY(azimuth) * rotationZ(inclination))(output_point);

    return changeBasis(x, y, z, intersection_point)(output_point);
};
