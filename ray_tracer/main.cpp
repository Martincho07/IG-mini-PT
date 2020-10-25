/*********************************************************************************
 * main
 *
 * File: ray_tracer.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "camera.hpp"
#include "color.hpp"
#include "file.hpp"
#include "geometry.hpp"
#include "image.hpp"
#include "shape.hpp"
#include "tone_mapping.hpp"

#include <vector>

int main(int argc, char **argv) {

    int width = 1000;
    int height = 1000;

    float acum_width = -1.0f + (1.0f / width);
    float acum_height = 1.0f - (1.0f / height);

    std::vector<std::shared_ptr<Shape>> scene;

    std::shared_ptr<Plane> plane(new Plane(RGB(255, 0, 0), Vector3(-1.0f, 0.0f, 0.0f), 8.0f));
    scene.push_back(plane);
    std::shared_ptr<Plane> plane2(new Plane(RGB(50.0f, 70.0f, 255.0f), Vector3(-1.0f, 1.0f, 0.0f), 12.0f));
    scene.push_back(plane2);
    std::shared_ptr<Sphere> sphere(new Sphere(RGB(255.0f, 255.0f, 0.0f), Point3(3.0f, 0.0f, 0.0f), 2.0f));
    scene.push_back(sphere);
    std::shared_ptr<Sphere> sphere2(new Sphere(RGB(0.0f, 0.0f, 0.0f), Point3(1.2f, 0.25f, 0.25f), 0.2f));
    scene.push_back(sphere2);
    std::shared_ptr<Sphere> sphere3(new Sphere(RGB(0.0f, 0.0f, 0.0f), Point3(1.2f, 0.25f, -0.25f), 0.2f));
    scene.push_back(sphere3);
    std::shared_ptr<Sphere> sphere4(new Sphere(RGB(255.0f, 102.0f, 254.0f), Point3(1.4f, -0.40f, 0.0f), 0.2f));
    scene.push_back(sphere4);

    Image image;

    image.width = width;
    image.height = height;

    // Camera l u f
    Camera c = Camera(Point3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

    for (int y = 0.0f; y < height; y++) {
        for (int x = 0.0f; x < width; x++) {
            // std::cout << "hola: " << acum_width << " " << acum_height << std::endl;
            image.v.push_back(c.generateRay((Vector3(acum_width, acum_height, 1.0f)), scene));
            acum_width += 2.0f / width;
        }
        acum_width = -1.0f + (1.0f / width);
        acum_height -= 2.0f / height;
    }

    // image.applyToneMappingOperator(Clamp());
    writePPM(image, "salida.ppm", max(image), 255);
};