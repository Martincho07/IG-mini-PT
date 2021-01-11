/*********************************************************************************
 * Sample scenes
 *
 * File: sample_scenes.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "BRDF.hpp"
#include "camera.hpp"
#include "file.hpp"
#include "image.hpp"
#include "light_source.hpp"
#include "scene.hpp"
#include "shape.hpp"

#include <iostream>

/*
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
*/

void escena4(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 480;
    height = 480;

    // c = Camera(orig, left, up, front);
    // c = Camera(Point3(0, 0, -10), Vector3(3, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));
    c = Camera(30, Point3(0, 0, 0), 15, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.0f, 0.0f))));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.5f, 0.0f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.0f, 0.0f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.0f, 0.8f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(1.0f, 0, 0))));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, -1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(2, 0.8, 1)))));
    // scene.push_back(std::make_shared<Plane>(RGB(0, 255, 0), Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 1, 1)))));
    // scene.push_back(std::make_shared<Plane>(RGB(0, 0, 255), Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(1, 1, 0.8)))));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, -1, 0), 3, std::make_shared<LigthEmission>(LigthEmission(RGB(1.0f, 1.0f, 1.0f)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(0, 80, 255), Point3(0.8, 1, -5), 1, std::make_shared<LigthEmission>(LigthEmission(RGB(1, 1, 1)))));
    // scene.push_back(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LightPower>(LightPower(RGB(10000, 10000, 10000)))));
    // // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-3, -2, 0), Point3(3, -2, 3), std::make_shared<LigthEmission>(LigthEmission(RGB(1.0f, 1.0f, 1.0f)))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -2), Point3(2, 2.995, 3), std::make_shared<LightPower>(RGB(1000, 1000, 1000))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-1, 2.995, -5), Point3(1, 2.995, -2), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));

    // scene.push_back(std::make_shared<Triangle>(RGB(255, 0, 255), Point3(-3, 2, 0), Point3(3, 3, 8), Point3(3, -1, -1), std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0, 0.5)))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0, 2), 0.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(-1.5, -1.5, -2), 1.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));
    // scene.push_back(std::make_shared<Sphere>(RGB(0, 80, 255), Point3(0.8, -2.5, -5), 0.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1, -1.5, -1), 1, std::make_shared<PerfectSpecular>(0.5)));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 2), 1, std::make_shared<LambertianDiffuse>(RGB(0.8, 0.5, 0.1))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(-1.5, -1.5, 0), 1.5, std::make_shared<Phong>(Phong(RGB(0.7, 0.7, 0.1), RGB(0.2, 0.2, 0.1)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(-1.5, -1.5, 0), 1.5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 0.5, 0.5)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, -1), 1.5, std::make_shared<PerfectSpecular>(PerfectSpecular(RGB(0.8, 0.5, 0.5)))));
    scene.add_shape(std::make_shared<Sphere>(Point3(0.8, -2.5, -2), 0.5, std::make_shared<LambertianDiffuse>(RGB(0.5, 0, 0.5))));

    // scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 80, 255), Point3(-2.5, 2.5, -19.5), Point3(2.5, 2.5, 4.5), std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.0f, 0.0f, 0.8f)))));

    // std::shared_ptr<Sphere> sphere(new Sphere(RGB(255, 102, 254), Point3(0, 0, 5), 0.5f));
    // scene.push_back(sphere);

    // std::shared_ptr<Sphere> sphere2(new Sphere(RGB(0, 255, 0), Point3(0, 0, 7.5), 2.0f));
    // scene.push_back(sphere2);

    // std::shared_ptr<Sphere> sphere3(new Sphere(RGB(0, 0, 255), Point3(4, 10, 7.5), 2.0f));
    // scene.push_back(sphere3);
    scene.fix();
}

