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

float Sphere::Intersection (Point3 o, Vector3 d) const{

    return 0.0f;

}

float Plane::Intersection (Point3 o, Vector3 d) const {

    float dot_d_n = dot(d,n);
    return (dot_d_n == 0) ? -1.0f : -(dot(o,n) + c ) / dot_d_n);

};