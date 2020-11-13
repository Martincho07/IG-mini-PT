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

#include <cassert>
#include <iostream>
#include <memory>
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
    c = Camera(Point3(0, 0, -20), Vector3(3, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));

    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), -5));
    scene.push_back(std::make_shared<Plane>(RGB(0, 255, 0), Vector3(1, 0, 0), -3));
    scene.push_back(std::make_shared<Plane>(RGB(0, 0, 255), Vector3(1, 0, 0), 3));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, 1, 0), 3));
    scene.push_back(std::make_shared<Plane>(RGB(0, 255, 255), Vector3(0, 1, 0), -3));

    scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0, 2), 0.5f));
    scene.push_back(std::make_shared<Sphere>(RGB(0, 80, 255), Point3(0.8, -2.5, -5), 0.5f));

    // std::shared_ptr<Sphere> sphere(new Sphere(RGB(255, 102, 254), Point3(0, 0, 5), 0.5f));
    // scene.push_back(sphere);

    // std::shared_ptr<Sphere> sphere2(new Sphere(RGB(0, 255, 0), Point3(0, 0, 7.5), 2.0f));
    // scene.push_back(sphere2);

    // std::shared_ptr<Sphere> sphere3(new Sphere(RGB(0, 0, 255), Point3(4, 10, 7.5), 2.0f));
    // scene.push_back(sphere3);
}

void escenaMartins(Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
    // Camera l u f
    Point3 o = Point3(2, 6, 0);
    Vector3 r = Vector3(0, 0, 1);
    Vector3 u = Vector3(0, 1, 0);
    Vector3 f = Vector3(1, 0, 0);
    c = Camera(o, r, u, f);

    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
}

void escenaPLY(Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
    c = Camera(Point3(800, 700, -20), Vector3(100, 0, 0), Vector3(0, 100, 0), Vector3(0, 0, 10));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 1000));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 0), Point3(750, 750, 0), Point3(850, 750, 0), Point3(850, 650, 0)));

    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 0), Point3(850, 750, 0), Point3(850, 750, 0), Point3(850, 650, 0)));

    // scene.push_back(std::make_shared<TriangleMesh>(RGB(255, 255, 255), readPLY("models/airplane.ply")));
}

void escenaPLY2(Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
    c = Camera(Point3(896, 595, -200), Vector3(2000, 0, 0), Vector3(0, 2000, 0), Vector3(0, 0, 200));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 1000));
    scene.push_back(std::make_shared<Triangle>(RGB(0, 255, 0), Point3(896.994, 595.49, -17.7412), Point3(865.796997, 595.489990, -17.225300), Point3(865.796997, 655.489990, -17.225300)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 0), Point3(1033.3, 1255.91, 162.47), Point3(975.054, 1241.46, 158.236), Point3(976.963, 1232.69, 159.918)));

    scene.push_back(std::make_shared<TriangleMesh>(RGB(0, 255, 255), readPLY("models/airplane.ply")));
}

int main(int argc, char **argv) {

    int width = 1000;
    int height = 1000;

    float mod_u = 1;
    float mod_r = 1;

    std::cout << "Relacion modulos: " << mod_r / mod_u << std::endl;
    std::cout << "Relacion pixeles: " << (float)width / (float)height << std::endl;
    assert((mod_r / mod_u) == (float)width / (float)height);

    float acum_width = -mod_r + (mod_r / width);
    float acum_height = mod_u - (mod_u / height);

    std::vector<std::shared_ptr<Shape>> scene;
    Camera c;
    escenaPLY2(c, scene);

    Image image;

    image.width = width;
    image.height = height;

    for (int y = 0.0f; y < height; y++) {
        for (int x = 0.0f; x < width; x++) {

            image.v.push_back(c.generateRay(normalize(Vector3(acum_width, acum_height, 1.0f)), scene));
            acum_width += 2.0f / width;
        }
        acum_width = -mod_r + (mod_r / width);
        acum_height -= (2.0f * mod_u) / height;
    }

    writePPM(image, "images/salida.ppm", 255, 255);
    writeHDR(image, "images/salida.hdr");
};