void pruebaGeometria(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 1200;
    height = 1000;

    // c = Camera(orig, left, up, front);
    // c = Camera(Point3(0, 0, -10), Vector3(3, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));
    c = Camera(30, Point3(0, 0, 0), -15, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.0f, 0.0f))));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.5f, 0.0f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.0f, 0.0f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.0f, 0.8f, 0.8f))));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(1.0f, 0, 0)))));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, -1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(2, 0.8, 1)))));
    // scene.push_back(std::make_shared<Plane>(RGB(0, 255, 0), Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 1, 1)))));
    // scene.push_back(std::make_shared<Plane>(RGB(0, 0, 255), Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(1, 1, 0.8)))));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, -1, 0), 3, std::make_shared<LigthEmission>(LigthEmission(RGB(1.0f, 1.0f, 1.0f)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(0, 80, 255), Point3(0.8, 1, -5), 1, std::make_shared<LigthEmission>(LigthEmission(RGB(1, 1, 1)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LightPower>(RGB(10000, 10000, 10000))));
    // // // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-3, -2, 0), Point3(3, -2, 3), std::make_shared<LigthEmission>(LigthEmission(RGB(1.0f, 1.0f, 1.0f)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-1, 2.995, -5), Point3(1, 2.995, -2), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));

    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-2, 2.995, -2), Point3(2, 2.995, 3), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-2, 2.995, -2), Point3(2, 2.995, 3), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));

    // scene.push_back(std::make_shared<Triangle>(RGB(255, 0, 255), Point3(-3, 2, 0), Point3(3, 3, 8), Point3(3, -1, -1), std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0, 0.5)))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0, 2), 0.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(-1.5, -1.5, -2), 1.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));
    // scene.push_back(std::make_shared<Sphere>(RGB(0, 80, 255), Point3(0.8, -2.5, -5), 0.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1, -1.5, 2), 1, std::make_shared<PerfectSpecular>(0.5f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, -1), 1, std::make_shared<LambertianDiffuse>(RGB(0.8, 0.5, 0.1))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(-1.5, -1.5, 0), 1.5, std::make_shared<Phong>(Phong(RGB(0.7, 0.7, 0.1), RGB(0.2, 0.2, 0.1)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(-1.5, -1.5, 0), 1.5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 0.5, 0.5)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, -1), 1.5, std::make_shared<PerfectSpecular>(PerfectSpecular(RGB(0.8, 0.5, 0.5)))));
    scene.add_shape(std::make_shared<Sphere>(Point3(0.8, -2.5, -2), 0.5, std::make_shared<LambertianDiffuse>(RGB(0.5, 0, 0.5))));

    // scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 80, 255), Point3(-2.5, 2.5, -19.5), Point3(2.5, 2.5, 4.5), std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.0f, 0.0f, 0.8f)))));

    // std::shared_ptr<Sphere> sphere(new Sphere(RGB(255, 102, 254), Point3(0, 0, 5), 0.5f));
    // scene.push_back(sphere);

    // std::shared_ptr<Sphere> sphere2(new Sphere(RGB(0, 255, 0), Point3(0, 0, 7.5), 2.0f));
    // scene.push_back(sphere2);

    // std::shared_ptr<Sphere> sphere3(new Sphere(RGB(0, 0, 255), Point3(4, 10, 7.5), 2.0f));

    // scene.push_back(sphere3);
    scene.fix();
}

void escenaPhong(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 480;
    height = 480;

    c = Camera(30, Point3(0, 0, 0), -15, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.0f, 0.0f)))));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.0f, 0.0f, 0.8f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.0f, 0.8f, 0.8f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(1.0f, 0, 0)))));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, -1, 0), 3, std::make_shared<LightEmission>(LightEmission(RGB(10000, 10000, 10000)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -5), Point3(2, 2.995, 5), std::make_shared<LightPower>(LightPower(RGB(1.0f, 1.0f, 1.0f)))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<Phong>(Phong(RGB(0.5, 0.5, 0.5), RGB(0.4, 0.4, 0.4)))));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, -1.5, 0), 1.5, std::make_shared<Phong>(Phong(RGB(0.5, 0.5, 0.5), 0.2, 50.0f))));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, -1.5, 0), 1.5, std::make_shared<PerfectSpecular>(PerfectSpecular(0.5f))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(2, -2, -3), 1, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 0.5, 0.5)))));
    scene.fix();
}

