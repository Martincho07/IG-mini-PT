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

#include <memory.h>
#include <vector>

void carita(Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
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

    // Camera l u f
    c = Camera(Point3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
}

void escena1(Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
    // Camera l u f
    c = Camera(Point3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

    std::shared_ptr<Plane> plane(new Plane(RGB(255, 0, 0), Vector3(0.0f, 0.0f, 1.0f), -2.0f));
    scene.push_back(plane);
    std::shared_ptr<Plane> plane2(new Plane(RGB(50, 70, 0), Vector3(0.0f, -1.0f, 1.0f), -2.0f));
    scene.push_back(plane2);

    std::shared_ptr<Sphere> sphere(new Sphere(RGB(255.0f, 102.0f, 254.0f), Point3(0, 0, 1), 0.5f));
    scene.push_back(sphere);
}

void escena2(Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
    // Camera l u f
    c = Camera(Point3(0.2f, 0.3f, 0.3f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

    std::shared_ptr<Plane> plane(new Plane(RGB(255, 0, 0), Vector3(1.0f, 0.0f, 0.0f), -2.0f));
    scene.push_back(plane);
    std::shared_ptr<Plane> plane2(new Plane(RGB(50, 70, 0), Vector3(1.0f, -1.0f, 0.0f), -2.0f));
    scene.push_back(plane2);

    std::shared_ptr<Sphere> sphere(new Sphere(RGB(255.0f, 102.0f, 254.0f), Point3(1, 0, 0), 0.5f));
    scene.push_back(sphere);
}

void escena3(Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
    // 3D origin, target point and 'up' vector + field of view

    // Camera l u f
    // Point3 target = Point3(0, 0, 1);
    // Vector3 up = Vector3(0, 1, 0);
    // Vector3 front = Vector3(0, 0, 1);
    // Vector3 left = cross(up, front);
    // std::cout << left << std::endl;
    // std::cout << up << std::endl;
    // std::cout << front << std::endl;

    // Point3 orig = target - front;

    Point3 target = Point3(0, 0, 0);
    Point3 orig = Point3(0, 0, -8);

    Vector3 front = target - orig;
    Vector3 up = Vector3(0, 1, 0);
    Vector3 left = normalize(cross(up, front)); // esto abrá que multiplicarlo por width / height

    std::cout << "left: " << left << std::endl;
    std::cout << "up: " << up << std::endl;
    std::cout << "front: " << front << std::endl;
    std::cout << "orig: " << orig << std::endl;

    // c = Camera(orig, left, up, front);
    c = Camera(Point3(0, 0, 0), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 2));

    std::shared_ptr<Plane> plane(new Plane(RGB(255, 0, 0), Vector3(0, 0, 1), -20));
    scene.push_back(plane);
    // std::shared_ptr<Plane> plane2(new Plane(RGB(50, 70, 0), Vector3(0.0f, -1.0f, 1.0f), -20.0f));
    // scene.push_back(plane2);

    std::shared_ptr<Sphere> sphere(new Sphere(RGB(255, 102, 254), Point3(0, 0, 5), 0.5f));
    scene.push_back(sphere);

    std::shared_ptr<Sphere> sphere2(new Sphere(RGB(0, 255, 0), Point3(0, 0, 7.5), 2.0f));
    scene.push_back(sphere2);

    std::shared_ptr<Sphere> sphere3(new Sphere(RGB(0, 0, 255), Point3(4, 10, 7.5), 2.0f));
    scene.push_back(sphere3);
}

void escena4(Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
    // Camera l u f

    // c = Camera(orig, left, up, front);
    c = Camera(Point3(0, 0, -10), Vector3(2, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));

    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), -5));
    scene.push_back(std::make_shared<Plane>(RGB(0, 255, 0), Vector3(1, 0, 0), -3));
    scene.push_back(std::make_shared<Plane>(RGB(0, 0, 255), Vector3(1, 0, 0), 3));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, 1, 0), 3));
    scene.push_back(std::make_shared<Plane>(RGB(0, 255, 255), Vector3(0, 1, 0), -3));

    scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0, 2), 0.5f));
    scene.push_back(std::make_shared<Sphere>(RGB(70, 10, 0), Point3(0.8, -2.0, 3.4), 0.5f));

    // std::shared_ptr<Sphere> sphere(new Sphere(RGB(255, 102, 254), Point3(0, 0, 5), 0.5f));
    // scene.push_back(sphere);

    // std::shared_ptr<Sphere> sphere2(new Sphere(RGB(0, 255, 0), Point3(0, 0, 7.5), 2.0f));
    // scene.push_back(sphere2);

    // std::shared_ptr<Sphere> sphere3(new Sphere(RGB(0, 0, 255), Point3(4, 10, 7.5), 2.0f));
    // scene.push_back(sphere3);
}

int main(int argc, char **argv) {

    int width = 200;
    int height = 200;

    float acum_width = -1.0f + (1.0f / width);
    float acum_height = 1.0f - (1.0f / height);

    std::vector<std::shared_ptr<Shape>> scene;
    Camera c;
    escena4(c, scene);

    Image image;

    image.width = width;
    image.height = height;

    // Camera o l u f
    Camera c = Camera(Point3(0.0f, .0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

    for (int y = 0.0f; y < height; y++) {
        for (int x = 0.0f; x < width; x++) {
            // std::cout << "hola: " << acum_width << " " << acum_height << std::endl;
            image.v.push_back(c.generateRay(normalize(Vector3(acum_width, acum_height, 1.0f)), scene));
            acum_width += 2.0f / width;
        }
        acum_width = -1.0f + (1.0f / width);
        acum_height -= 2.0f / height;
    }

    // image.applyToneMappingOperator(Equalize(max(image)));
    writePPM(image, "salida.ppm", 255, 255);
    writeHDR(image, "salida.hdr");
};
