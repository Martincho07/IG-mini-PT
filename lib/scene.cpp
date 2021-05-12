/*********************************************************************************
 * Scene
 *
 * File: scene.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include <cfloat>

#include "random.hpp"
#include "scene.hpp"
#include "surface_interaction.hpp"

Scene::Scene() {
    background = RGB(0, 0, 0);
    ambient_ri = 1;
    total_power = 0;
}

Scene::Scene(RGB _background, float _ambient_ri) {
    background = _background;
    ambient_ri = _ambient_ri;
    total_power = 0;
}

void Scene::set_background(RGB _background) {
    background = _background;
}

RGB Scene::get_background() const {
    return background;
}

void Scene::add_shape(const std::shared_ptr<Shape> shape) {
    // Add a shape to the BVH

    // If the shape is a triangle mesh, add each triangle separately
    std::shared_ptr<TriangleMesh> tm = std::dynamic_pointer_cast<TriangleMesh>(shape);

    if (!(tm == nullptr)) {
        for (Triangle &t : tm->faces) {
            shapes.push_back(std::make_shared<Triangle>(t));
        }
    } else {
        shapes.push_back(shape);
    }
}

int Scene::get_num_shapes() const {
    return shapes.size();
}

void Scene::add_light(const std::shared_ptr<LightSource> light) {
    lights.push_back(light);
    total_power += max(light->power);
}

int Scene::get_num_lights() const {
    return lights.size();
}

std::shared_ptr<LightSource> Scene::get_light(int idx) const {
    return lights[idx];
}

float Scene::sample_light(std::shared_ptr<LightSource> &light) const {
    // Sample a random light using importance sampling based on its powers
    float rand = random_float(0, total_power);
    float acum = 0;
    for (std::shared_ptr<LightSource> l : lights) {
        if (acum > rand) {
            light = l;
            return max(l->power) / total_power;
        } else {
            acum += max(l->power);
        }
    }
    return 0;
}

bool Scene::first_intersection(const Ray &ray, SurfaceInteraction &si) const {
    return bvh.intersect(ray, si);
    // return shapes_first_intersection(shapes, ray, si);
}

void Scene::fix() {
    // Construct the BVH with the current shapes
    bvh = BVH(shapes, 0, shapes.size(), 10);
}