void escenaDielectrico(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 400;
    height = 400;
    Image texture = readPPM("../textures/world.ppm");
    Image texture2 = readPPM("../textures/world.ppm");

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture)))));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.7f, 0.45f, 0.65f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.44f, 0.86f, 0.86f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.3f, 0.3f, 0.3f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.3f, 0.3f, 0.3))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 20, std::make_shared<LambertianDiffuse>(RGB(0.2f, 0.2f, 0.2f))));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LightPower>(RGB(10000, 10000, 10000))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -5), Point3(2, 2.995, 5), std::make_shared<LightPower>(RGB(1.0f, 1.0f, 1.0f))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(2.8, 2.5, 1), Point3(2.8, -1, -7), std::make_shared<Texture>(TextureMappingUV(texture2))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<Phong>(Phong(RGB(0.5, 0.5, 0.5), RGB(0.4, 0.4, 0.4)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<Phong>(Phong(RGB(0.5, 0.5, 0.5), RGB(0.2, 0.2, 0.2)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<PerfectSpecular>(PerfectSpecular(RGB(0.5, 0.5, 0.5)))));
    // LambertianDiffuse(RGB(0.7f, 0.0f, 0.6f)
    // Plastic(RGB(0.7f, 0.0f, 0.6f), 0.1f)
    // PerfectSpecular(0.95);
    // Phong(RGB(0.0f, 0.4f, 0.2f), 0.5f, 10.0f)
    // Dielectric(1.52f) cristal
    // Dielectric(1.31f) hielo
    // Dielectric(2.42f) diamante
    // Dielectric(1.47) aceite
    scene.add_shape(std::make_shared<Sphere>(Point3(0, -1.5, 0), 1.5, std::make_shared<Texture>(TextureMappingUV(texture))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<Dielectric>(Dielectric(RGB(0.0, 0.0, 0.0), RGB(0.9, 0.9, 0.9)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0, 0), 1.5, std::make_shared<Dielectric>(Dielectric(RGB(0.0, 0.0, 0.0), RGB(0.5, 0.5, 0.5)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0.5, 0), 1, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.9, 0.9, 0.9)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<Dielectric>(Dielectric(RGB(0.0, 0.0, 0.0), RGB(0.9, 0.9, 0.9)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-0.25, -1.995, 0), Point3(0.25, 1.995, 0), std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.1, 0.8, 0.1)))));

    //scene.push_back(std::make_shared<Sphere>(Point3(0, -1.5, -4), 1.5, std::make_shared<Dielectric>(Dielectric(1.52f))));
    //scene.push_back(std::make_shared<Sphere>(Point3(1.5, -2, 2), 1, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 0.5, 0.5)))));
    scene.fix();
}

void escenaConejo(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 480;
    height = 480;

    c = Camera(30, Point3(0, 0, 0), 15, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), -3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.0f, 0.0f))));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.5f, 0.0f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.0f, 0.0f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.0f, 0.8f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(1.0f, 0, 0))));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, -1, 0), 3, std::make_shared<LightEmission>(LightEmission(RGB(255, 255, 255)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -5), Point3(2, 2.995, 5), std::make_shared<LightPower>(RGB(1000, 1000, 1000))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.9, 0.9, 0.9)))));
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res4.ply");
    // // std::vector<Triangle> triangle_mesh = readPLY("../models/airplane.ply");
    // // scene.push_back(std::make_shared<TriangleMesh>(RGB(0, 255, 255), triangle_mesh, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 0.8, 0.8))), Point3(1, -3, 0), 18));
    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<Plastic>(Plastic(RGB(0.8f, 0.0f, 0.6f), 0.01f)), Point3(0, -1.5, 0), 25);
    // for (Triangle &f : tm.faces) {
    //     scene.push_back(std::make_shared<Triangle>(f));
    // }

    scene.add_shape(std::make_shared<Sphere>(Point3(0, 0, 0), 1, std::make_shared<LambertianDiffuse>(RGB(0.8, 0.5, 0.5))));
    scene.fix();
}

void escenaBVH(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 400;
    height = 400;

    // c = Camera(orig, left, up, front);
    // c = Camera(Point3(0, 0, -10), Vector3(3, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));
    c = Camera(30, Point3(0, 0, 0), 15, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    RGB white(0.85, 0.85, 0.85);
    RGB red(0.85, 0.2, 0.2);
    RGB green(0.2, 0.85, 0.2);

// #define INFINITOS
#ifdef INFINITOS
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.1f, 0.1f))));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.5f, 0.1f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1f, 0.1f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1f, 0.8f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(8.0f, 0.4, 0.2))));

#else
    // techo
    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, -3), Point3(-3, 3, 3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, 3), Point3(-3, 3, -3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, 3, -3), Point3(-3, 3, -3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -3), Point3(3, 3, 3), Point3(-3, 3, -3), std::make_shared<LambertianDiffuse>(white)));

    // suelo
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -3), Point3(-3, -3, 3), Point3(3, -3, 3), std::make_shared<LambertianDiffuse>(white)));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, 3), Point3(3, -3, -3), Point3(-3, -3, -3), std::make_shared<LambertianDiffuse>(white)));

    // pared fondo
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, 3), Point3(-3, 3, 3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(white)));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, -3, 3), Point3(-3, -3, 3), std::make_shared<LambertianDiffuse>(white)));

    // pared derecha
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, -3), Point3(3, 3, -3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -3), Point3(3, -3, -3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(green)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, -3, 3), Point3(3, -3, -3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, 3), Point3(3, 3, 3), Point3(3, -3, -3), std::make_shared<LambertianDiffuse>(green)));

    // pared izquierda
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -3), Point3(-3, 3, -3), Point3(-3, 3, 3), std::make_shared<LambertianDiffuse>(red)));
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, 3), Point3(-3, -3, 3), Point3(-3, -3, -3), std::make_shared<LambertianDiffuse>(red)));

