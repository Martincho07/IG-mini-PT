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

RGB Camera::generateRay(const Vector3 &d, const std::vector<std::shared_ptr<Shape>> &shapes) const {

    RGB color(255, 255, 255);
    float t = INFINITY;
    float shape_t = 0.0f;

    for (const std::shared_ptr<Shape> &s : shapes) {
        shape_t = s->intersection(o, camera2world(d));

        if (shape_t < t && shape_t > 0.0f) {

            color = s->color;
            t = shape_t;
        }
    }

    return color;
};