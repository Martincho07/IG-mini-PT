/*********************************************************************************
 * Main
 *
 * File: main.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 22/10/2020
 * Coms: Informática Gráfica, curso 2020-2021
 **********************************************************************************/

#include <iostream>

#include "coordinate.hpp"
#include "geometry.hpp"
#include "transform.hpp"

int main()
{
    HCoord a = direction(1, 2, 3);
    HCoord b = point(2, 3, 4);
    HCoord c = a + b;

    Vector3 v = Vector3(1, 2, 3);
    Point3 b = Point3(2, 3, 4);

    Transform t1;
    t1 = identity();
    Transform t2 = translation(v);
    t1 = t1 * t2;
    v = t1(v);
    v = identity()(v);

    Matrix4x4 m1;
    m1 = Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Matrix4x4 m2 = Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    m1 = m1 * m2;

    // Comprobación de que están definidas todas las operaciones con vectores y puntos
    Vector3 d;
    Point3 p;
    float s;

    s = dot(d, d);
    p = p + d;
    d = d + d;
    d = d * s;
    d = cross(d, d);
    d = p - p;
    d = d - d;
    d = d / s;

    // Operaciones sin significado
    p = p + p;
    p = p * s;
    p = p / s;
    p = d - p;
}