#endif

    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 0, 0), RGB(1, 1, 1)));
    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(-2.9, -2.9, 0), RGB(1, 1, 1)));
    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(2.5, 2.5, 0), RGB(1, 1, 1)));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.4, 0), RGB(1, 1, 1)));

    // Luz cuadrilatero
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -2), Point3(2, 2.995, 3), std::make_shared<LightPower>(RGB(1, 1, 1))));

    // // Luz 4x4
    // scene.add_shape(std::make_shared<Triangle>(Point3(-2, 2.995, 2), Point3(-2, 2.995, -2), Point3(2, 2.995, 2), std::make_shared<LightPower>(RGB(1, 1, 1))));
    // scene.add_shape(std::make_shared<Triangle>(Point3(2, 2.995, -2), Point3(2, 2.995, 2), Point3(-2, 2.995, -2), std::make_shared<LightPower>(RGB(1, 1, 1))));

    // // Luz 2x2
    // scene.add_shape(std::make_shared<Triangle>(Point3(-1, 2.995, 1), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightPower>(RGB(5, 5, 5))));
    // scene.add_shape(std::make_shared<Triangle>(Point3(1, 2.995, -1), Point3(1, 2.995, 1), Point3(-1, 2.995, -1), std::make_shared<LightPower>(RGB(5, 5, 5))));

    // scene.add_shape(std::make_shared<Triangle>(Point3(-4, 1, 0), Point3(-4, 0, 0), Point3(4, 0, 0), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));

    // scene.add_shape(std::make_shared<Sphere>(Point3(-1, -1.5, -1), 1, std::make_shared<PerfectSpecular>(0.5)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 2), 1, std::make_shared<LambertianDiffuse>(RGB(0.8, 0.5, 0.1))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0.8, -2.5, -2), 0.5, std::make_shared<LambertianDiffuse>(RGB(0.5, 0, 0.5))));

    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, -2.5, 2.5), Point3(3, -2.5, 2.5), Point3(3, 1, 2.5), std::make_shared<LambertianDiffuse>(green)));

    scene.add_shape(std::make_shared<Sphere>(Point3(0, -2, 0), 1, std::make_shared<Dielectric>(1.5)));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, -1, 0), 1, std::make_shared<Dielectric>(1.5)));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, 0, 0), 1, std::make_shared<Dielectric>(1.5)));

    // scene.add_shape(std::make_shared<Sphere>(Point3(0.8, -2.5, -2), 0.5, std::make_shared<Dielectric>(1.5)));

    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res4.ply");
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res3.ply");

    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<Plastic>(RGB(0.8f, 0.0f, 0.6f), 0.01f), Point3(0, -1.5, 0), 25);
    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<PerfectSpecular>(0.8f), Point3(0, -1.5, 0), 25);
    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<Dielectric>(1.5), Point3(0, -1.5, 0), 25);
    // scene.add_shape(std::make_shared<TriangleMesh>(tm));

    scene.fix();
}

/*
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
    c = Camera(Point3(896, 595, -200), Vector3(2000, 0, 0), Vector3(0, 2000, 0), Vector3(0, 0, 200));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 1000));
    scene.push_back(std::make_shared<Triangle>(RGB(0, 255, 0), Point3(896.994, 595.49, -17.7412), Point3(865.796997, 595.489990, -17.225300), Point3(865.796997, 655.489990, -17.225300)));
    //scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 0), Point3(1033.3, 1255.91, 162.47), Point3(975.054, 1241.46, 158.236), Point3(976.963, 1232.69, 159.918)));

    std::vector<Triangle> triangle_mesh = readPLY("../models/airplane.ply");
    scene.push_back(std::make_shared<TriangleMesh>(RGB(0, 255, 255), triangle_mesh));

    std::cout << "Tamanyo de la escena: " << scene.size() << std::endl;
}

void escenaCara(std::vector<std::shared_ptr<Shape>> &scene) {
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(-1, 0, 0), 8));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 172, 0), Point3(8, 2, 0), 1.0f));
    scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 255, 0), Point3(7, 6, -3), Point3(7, 8, -1)));
    scene.push_back(std::make_shared<Triangle>(RGB(255, 255, 255), Point3(7, 8, 3), Point3(7, 8, 1), Point3(7, 6, 3)));
}
*/
