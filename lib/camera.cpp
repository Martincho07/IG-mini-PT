/*********************************************************************************
 * Image
 *
 * File: camera.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/
#include <cmath>

#include "camera.hpp"

RGB Camera::generateRay(const Vector3 &d, const std::vector<std::shared_ptr<Shape>> &shapes) {

    RGB color(255, 255, 255);
    float t = INFINITY;
    float shape_t = 0.0f;

    // std::cout << "rayo desde camera: " << d.x << " " << d.y << " " << d.z << std::endl;
    std::cout << "rayo desde camera: " << o << d << std::endl;
    // std::cout << "rayo en el mundo: " << camera2world(o) << camera2world(d) << std::endl;

    for (const std::shared_ptr<Shape> &s : shapes) {
        shape_t = s->intersection(camera2world(o), camera2world(d));
        // std::cout << shape_t << std::endl;
        if (shape_t < t && shape_t > 0.0f) {
            // std::cout << "me gusta" << std::endl;
            color = s->color;
            t = shape_t;
        }
    }

    // std::cout << "color: " << color << std::endl;
    return color;
};