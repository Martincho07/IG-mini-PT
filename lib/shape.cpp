/*********************************************************************************
 * Image
 *
 * File: shape.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "shape.hpp"

float Sphere::intersection(Point3 o, Vector3 d) const {
    float a = pow(modulus(d), 2.0f);
    float b = dot(d, o - center) * 2.0f;
    float c = pow(modulus(o - center), 2.0f) - pow(r, 2.0f);

    float delta = pow(b, 2) - 4.0f * a * c;
    // std::cout << a << " " << b << " " << c << std::endl;
    // std::cout << "Center: " << center << std::endl;
    // std::cout << "Delta: " << delta << std::endl;

    if (delta < 0) {
        return -1.0f;
    } else if (delta == 0) {
        return -b + sqrt(delta) / 2 * b;
    } else {
        // std::cout << "Mayor que 0" << std::endl;
        // std::cout << a << " " << b << " " << c << std::endl;
        return std::min(-b + sqrt(delta) / 2 * a,
                        -b - sqrt(delta) / 2 * a);
    }
}

float Plane::intersection(Point3 o, Vector3 d) const {
    float dot_d_n = dot(d, n);
    if (dot_d_n == 0) {
        return -1.0f;
    } else {
        return -((dot((Vector3)o, n) + c) / dot_d_n);
    }
};