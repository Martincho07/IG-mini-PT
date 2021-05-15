/*********************************************************************************
 * Integrator
 *
 * File: integrator.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "integrator.hpp"

#include "BRDF.hpp"

RGB PathTracingIntegrator::render(float x, float y, const Scene &scene) const {
    bool success = true;
    float distance;
    RGB texture_color;

    // Albedo after all the interactions
    RGB total_albedo(1, 1, 1);

    RGB point_light_contribution(0, 0, 0);

    SurfaceInteraction si;
    Ray ray = camera->calculate_ray(x, y);

    Vector3 wi;
    EVENT event;

    // Mientras que no se llegue a una luz de área o la ruleta diga evento DEAD
    while (success) {
        RGB albedo(1, 1, 1);
        if (scene.first_intersection(ray, si)) {
            event = si.shape->material->russian_roulette(si, -ray.d, wi, albedo);

            // Si es emisor se calcula la perdida de lus en el camino
            // y se retorna la intensidad de la luz
            if (event == EMISSION_EVENT) {
                return total_albedo * std::static_pointer_cast<LightPower>(si.shape->material)->light_power + point_light_contribution;

            } else if (event != DEAD_EVENT) {
                // En caso contrario se usa la ruleta rusa para determinar si
                // se sigue o no
                ray = Ray(si.position, wi);
                total_albedo = total_albedo * albedo;

                if (event == DIFFUSE_EVENT) {
                    for (int i = 0; i < scene.get_num_lights(); i++) {
                        std::shared_ptr<LightSource> light = scene.get_light(i);
                        if (light->is_visible(si.position)) {
                            point_light_contribution = point_light_contribution +
                                                       total_albedo * light->get_incoming_light(si.position) *
                                                           fabs(dot(si.normal, -light->get_incoming_direction(si.position)));
                        }
                    }
                }
            } else {
                success = false;
            }
        } else {
            success = false;
        }
    }

    if (max(point_light_contribution) > 0) {
        return point_light_contribution;
    } else {
        return scene.get_background();
    }
}

RGB RayTracingIntegrator::render(float x, float y, const Scene &scene) const {
    SurfaceInteraction si;
    Ray ray = camera->calculate_ray(x, y);

    bool terminado = false;

    RGB light(0, 0, 0);

    Vector3 wi;

    int iteraciones = 0;

    while (!terminado) {
        iteraciones += 1;
        if (iteraciones > 10) {
            terminado = true;
        }
        RGB albedo = RGB(1, 1, 1);
        if (scene.first_intersection(ray, si)) {
            if (si.shape->material->type == DIELECTRIC) {
                float n1 = AIR_N;
                float n2 = std::dynamic_pointer_cast<Dielectric>(si.shape->material)->n;
                if (!si.into) {
                    std::swap(n1, n2);
                }
                float coefks = fresnel_ks(-ray.d, si.normal, n1, n2);
                if (coefks == 1) {
                    wi = specular_reflection(-ray.d, si.normal);
                } else {
                    wi = refraction(-ray.d, si.normal, n1, n2);
                }
                ray = Ray(si.position, wi);
            } else if (si.shape->material->type == PERFECT_SPECULAR) {
                wi = specular_reflection(-ray.d, si.normal);
                ray = Ray(si.position, wi);
            } else {
                terminado = true;

                if (si.shape->material->type == DIFFUSE) {
                    albedo = std::dynamic_pointer_cast<LambertianDiffuse>(si.shape->material)->kd;
                } else if (si.shape->material->type == PHONG) {
                    albedo = std::dynamic_pointer_cast<Phong>(si.shape->material)->kd;
                } else if (si.shape->material->type == PLASTIC) {
                    albedo = std::dynamic_pointer_cast<Plastic>(si.shape->material)->kd;
                } else if (si.shape->material->type == EMISSOR) {
                    return std::dynamic_pointer_cast<LightPower>(si.shape->material)->light_power;
                }

                if (scene.get_num_lights() != 0) {
                    RGB contribution(0, 0, 0);
                    for (int i = 0; i < scene.get_num_lights(); i++) {
                        std::shared_ptr<LightSource> light = scene.get_light(i);
                        if (light->is_visible(si.position)) {
                            return contribution = contribution +
                                                  albedo * light->get_incoming_light(si.position) *
                                                      fabs(dot(si.normal, -light->get_incoming_direction(si.position)));
                        }
                    }
                    return contribution;
                } else {
                    return albedo;
                }
            }
        } else {
            terminado = true;
        }
    }

    return scene.get_background();
}

RGB NormalMapIntegrator::render(float x, float y, const Scene &scene) const {
    Ray ray = camera->calculate_ray(x, y);
    SurfaceInteraction si;

    if (scene.first_intersection(ray, si)) {

        // // Real normals
        // Vector3 n = si.into ? si.normal : -si.normal;

        Vector3 n = si.normal;

        // x -> more blue
        // y -> more green
        // z -> more red

        n = n * 0.5f;
        return RGB(0.5f + n.z, 0.5f + n.y, 0.5f + n.x);
    }

    return scene.get_background();
}
