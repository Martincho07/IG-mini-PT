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

Camera::RGB GenerateRay(const Vector3 &d, const std::vector<Shape> &shapes){

    RGB color;
    float t = INFINITY;
    float shape_t = 0.0f

    for (const Shape &s : shapes){

        shape_t = s.Intersection(Camera2World(o), Camera2World(d));
        if (shape_t < t && shape_t > 0.0f){

            color = s.color;
            t = shape_t;
        }

    }

    return color;

};