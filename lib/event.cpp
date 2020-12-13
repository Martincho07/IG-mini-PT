/*********************************************************************************
 * Event
 *
 * File: event.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 1/12/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "event.hpp"
#include "BRDF.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "random.hpp"
#include <cmath>
#include <iostream>
#include <memory>

EVENT randomEvent(const MaterialProperty &material) {
    // Russian roulette

    // Elegir número entre 0 - 1
    float rand = random_float();

    if (material.type == PLASTIC) {
        //std::cout << "kd: " << material.max_kd << std::endl;
        // std::cout << "ks: " << material.max_ks << std::endl;
        //std::cout << "rand: " << rand << std::endl;
    }

    if (material.type == DIELECTRIC) {
        //std::cout << "kt: " << material.max_kt << std::endl;
        //std::cout << "ks: " << material.max_ks << std::endl;
    }

    // std::cout << rand << std::endl;

    // Ver dónde ha caído el punto y devolver ese evento
    if (rand < material.max_kd) {
        //if (material.type == PLASTIC)
        //std::cout << "*" << std::endl;
        return DIFFUSE_EVENT;
        std::cout << "por queee" << std::endl;
    } else if (rand < material.max_kd + material.max_ks) {
        // if (material.type == PLASTIC)
        //std::cout << "+" << std::endl;
        return SPECULAR_EVENT;
    } else if (rand < material.max_kd + material.max_ks + material.max_kt) {
        //std::cout << "refraccion" << std::endl;
        return REFRACTION_EVENT;
    } else {
        //if (material.type == PLASTIC)
        //std::cout << "&" << std::endl;
        return DEAD_EVENT;
    }

    std::cout << "por queee" << std::endl;
}

void RussianRoulette(const MaterialProperty &material, const Vector3 &normal, const Point3 &point, Vector3 &direction, RGB &contribution, bool &success) {

    success = true;
    int event;

    event = randomEvent(material);
    switch (event) {

    case DIFFUSE_EVENT:

        direction = diffuse_reflection(direction, normal, point);
        contribution = contribution * (material.kd / material.max_kd);
        //if (material.type == PLASTIC)

        //std::cout << "cont: " << contribution << std::endl;
        break;

    case SPECULAR_EVENT:

        if (dot(direction, normal) < 0.0f) {
            direction = specular_reflection(direction, normal);
        } else {
            //std::cout << "entro " << std::endl;
            //std::cout << "normal: " << normal << std::endl;
            //std::cout << "dir: " << direction << std::endl;
            direction = specular_reflection(direction, -normal);
        }

        if (material.type == PHONG) {

            Vector3 reflected_ray = direction;
            MaterialProperty phong = material;
            MaterialProperty *ptrPhong = &phong;
            float alpha = static_cast<Phong *>(ptrPhong)->get_alpha();
            //std::cout << "alpha: " << alpha << std::endl;

            direction = phong_reflection(direction, normal, point, alpha);
            if (dot(direction, normal) < 0.0f) {
                success = false;
                return;
            }

            float cosTh = dot(reflected_ray, direction);
            RGB ant = contribution;

            contribution = contribution * ((material.ks * (((alpha + 2.0f) / 2.0f * (float)M_PI) * pow(abs(cosTh), alpha))) / material.max_ks);

            if (isinf(max(contribution))) {
                std::cout << "antes: " << ant << std::endl;
                std::cout << "mult: " << ((material.ks * (((alpha + 2.0f) / 2.0f * (float)M_PI) * pow(abs(cosTh), alpha))) / material.max_ks) << std::endl;
            }

        } else {

            contribution = contribution * (material.ks / material.max_ks);
        }

        //if (material.type == PLASTIC)
        //std::cout << "tupla especular: " << material.ks / material.max_ks << std::endl;

        break;

    case REFRACTION_EVENT:
        //std::cout << "F" << std::endl;
        if (dot(direction, normal) < 0.0f)

            direction = refraction(direction, normal, AIR_N, material.n, success);
        else
            direction = refraction(direction, -normal, material.n, AIR_N, success);

        if (!success)
            return;
        contribution = contribution * (material.kt / material.max_kt);

        break;

    default:
        success = false;
        break;
    }
    //std::cout << "evento: " << event << std::endl;
};

/*
Vector3 output

    Vector3
    output_direction(EVENT event, const Vector &wi, const Vector3 &normal, const Point3 intersection_point) {
}
*/