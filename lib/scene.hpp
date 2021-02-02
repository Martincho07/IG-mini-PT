/*********************************************************************************
 * Scene
 *
 * File: scene.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

// #include <vector>

#include "BVH.hpp"

#include "light_source.hpp"
#include "shape.hpp"

#define AIR_N 1.000293f

struct LightSource;

class Scene {
    // Objects in the scene
    std::vector<std::shared_ptr<Shape>> shapes;

    // Light sources in the scene
    std::vector<std::shared_ptr<LightSource>> lights;
    // Sum of the power of all the light sources
    float total_power;

    // BVH for fast intersection with the objects in the scene
    BVH bvh;

    // Background
    RGB background;

    // Ambient refraction index
    float ambient_ri;

  public:
    Scene();

    Scene(RGB _background, float _ambient_ri = 1);

    void set_background(RGB _background);
    RGB get_background() const;

    // Add a shape
    void add_shape(const std::shared_ptr<Shape> shape);
    // Add triangle mesh
    // void add_shape(const std::shared_ptr<TriangleMesh> mesh);

    int get_num_shapes() const;

    // Add a light source
    void add_light(const std::shared_ptr<LightSource> light);

    // Get light
    int get_num_lights() const;
    std::shared_ptr<LightSource> get_light(int idx) const;

    // Sample a random light
    float sample_light(std::shared_ptr<LightSource> &light) const;

    // Return first object that intersects a ray
    bool first_intersection(const Ray &ray, SurfaceInteraction &si) const;

    // Create bounding boxes for the shapes and an array for light importance sampling
    void fix();
};
