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
#include <iostream>
#include <memory>

#include "BRDF.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "shape.hpp"

RGB Camera::generateRay(Vector3 d, const std::vector<std::shared_ptr<Shape>> &shapes) const {

    RGB color(0, 0, 0);
    RGB alpha(1, 1, 1);
    float t = INFINITY;
    float shape_t = 0.0f;
    Vector3 normal;
    PerfectSpecular spec;
    std::shared_ptr<Shape> object;
    Point3 p;
    Point3 _o = o;

    d = camera2world(d);
    for (int i = 0; i < 200; i++) {
        t = INFINITY;
        shape_t = 0.0f;

        for (const std::shared_ptr<Shape> &s : shapes) {
            shape_t = s->intersection(_o, d);

            if (shape_t < t && shape_t > 0.0f) {

                t = shape_t;
                object = s;
            }
        }

        if (t != INFINITY && t > 0.0f) {

            p = o + d * t;
            normal = object->normal(p);

            if (object->brdf->type == EMISOR) {
                //std::cout << "Llegoo a luz" << std::endl;
                color = alpha * object->brdf->light_contribution();
                return color;
            } else if (object->brdf->type == LAMBERTIAN_DIFUSE) {

                d = object->brdf->output_direction(d, normal, p);
                _o = p;
                alpha = alpha * (object->brdf->light_contribution() * dot(d, normal));

            } else if (object->brdf->type == PERFECT_SPECULAR) {

                d = object->brdf->output_direction(-d, normal, p);
                _o = p;
                alpha = alpha * object->brdf->light_contribution();
            }
        }
    };

    return color;
};