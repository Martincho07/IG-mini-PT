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
    width = 1920;
    height = 1080;

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
    //scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -2), Point3(2, 2.995, 3), std::make_shared<LightPower>(RGB(1000, 1000, 1000))));
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
    width = 1920;
    height = 1080;

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
    width = 1920;
    height = 1080;

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
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(6, 2.995, -5), Point3(-6, 2.995, 10), Point3(-6, 2.995, -5), std::make_shared<LightPower>(RGB(1.0f, 1.0f, 1.0f))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<Phong>(Phong(RGB(0.5, 0.5, 0.5), RGB(0.4, 0.4, 0.4)))));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, -1.5, 0), 1.5, std::make_shared<Phong>(Phong(RGB(0.5, 0.5, 0.5), 0.2, 50.0f))));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, -1.5, 0), 1.5, std::make_shared<PerfectSpecular>(PerfectSpecular(0.5f))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(2, -2, -3), 1, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 0.5, 0.5)))));
    scene.fix();
}

void escenaDielectrico(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 1920;
    height = 1080;
    Image texture = readPPM("Texture.ppm");
    //Image texture2 = readPPM("Texture.ppm");

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 6, 0), Vector3(-6, 0, 0), Point3(3, -3, 3)));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.7f, 0.45f, 0.65f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.44f, 0.86f, 0.86f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.3f, 0.3f, 0.3f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.3f, 0.3f, 0.3))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 20, std::make_shared<LambertianDiffuse>(RGB(0.2f, 0.2f, 0.2f))));

    //scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LightPower>(RGB(10000, 10000, 10000))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));
    //scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -5), Point3(2, 2.995, 5), std::make_shared<LightPower>(RGB(1.0f, 1.0f, 1.0f))));
    //scene.add_shape(std::make_shared<Quadrilateral>(Point3(2.8, 2.5, 1), Point3(2.8, -1, -7), std::make_shared<Texture>(TextureMappingUV(texture))));

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

void escenaChula(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 1920;
    height = 1080;
    Image texture = readPPM("../textures/Amigos.ppm");
    Image texture2 = readPPM("../textures/Texture.ppm");
    Image texture3 = readPPM("../textures/salasAltas.ppm");

    //Image texture2 = readPPM("Texture.ppm");

    c = Camera(30.0f, Point3(0, -2, 0), 19.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 9, 0), Vector3(16, 0, 0), Point3(8, -6, 3)));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 8, std::make_shared<LambertianDiffuse>(RGB(0.7f, 0.45f, 0.65f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 8, std::make_shared<LambertianDiffuse>(RGB(0.44f, 0.86f, 0.86f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 6, std::make_shared<LambertianDiffuse>(RGB(0.3f, 0.3f, 0.3f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.3f, 0.3f, 0.3))));
    //scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 20, std::make_shared<LambertianDiffuse>(RGB(0.2f, 0.2f, 0.2f))));

    //scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LightPower>(RGB(10000, 10000, 10000))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightEmission>(LightEmission(RGB(1000, 1000, 1000)))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(6, 2.995, -5), Point3(-6, 2.995, 10), Point3(-6, 2.995, -5), std::make_shared<LightPower>(RGB(1.0f, 1.0f, 1.0f))));
    scene.add_shape(std::make_shared<Sphere>(Point3(-6.5, 1, -2), 1, std::make_shared<Texture>(TextureMappingUV(texture2))));
    scene.add_shape(std::make_shared<Sphere>(Point3(-6.5, -2, -2), 1, std::make_shared<Dielectric>(1.52f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(5, 1, -2), 1, std::make_shared<Plastic>(Plastic(RGB(0.7f, 0.0f, 0.6f), 0.1f))));
    scene.add_shape(std::make_shared<Sphere>(Point3(5, -1, 3), 0.75, std::make_shared<PerfectSpecular>(0.95)));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(7.5, 2.5, 3), Point3(7.5, -1.5, -2.5), Point3(7.5, 2.5, -2.5), std::make_shared<Texture>(TextureMappingUV(texture3))));
    std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_smooth.ply");

    TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<Dielectric>(1.52f), Point3(-5, -4.5, 3), 25);
    scene.add_shape(std::make_shared<TriangleMesh>(tm));
    TriangleMesh tm2 = TriangleMesh(triangle_mesh, std::make_shared<PerfectSpecular>(0.95f), Point3(5, -4.5, 3), 25);
    scene.add_shape(std::make_shared<TriangleMesh>(tm2));

    scene.fix();

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
    //scene.add_shape(std::make_shared<Sphere>(Point3(0, -1.5, 0), 1.5, std::make_shared<Texture>(TextureMappingUV(texture))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<Dielectric>(Dielectric(RGB(0.0, 0.0, 0.0), RGB(0.9, 0.9, 0.9)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0, 0), 1.5, std::make_shared<Dielectric>(Dielectric(RGB(0.0, 0.0, 0.0), RGB(0.5, 0.5, 0.5)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0.5, 0), 1, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.9, 0.9, 0.9)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, -1.5, 0), 1.5, std::make_shared<Dielectric>(Dielectric(RGB(0.0, 0.0, 0.0), RGB(0.9, 0.9, 0.9)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-0.25, -1.995, 0), Point3(0.25, 1.995, 0), std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.1, 0.8, 0.1)))));

    //scene.push_back(std::make_shared<Sphere>(Point3(0, -1.5, -4), 1.5, std::make_shared<Dielectric>(Dielectric(1.52f))));
    //scene.push_back(std::make_shared<Sphere>(Point3(1.5, -2, 2), 1, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 0.5, 0.5)))));
}

void escenaConejo(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 1920;
    height = 1080;

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
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(6, 2.995, -5), Point3(-6, 2.995, 10), Point3(-6, 2.995, -5), std::make_shared<LightPower>(RGB(1.0f, 1.0f, 1.0f))));

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
    width = 800;
    height = 800;

    // c = Camera(orig, left, up, front);
    // c = Camera(Point3(0, 0, -10), Vector3(3, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));
    c = Camera(30, Point3(0, 0, 0), 15, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    RGB white(0.85, 0.85, 0.85);
    RGB red(0.85, 0.2, 0.2);
    RGB green(0.2, 0.85, 0.2);
    RGB blue(0.2, 0.2, 0.85);

// #define INFINITOS
#ifdef INFINITOS
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.1f, 0.1f))));
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.5f, 0.0f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.5f, 0.1f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1f, 0.1f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1f, 0.8f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(8.0f, 0.4, 0.2))));

#else
    Image texture = readPPM("../textures/world.ppm");
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 1, 0), Vector3(1, 0, 0), Point3(8, -6, 3)));
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 9, 0), Vector3(16, 0, 0), Point3(8, -6, 3)));
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 1, 0), Vector3(1, 0, 0), Point3(3, 3, 3)));

    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 1, 0), Vector3(1, 0, 0), Point3(3, -3, 3)));
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 1, 0), Vector3(1, 0, 0), Point3(3, -3, -3)));
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 1, 0), Vector3(1, 0, 0), Point3(-3, -3, 3)));
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 1, 0), Vector3(1, 0, 0), Point3(3, -3, 3)));

    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 1, 0), Vector3(1, 0, 0), Point3(3, -3, 3)));

    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<LambertianDiffuse>(blue)));
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(blue)));

    /*
    // techo
    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, -3), Point3(-3, 3, 3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, 5), Point3(-3, 3, -3), Point3(3, 3, 5), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, 3, -3), Point3(-3, 3, -3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -3), Point3(3, 3, 5), Point3(-3, 3, -3), std::make_shared<LambertianDiffuse>(white)));

    // suelo
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -3), Point3(-3, -3, 5), Point3(3, -3, 5), std::make_shared<LambertianDiffuse>(white)));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, 5), Point3(3, -3, -3), Point3(-3, -3, -3), std::make_shared<LambertianDiffuse>(white)));

    // pared fondo
    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -3), Point3(-3, 3, -3), Point3(3, 3, -3), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -3), Point3(3, -3, -3), Point3(-3, -3, -3), std::make_shared<LambertianDiffuse>(white)));

    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, 3), Point3(-3, 3, 3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, -3, 3), Point3(-3, -3, 3), std::make_shared<LambertianDiffuse>(white)));

    // pared derecha
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, -3), Point3(3, 3, -3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -3), Point3(3, -3, -3), Point3(3, 3, 5), std::make_shared<LambertianDiffuse>(green)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, -3, 3), Point3(3, -3, -3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, 5), Point3(3, 3, 5), Point3(3, -3, -3), std::make_shared<LambertianDiffuse>(green)));

    // pared izquierda
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -3), Point3(-3, 3, -3), Point3(-3, 3, 5), std::make_shared<LambertianDiffuse>(red)));
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, 5), Point3(-3, -3, 5), Point3(-3, -3, -3), std::make_shared<LambertianDiffuse>(red)));
    */

    // techo
    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, -3), Point3(-3, 3, 3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, 3), Point3(-3, 3, -3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, 3, -3), Point3(-3, 3, -3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -3), Point3(3, 3, 3), Point3(-3, 3, -3), std::make_shared<LambertianDiffuse>(white)));

    // suelo
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -3), Point3(-3, -3, 3), Point3(3, -3, 3), std::make_shared<LambertianDiffuse>(white)));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, 3), Point3(3, -3, -3), Point3(-3, -3, -3), std::make_shared<LambertianDiffuse>(white)));

    // // pared fondo
    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -3), Point3(-3, 3, -3), Point3(3, 3, -3), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -3), Point3(3, -3, -3), Point3(-3, -3, -3), std::make_shared<LambertianDiffuse>(white)));

    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, 3), Point3(-3, 3, 3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, -3, 3), Point3(-3, -3, 3), std::make_shared<LambertianDiffuse>(white)));

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
    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(2.9, -2.9, 0), RGB(1, 1, 1)));
    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(2.5, 2.5, 0), RGB(1, 1, 1)));

    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.4, 0), RGB(5, 5, 5)));

    // Luz cuadrilatero
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -2), Point3(2, 2.995, 3), std::make_shared<LightPower>(RGB(1, 1, 1))));

    // // Luz 4x4
    // scene.add_shape(std::make_shared<Triangle>(Point3(-2, 2.995, 2), Point3(-2, 2.995, -2), Point3(2, 2.995, 2), std::make_shared<LightPower>(RGB(5, 5, 5))));
    // scene.add_shape(std::make_shared<Triangle>(Point3(2, 2.995, -2), Point3(2, 2.995, 2), Point3(-2, 2.995, -2), std::make_shared<LightPower>(RGB(5, 5, 5))));

    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -3), Point3(3, -3, -3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(green)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, -3, 3), Point3(3, -3, -3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, 3), Point3(3, 3, 3), Point3(3, -3, -3), std::make_shared<LambertianDiffuse>(green)));

    // Luz 4x4
    scene.add_shape(std::make_shared<Triangle>(Point3(2.995, 2, -2), Point3(2.995, -2, -2), Point3(2.995, 2, 2), std::make_shared<LightPower>(RGB(5, 5, 5))));
    scene.add_shape(std::make_shared<Triangle>(Point3(2.995, -2, 2), Point3(2.995, 2, 2), Point3(2.995, -2, -2), std::make_shared<LightPower>(RGB(5, 5, 5))));

    // // Luz 2x2
    // scene.add_shape(std::make_shared<Triangle>(Point3(-1, 2.995, 1), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightPower>(RGB(5, 5, 5))));
    // scene.add_shape(std::make_shared<Triangle>(Point3(1, 2.995, -1), Point3(1, 2.995, 1), Point3(-1, 2.995, -1), std::make_shared<LightPower>(RGB(5, 5, 5))));

    // scene.add_shape(std::make_shared<Triangle>(Point3(-4, 1, 0), Point3(-4, 0, 0), Point3(4, 0, 0), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));

    // scene.add_shape(std::make_shared<Sphere>(Point3(-1, -1.5, -1), 1, std::make_shared<PerfectSpecular>(0.5)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 2), 1, std::make_shared<LambertianDiffuse>(RGB(0.8, 0.5, 0.1))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0.8, -2.5, -2), 0.5, std::make_shared<LambertianDiffuse>(RGB(0.5, 0, 0.5))));

    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, -2.5, 2.5), Point3(3, -2.5, 2.5), Point3(3, 1, 2.5), std::make_shared<LambertianDiffuse>(green)));

    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 0, 0), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.5, 0.3))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 0, 0), 1, std::make_shared<PerfectSpecular>(0.8)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(-2, 2, 0), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.5, 0.3))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, -1, 0), 2, std::make_shared<Dielectric>(2.5)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, -2, 0), 1, std::make_shared<Dielectric>(1.5)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, -1, 0), 1, std::make_shared<Dielectric>(1.5)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(2, -2, 0), 1, std::make_shared<Dielectric>(1.5)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 0, 2), 1, std::make_shared<Plastic>(RGB(0.2, 0.3, 0.4), 0.1)));

    // scene.add_shape(std::make_shared<Sphere>(Point3(0.8, -2.5, -2), 0.5, std::make_shared<Dielectric>(1.5)));

    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res3_smooth.ply");
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res3.ply");
    std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_smooth.ply");
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper.ply");

    TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<Plastic>(RGB(0.5f, 0.2f, 0.4f), 0.2f), Point3(0, -1.5, 0), 25);
    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<PerfectSpecular>(0.8f), Point3(0, -1.5, 0), 25);
    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<Dielectric>(1.5), Point3(0, -1.5, 0), 25);
    scene.add_shape(std::make_shared<TriangleMesh>(tm));

    // std::vector<Triangle> teapot = readPLY("../models/teapot.ply");
    // std::vector<Triangle> teapot = readPLY("../models/teapot_smooth.ply");
    // std::vector<Triangle> teapot = readPLY("../models/teapot_smooth-girada.ply");

    // TriangleMesh tm = TriangleMesh(teapot, std::make_shared<PerfectSpecular>(0.8), Point3(0, -1.5, 0), 1);
    // TriangleMesh tm = TriangleMesh(teapot, std::make_shared<Dielectric>(1.5), Point3(0, -1.5, 0), 0.8);

    // scene.add_shape(std::make_shared<TriangleMesh>(tm));

    // std::vector<Triangle> dragon = readPLY("../models/dragon_vrip_res3.ply");
    // TriangleMesh tm = TriangleMesh(dragon, std::make_shared<PerfectSpecular>(0.8), Point3(0, -1.5, 0), 25);
    // TriangleMesh tm = TriangleMesh(dragon, std::make_shared<Dielectric>(1.5), Point3(0, -1.5, 0), 25);
    // scene.add_shape(std::make_shared<TriangleMesh>(tm));

    scene.fix();
}

void escenaDOF(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 800;
    height = 800;

    // c = Camera(orig, left, up, front);
    // c = Camera(Point3(0, 0, -18), Vector3(4, 0, 0), Vector3(0, 4, 0), Vector3(0, 0, 20));
    // c = Camera(Point3(0, 0, -18), Vector3(0.2, 0, 0), Vector3(0, 0.2, 0), Vector3(0, 0, 1));
    c = Camera(25, Point3(0, 0, 2), 20, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    RGB white(0.85, 0.85, 0.85);
    RGB red(0.85, 0.2, 0.2);
    RGB green(0.2, 0.85, 0.2);

// #define INFINITOS
#ifdef INFINITOS
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.1f, 0.1f))));
    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, 1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.5f, 0.1f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1f, 0.1f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1f, 0.8f, 0.8f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(8.0f, 0.4, 0.2))));

#else
    // Image texture = readPPM("../textures/world.ppm");
    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 9, 0), Vector3(16, 0, 0), Point3(8, -6, 3)));

    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 3, std::make_shared<LambertianDiffuse>(white)));

    // techo
    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, -3), Point3(-3, 3, 3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, 5), Point3(-3, 3, -5), Point3(3, 3, 5), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, 3, -3), Point3(-3, 3, -3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -5), Point3(3, 3, 5), Point3(-3, 3, -5), std::make_shared<LambertianDiffuse>(white)));

    // suelo
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -5), Point3(-3, -3, 5), Point3(3, -3, 5), std::make_shared<LambertianDiffuse>(white)));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, 5), Point3(3, -3, -5), Point3(-3, -3, -5), std::make_shared<LambertianDiffuse>(white)));

    // pared fondo
    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, 3), Point3(-3, 3, 3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(white)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, -3, 3), Point3(-3, -3, 3), std::make_shared<LambertianDiffuse>(white)));
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, 5), Point3(-3, 3, 5), Point3(3, 3, 5), std::make_shared<LambertianDiffuse>(white)));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 5), Point3(3, -3, 5), Point3(-3, -3, 5), std::make_shared<LambertianDiffuse>(white)));

    // pared derecha
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, -3), Point3(3, 3, -3), Point3(3, 3, 3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, -5), Point3(3, -3, -5), Point3(3, 3, 5), std::make_shared<LambertianDiffuse>(green)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(3, 3, 3), Point3(3, -3, 3), Point3(3, -3, -3), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));
    scene.add_shape(std::make_shared<Triangle>(Point3(3, -3, 5), Point3(3, 3, 5), Point3(3, -3, -5), std::make_shared<LambertianDiffuse>(green)));

    // pared izquierda
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, -3, -5), Point3(-3, 3, -5), Point3(-3, 3, 5), std::make_shared<LambertianDiffuse>(red)));
    scene.add_shape(std::make_shared<Triangle>(Point3(-3, 3, 5), Point3(-3, -3, 5), Point3(-3, -3, -5), std::make_shared<LambertianDiffuse>(red)));

#endif

    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 0, 0), RGB(1, 1, 1)));
    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(-2.9, -2.9, 0), RGB(1, 1, 1)));
    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(2.5, 2.5, 0), RGB(1, 1, 1)));

    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.4, 0), RGB(5, 5, 5)));

    // Luz cuadrilatero
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2, 2.995, -2), Point3(2, 2.995, 3), std::make_shared<LightPower>(RGB(1, 1, 1))));

    // Luz 4x4
    scene.add_shape(std::make_shared<Triangle>(Point3(-2, 2.995, 3), Point3(-2, 2.995, -1), Point3(2, 2.995, 3), std::make_shared<LightPower>(RGB(5, 5, 5))));
    scene.add_shape(std::make_shared<Triangle>(Point3(2, 2.995, -1), Point3(2, 2.995, 3), Point3(-2, 2.995, -1), std::make_shared<LightPower>(RGB(5, 5, 5))));

    // // Luz 2x2
    // scene.add_shape(std::make_shared<Triangle>(Point3(-1, 2.995, 1), Point3(-1, 2.995, -1), Point3(1, 2.995, 1), std::make_shared<LightPower>(RGB(5, 5, 5))));
    // scene.add_shape(std::make_shared<Triangle>(Point3(1, 2.995, -1), Point3(1, 2.995, 1), Point3(-1, 2.995, -1), std::make_shared<LightPower>(RGB(5, 5, 5))));

    // scene.add_shape(std::make_shared<Triangle>(Point3(-4, 1, 0), Point3(-4, 0, 0), Point3(4, 0, 0), std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.2))));

    // scene.add_shape(std::make_shared<Sphere>(Point3(-1, -1.5, -1), 1, std::make_shared<PerfectSpecular>(0.5)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 2), 1, std::make_shared<LambertianDiffuse>(RGB(0.8, 0.5, 0.1))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0.8, -2.5, -2), 0.5, std::make_shared<LambertianDiffuse>(RGB(0.5, 0, 0.5))));

    // scene.add_shape(std::make_shared<Triangle>(Point3(-3, -2.5, 2.5), Point3(3, -2.5, 2.5), Point3(3, 1, 2.5), std::make_shared<LambertianDiffuse>(green)));

    scene.add_shape(std::make_shared<Sphere>(Point3(0, -2, -1), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.5, 0.3))));
    scene.add_shape(std::make_shared<Sphere>(Point3(1, -2, 2), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.5, 0.3))));
    scene.add_shape(std::make_shared<Sphere>(Point3(-1, -2, 5), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.5, 0.3))));

    // scene.add_shape(std::make_shared<Sphere>(Point3(0.8, -2.5, -2), 0.5, std::make_shared<Dielectric>(1.5)));

    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res3_smooth.ply");
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res3.ply");
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_smooth.ply");
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper.ply");

    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<Plastic>(RGB(0.8f, 0.0f, 0.6f), 0.01f), Point3(0, -1.5, 0), 25);
    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<PerfectSpecular>(0.8f), Point3(0, -1.5, 0), 25);
    // TriangleMesh tm = TriangleMesh(triangle_mesh, std::make_shared<Dielectric>(1.5), Point3(0, -1.5, 0), 25);
    // scene.add_shape(std::make_shared<TriangleMesh>(tm));

    // std::vector<Triangle> teapot = readPLY("../models/teapot.ply");
    // std::vector<Triangle> teapot = readPLY("../models/teapot_smooth.ply");

    // TriangleMesh tm = TriangleMesh(teapot, std::make_shared<PerfectSpecular>(0.8), Point3(0, -1.5, 0), 1);
    // TriangleMesh tm = TriangleMesh(teapot, std::make_shared<Dielectric>(0.8), Point3(0, -1.5, 0), 1);

    // scene.add_shape(std::make_shared<TriangleMesh>(tm));

    // std::vector<Triangle> dragon = readPLY("../models/dragon_vrip_res3.ply");
    // TriangleMesh tm = TriangleMesh(dragon, std::make_shared<PerfectSpecular>(0.8), Point3(0, -1.5, 0), 25);
    // scene.add_shape(std::make_shared<TriangleMesh>(tm));

    scene.fix();
}

void cornellBox(int &width, int &height, Camera &c, Scene &scene) {
    // Camera l u f
    width = 400;
    height = 400;

    // c = Camera(orig, left, up, front);
    c = Camera(Point3(278, 273, -800), Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 2));
    // c = Camera(35, Point3(278, 273, -800), -800, (float)width / height);
    // c = Camera(Point3(278, 273, -800), Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));

    scene.set_background(RGB(0, 0, 0));

    // Difuse surfaces
    std::shared_ptr<LambertianDiffuse> white = std::make_shared<LambertianDiffuse>(RGB(0.8, 0.8, 0.8));
    std::shared_ptr<LambertianDiffuse> green = std::make_shared<LambertianDiffuse>(RGB(0.1, 0.8, 0.1));
    std::shared_ptr<LambertianDiffuse> red = std::make_shared<LambertianDiffuse>(RGB(0.8, 0.1, 0.1));

    // Floor
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(552.8, 0.0, 0.0), Point3(0.0, 0.0, 0.0), Point3(0.0, 0.0, 559.2), Point3(549.6, 0.0, 559.2), white));
    // Ceiling
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(556.0, 548.8, 0.0), Point3(556.0, 548.8, 559.2), Point3(0.0, 548.8, 559.2), Point3(0.0, 548.8, 0.0), white));
    // Back wall
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(0.0, 0.0, 559.2), Point3(0.0, 548.8, 559.2), Point3(556.0, 548.8, 559.2), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(500, 0.0, 559.2), Point3(0.0, 0.0, 559.2), Point3(0.0, 500, 559.2), Point3(500, 500, 559.2), white));
    // Right wall
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(0.0, 0.0, 559.2), Point3(0.0, 0.0, 0.0), Point3(0.0, 548.8, 0.0), Point3(0.0, 548.8, 559.2), green));
    // Left wall
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(552.8, 0.0, 0.0), Point3(549.6, 0.0, 559.2), Point3(556.0, 548.8, 559.2), Point3(556.0, 548.8, 0.0), red));

    // Light
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(343.0, 548.8, 332.0), Point3(213.0, 548.8, 332.0), Point3(213.0, 548.8, 227.0),
                                                    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(500, 548.8, 0), Point3(500, 548.8, 500), Point3(0, 548.8, 500), Point3(0, 548.8, 0),
                                                    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(556.0, 548, 0.0), Point3(556.0, 548, 559.2), Point3(0.0, 548, 559.2), Point3(0.0, 548, 0.0),
                                                    std::make_shared<LightPower>(LightPower(RGB(20, 20, 20)))));

    // // Short block
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(130, 165, 65), Point3(82, 165, 225), Point3(240, 165, 272), Point3(290, 165, 114), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(290, 0, 114), Point3(290, 165, 114), Point3(240, 165, 272), Point3(240, 0, 272), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(130, 0, 65), Point3(130, 165, 65), Point3(290, 165, 114), Point3(290, 0, 114), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(82, 0, 225), Point3(82, 165, 225), Point3(130, 165, 65), Point3(130, 0, 65), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(240, 0, 272), Point3(240, 165, 272), Point3(82, 165, 225), Point3(82, 0, 225), white));

    // // Tall block
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(423, 330, 274), Point3(265, 330, 296), Point3(314, 330, 456), Point3(472, 330, 406), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(423, 0, 247), Point3(423, 330, 247), Point3(472, 330, 406), Point3(472, 0, 406), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(472, 0, 406), Point3(472, 330, 406), Point3(314, 330, 456), Point3(314, 0, 456), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(314, 0, 456), Point3(314, 330, 456), Point3(265, 330, 296), Point3(265, 0, 296), white));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(265, 0, 296), Point3(265, 330, 296), Point3(423, 330, 247), Point3(423, 0, 247), white));

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

void dielectric_1(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.9f, 0.8f, 0.6f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.70f, 0.085f, 0.085f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.8f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.68f, 0.93f, 0.93f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.5f, 0.6))));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, -3), 0.5, std::make_shared<Dielectric>(1.52f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 0), 1, std::make_shared<Dielectric>(Dielectric(1.52f))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 0), 1, std::make_shared<PerfectSpecular>(0.8)));
    scene.add_shape(std::make_shared<Sphere>(Point3(1.5, -0.75, -2), 1.25, std::make_shared<Dielectric>(1.52f)));

    scene.add_shape(std::make_shared<Quadrilateral>(Point3(2, 2.995, -3), Point3(-2, 2.995, 0), Point3(-2, 2.995, -3), std::make_shared<LightPower>(RGB(5.0f, 5.0f, 5.0f))));
    scene.fix();
}

void dielectric_2(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 18.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.9f, 0.8f, 0.6f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.70f, 0.085f, 0.085f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.8f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.68f, 0.93f, 0.93f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.5f, 0.6))));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, -4), 0.5, std::make_shared<Dielectric>(1.52f)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 0), 1, std::make_shared<Dielectric>(1.52f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(-1, 1, 0), 1, std::make_shared<Dielectric>(1.8)));
    scene.add_shape(std::make_shared<Sphere>(Point3(1.5, -1, -2), 1, std::make_shared<Dielectric>(1.52f)));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.5, 0), RGB(5, 5, 5)));
    scene.fix();
}

void dielectric_3(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.9f, 0.8f, 0.6f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.70f, 0.085f, 0.085f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.8f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.68f, 0.93f, 0.93f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.5f, 0.6))));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, -3), 0.5, std::make_shared<Dielectric>(1.52f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 0), 1, std::make_shared<Dielectric>(1.52f)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 0), 1, std::make_shared<PerfectSpecular>(0.8)));
    scene.add_shape(std::make_shared<Sphere>(Point3(1.5, -0.75, -2), 1.25, std::make_shared<Dielectric>(1.52f)));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.5, 0), RGB(5, 5, 5)));
    scene.fix();
}

void difusos_2(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.9f, 0.8f, 0.6f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.70f, 0.085f, 0.085f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.8f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.68f, 0.93f, 0.93f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.5f, 0.6))));

    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(2, 2.995, -3), Point3(-2, 2.995, 0), Point3(-2, 2.995, -3), std::make_shared<LightPower>(RGB(5.0f, 5.0f, 5.0f))));
    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.5, 0), RGB(5, 5, 5)));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, -3), 0.5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.82f, 0.41f, 0.11f)))));   // Chocolate
    scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 0), 1, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.9f, 0.49f, 0.31f)))));           // Naranja
    scene.add_shape(std::make_shared<Sphere>(Point3(1.5, -0.75, -2), 1.25, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.48f, 0.95f, 0.3f))))); // Verde

    scene.fix();
}

void difusos_3(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 2, std::make_shared<LambertianDiffuse>(RGB(0.5, 0.5, 0.5))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8, 0.1, 0.1))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1, 0.1, 0.8))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.5, 0.5, 0.5))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.5, 0.5, 0.5))));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 1.5, 0), RGB(5, 5, 5)));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(2, 2.995, -3), Point3(-2, 2.995, 0), Point3(-2, 2.995, -3), std::make_shared<LightPower>(RGB(5.0f, 5.0f, 5.0f))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 2.5, 0), 0.5, std::make_shared<LightPower>(RGB(5.0f, 5.0f, 5.0f))));

    // scene.add_shape(std::make_shared<Sphere>(Point3(-1, -2, 1), 1, std::make_shared<LambertianDiffuse>(RGB(0.82f, 0.41f, 0.11f))));   // Chocolate
    // scene.add_shape(std::make_shared<Sphere>(Point3(1.5, -2, -1), 1, std::make_shared<LambertianDiffuse>(RGB(0.82f, 0.41f, 0.11f)))); // Chocolate

    scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, 0), 1, std::make_shared<Dielectric>(2.42))); // Chocolate
    scene.add_shape(std::make_shared<Sphere>(Point3(1.75, -2, -1), 1, std::make_shared<Dielectric>(1.5))); // Chocolate

    // scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, 0), 1, std::make_shared<Phong>(RGB(0.05, 0.6, 0.6), 0.3, 1000)));  // Chocolate
    // scene.add_shape(std::make_shared<Sphere>(Point3(1.75, -2, -1), 1, std::make_shared<Phong>(RGB(0.2f, 0.7f, 0.2f), 0.2, 10))); // Chocolate

    // scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, -1), 1, std::make_shared<PerfectSpecular>(0.5))); // Chocolate
    // scene.add_shape(std::make_shared<Sphere>(Point3(1.75, -2, -2), 1, std::make_shared<PerfectSpecular>(0.8))); // Chocolate

    scene.fix();
}

void phong_1(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    // scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.5, 0.5, 0.5))));
    // scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8, 0.1, 0.1))));
    // scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1, 0.1, 0.8))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.5, 0.5, 0.5))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.5, 0.5, 0.5))));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.5, 0), RGB(5, 5, 5)));
    // scene.add_shape(std::make_shared<Quadrilateral>(Point3(2, 2.995, -2), Point3(-2, 2.995, 0), Point3(-2, 2.995, -2), std::make_shared<LightPower>(RGB(5.0f, 5.0f, 5.0f))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 2.5, 0), 0.1, std::make_shared<LightPower>(RGB(5, 5, 5)))); // Chocolate

    // scene.add_shape(std::make_shared<Sphere>(Point3(-1, -2, 1), 1, std::make_shared<LambertianDiffuse>(RGB(0.82f, 0.41f, 0.11f))));   // Chocolate
    // scene.add_shape(std::make_shared<Sphere>(Point3(1.5, -2, -1), 1, std::make_shared<LambertianDiffuse>(RGB(0.82f, 0.41f, 0.11f)))); // Chocolate

    // scene.add_shape(std::make_shared<Sphere>(Point3(-1, -2, 1), 1, std::make_shared<Plastic>(RGB(0.8, 0.2, 0.2), 0.1))); // Chocolate
    // scene.add_shape(std::make_shared<Sphere>(Point3(1.75, -2, -2), 1, std::make_shared<Dielectric>(1.5)));               // Chocolate
    // scene.add_shape(std::make_shared<Sphere>(Point3(1.75, -2, -2), 1, std::make_shared<Phong>(RGB(0.2, 0.8, 0.2), 0.1, 20))); // Chocolate

    // scene.add_shape(std::make_shared<Sphere>(Point3(0, -2, 0), 1, std::make_shared<Phong>(RGB(0.2, 0.8, 0.2), 0.04, 2))); // Chocolate
    scene.add_shape(std::make_shared<Sphere>(Point3(0, -2, 0), 1, std::make_shared<Phong>(RGB(0.2, 0.5, 0.2), 0.4, 1250))); // Chocolate
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, -2, 0), 1, std::make_shared<PerfectSpecular>(0.8))); // Chocolate
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 1, 0), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.8, 0.2)))); // Chocolate

    scene.fix();
}

void phong_250(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.3f, 0.3f, 0.3f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.3f, 0.3f, 0.3))));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.5, 0), RGB(5, 5, 5)));
    scene.add_shape(std::make_shared<Sphere>(Point3(0.0f, -1.5, 0.0f), 1.5, std::make_shared<Phong>(Phong(RGB(0.55, 0.65, 0.2), 0.2f, 250.0f))));

    scene.fix();
}

void box(bool zforward, Scene &scene, int h, int w, int d, RGB cceil, RGB cfloor, RGB cright, RGB cleft, RGB cback) {
    // ceil
    scene.add_shape(std::make_shared<Triangle>(Point3(-w, h, d), Point3(-w, h, -d), Point3(w, h, d), std::make_shared<LambertianDiffuse>(cceil)));
    scene.add_shape(std::make_shared<Triangle>(Point3(w, h, -d), Point3(w, h, d), Point3(-w, h, -d), std::make_shared<LambertianDiffuse>(cceil)));
    // floor
    scene.add_shape(std::make_shared<Triangle>(Point3(-w, -h, -d), Point3(-w, -h, d), Point3(w, -h, d), std::make_shared<LambertianDiffuse>(cfloor)));
    scene.add_shape(std::make_shared<Triangle>(Point3(w, -h, d), Point3(w, -h, -d), Point3(-w, -h, -d), std::make_shared<LambertianDiffuse>(cfloor)));
    // back
    if (zforward) {
        scene.add_shape(std::make_shared<Triangle>(Point3(-w, -h, d), Point3(-w, h, d), Point3(w, h, d), std::make_shared<LambertianDiffuse>(cback)));
        scene.add_shape(std::make_shared<Triangle>(Point3(w, h, d), Point3(w, -h, d), Point3(-w, -h, d), std::make_shared<LambertianDiffuse>(cback)));
    } else {
        scene.add_shape(std::make_shared<Triangle>(Point3(-w, -h, -d), Point3(-w, h, -d), Point3(w, h, -d), std::make_shared<LambertianDiffuse>(cback)));
        scene.add_shape(std::make_shared<Triangle>(Point3(w, h, -d), Point3(w, -h, -d), Point3(-w, -h, -d), std::make_shared<LambertianDiffuse>(cback)));
    }
    // right
    scene.add_shape(std::make_shared<Triangle>(Point3(w, h, -d), Point3(w, -h, -d), Point3(w, h, d), std::make_shared<LambertianDiffuse>(cright)));
    scene.add_shape(std::make_shared<Triangle>(Point3(w, -h, d), Point3(w, h, d), Point3(w, -h, -d), std::make_shared<LambertianDiffuse>(cright)));
    // left
    scene.add_shape(std::make_shared<Triangle>(Point3(-w, -h, -d), Point3(-w, h, -d), Point3(-w, h, d), std::make_shared<LambertianDiffuse>(cleft)));
    scene.add_shape(std::make_shared<Triangle>(Point3(-w, h, d), Point3(-w, -h, d), Point3(-w, -h, -d), std::make_shared<LambertianDiffuse>(cleft)));
}

void box(bool zforward, Scene &scene, int h, int w, int d, RGB cceil, RGB cfloor, RGB cright, RGB cleft, RGB cback, int lw, int ld, RGB lpower, int lz) {
    box(zforward, scene, h, w, d, cceil, cfloor, cright, cleft, cback);
    // // area light
    // scene.add_shape(std::make_shared<Triangle>(Point3(-lw, h - 0.05, ld + lz), Point3(-lw, h - 0.05, -ld + lz), Point3(lw, h - 0.05, ld + lz), std::make_shared<LightPower>(lpower)));
    // scene.add_shape(std::make_shared<Triangle>(Point3(lw, h - 0.05, -ld + lz), Point3(lw, h - 0.05, ld + lz), Point3(-lw, h - 0.05, -ld + lz), std::make_shared<LightPower>(lpower)));

    // area light
    scene.add_shape(std::make_shared<Triangle>(Point3(lw, h - 0.05, ld + lz), Point3(-lw, h - 0.05, -ld + lz), Point3(-lw, h - 0.05, ld + lz), std::make_shared<LightPower>(lpower)));
    scene.add_shape(std::make_shared<Triangle>(Point3(lw, h - 0.05, ld + lz), Point3(lw, h - 0.05, -ld + lz), Point3(-lw, h - 0.05, -ld + lz), std::make_shared<LightPower>(lpower)));
}

void escena_conejos(int width, int height, Camera &c, Scene &scene) {

    // c = Camera(orig, left, up, front);
    // c = Camera(Point3(0, 0, -10), Vector3(3, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));
    c = Camera(35, Point3(0, -2, 0), 20, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    RGB white(0.85, 0.85, 0.85);
    RGB red(0.85, 0.2, 0.2);
    RGB green(0.2, 0.85, 0.2);

    RGB power(5, 5, 5);

    float h = 6, w = 8, d = 10;

    // box(scene, h, w, d, white, white, green, red, white, 5, 5, power, 0);
    box(true, scene, h, w, d, white, white, green, red, white);

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 4, 0), RGB(20, 20, 20)));

    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res3_smooth.ply");
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_res3.ply");
    std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper_smooth.ply");
    // std::vector<Triangle> triangle_mesh = readPLY("../models/bun_zipper.ply");

    // z backwards
    // TriangleMesh tm1 = TriangleMesh(triangle_mesh, std::make_shared<Plastic>(RGB(0.7f, 0.4f, 0.5f), 0.1f), Point3(3.7, -4.25, -3), 30);
    // TriangleMesh tm2 = TriangleMesh(triangle_mesh, std::make_shared<PerfectSpecular>(0.9f), Point3(-3.7, -4.25, -3), 30);
    // TriangleMesh tm3 = TriangleMesh(triangle_mesh, std::make_shared<Dielectric>(1.5), Point3(0, -4.25, 2), 30);

    TriangleMesh tm1 = TriangleMesh(triangle_mesh, std::make_shared<Plastic>(RGB(0.7f, 0.4f, 0.5f), 0.1f), Point3(3.7, -4.25, 3), 30, true);
    TriangleMesh tm2 = TriangleMesh(triangle_mesh, std::make_shared<PerfectSpecular>(0.9f), Point3(-3.7, -4.25, 3), 30, true);
    TriangleMesh tm3 = TriangleMesh(triangle_mesh, std::make_shared<Dielectric>(1.5), Point3(0, -4.25, 0), 30, true);

    scene.add_shape(std::make_shared<TriangleMesh>(tm1));
    scene.add_shape(std::make_shared<TriangleMesh>(tm2));
    scene.add_shape(std::make_shared<TriangleMesh>(tm3));

    scene.fix();
}

void escena_dragon(int width, int height, Camera &c, Scene &scene) {

    // c = Camera(orig, left, up, front);
    // c = Camera(Point3(0, 0, -10), Vector3(3, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));
    c = Camera(30, Point3(0, 0, 0), 15, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    RGB white(0.85, 0.85, 0.85);
    RGB red(0.85, 0.2, 0.2);
    RGB green(0.2, 0.85, 0.2);
    RGB blue(0.2, 0.2, 0.85);
    RGB power(5, 5, 5);

    box(true, scene, 3, 3, 3, white, white, green, red, blue, 2, 2, power, 0);

    std::vector<Triangle> dragon = readPLY("../models/dragon_vrip_res3.ply");
    TriangleMesh tm = TriangleMesh(dragon, std::make_shared<PerfectSpecular>(0.8), Point3(0, -1.5, 0), 25, true);
    // TriangleMesh tm = TriangleMesh(dragon, std::make_shared<Dielectric>(1.5), Point3(0, -1.6, 0), 25);
    scene.add_shape(std::make_shared<TriangleMesh>(tm));

    scene.fix();
}

void escena_dof(int width, int height, Camera &c, Scene &scene) {

    c = Camera(25, Point3(0, 0, -1), 20, (float)width / height);

    scene.set_background(RGB(0, 0, 0));

    RGB white(0.85, 0.85, 0.85);

    RGB red(0.85, 0.2, 0.2);
    RGB green(0.2, 0.85, 0.2);
    RGB blue(0.2, 0.2, 0.85);
    RGB power(5, 5, 5);

    box(true, scene, 3, 3, 8, white, white, green, red, white, 2, 2, power, -1);

    scene.add_shape(std::make_shared<Sphere>(Point3(0, -2, -1), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.5, 0.3))));
    scene.add_shape(std::make_shared<Sphere>(Point3(-1, -2, -3), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.5, 0.3))));
    scene.add_shape(std::make_shared<Sphere>(Point3(1, -2, 1), 1, std::make_shared<LambertianDiffuse>(RGB(0.2, 0.5, 0.3))));

    scene.fix();
}

void dielectric_4(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.9f, 0.8f, 0.6f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.70f, 0.085f, 0.085f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.8f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.68f, 0.93f, 0.93f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.5f, 0.6))));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, -4), 0.5, std::make_shared<Dielectric>(1.52f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(-1, 1, 0), 1, std::make_shared<Dielectric>(1.8)));
    scene.add_shape(std::make_shared<Sphere>(Point3(1.5, -1, -2), 1, std::make_shared<Dielectric>(1.52f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(-1, 1, 0), 0.25, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.9f, 0.49f, 0.31f)))));
    scene.add_shape(std::make_shared<Sphere>(Point3(1.5, -1, -2), 0.25, std::make_shared<PerfectSpecular>(PerfectSpecular(0.95f))));
    scene.add_shape(std::make_shared<Sphere>(Point3(-1.5, -2, -4), 0.15, std::make_shared<Plastic>(Plastic(RGB(0.7f, 0.0f, 0.6f), 0.1f))));
    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.5, 0), RGB(5, 5, 5)));
    scene.fix();
}

void texture_1(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;
    Image texture = readPPM("../textures/world.ppm");
    Image texture2 = readPPM("../textures/world.ppm");

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture))), Vector3(0, 1, 0), Vector3(1, 0, 0), Point3(3, -3, 3)));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.7f, 0.45f, 0.65f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.44f, 0.86f, 0.86f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<Texture>(Texture(TextureMappingUV(texture2))), Vector3(0, 0, 12), Vector3(6, 0, 0), Point3(3, -3, -9)));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.9f, 0.8f, 0.7))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, 1), 20, std::make_shared<LambertianDiffuse>(RGB(0.2f, 0.2f, 0.2f))));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2.5, 0), RGB(5, 5, 5)));
    scene.fix();
}

void texture_2(int &width, int &height, Camera &c, Scene &scene) {

    width = 800;
    height = 800;
    Image texture = readPPM("../textures/world.ppm");
    Image texture2 = readPPM("../textures/world.ppm");
    Image texture3 = readPPM("../textures/world.ppm");

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.9f, 0.8f, 0.6f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.70f, 0.085f, 0.085f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.8f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.68f, 0.93f, 0.93f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.5f, 0.6))));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, 0, 0), 1.5, std::make_shared<Texture>(TextureMappingUV(texture))));

    scene.add_shape(std::make_shared<Quadrilateral>(Point3(2.995, 1.5, 1), Point3(2.995, -1.5, -3), Point3(2.995, 1.5, -3), std::make_shared<Texture>(TextureMappingUV(texture3))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2.995, 1.5, -3), Point3(-2.995, -1.5, 1), Point3(-2.995, 1.5, 1), std::make_shared<Texture>(TextureMappingUV(texture2))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(2, 2.995, -3), Point3(-2, 2.995, 0), Point3(-2, 2.995, -3), std::make_shared<LightPower>(RGB(5.0f, 5.0f, 5.0f))));

    scene.fix();
}

void esferas(int &width, int &height, Camera &c, Scene &scene) {
    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(50, 52, 295.6), 15.0f, (float)width / (float)height);
    scene.set_background(RGB(0, 0, 0));

    float scale = 1e4;
    // Left
    scene.add_shape(std::make_shared<Sphere>(Point3(scale + 1, 40.8, 81.6), scale, std::make_shared<LambertianDiffuse>(RGB(.75, .25, .25))));
    // Right
    scene.add_shape(std::make_shared<Sphere>(Point3(-scale + 99, 40.8, 81.6), scale, std::make_shared<LambertianDiffuse>(RGB(.25, .25, .75))));
    // Back
    scene.add_shape(std::make_shared<Sphere>(Point3(50, 40.8, scale), scale, std::make_shared<LambertianDiffuse>(RGB(.75, .75, .75))));
    // Front
    // scene.add_shape(std::make_shared<Sphere>(Point3(50, 40.8, -1e4 + 170), 1e4, std::make_shared<LambertianDiffuse>(RGB(0, 0, 0))));
    // Botom
    scene.add_shape(std::make_shared<Sphere>(Point3(50, scale, 81.6), scale, std::make_shared<LambertianDiffuse>(RGB(.75, .75, .75))));
    // Top
    scene.add_shape(std::make_shared<Sphere>(Point3(50, -scale + 81.6, 81.6), scale, std::make_shared<LambertianDiffuse>(RGB(.75, .75, .75))));
    // Mirror
    scene.add_shape(std::make_shared<Sphere>(Point3(27, 16.5, 47), 16.5, std::make_shared<PerfectSpecular>(0.9)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(27, 16.5, 47), 16.5, std::make_shared<LambertianDiffuse>(RGB(.75, .25, .25))));
    // Glass
    scene.add_shape(std::make_shared<Sphere>(Point3(73, 16.5, 78), 16.5, std::make_shared<Dielectric>(1.50)));
    // Light
    scene.add_shape(std::make_shared<Sphere>(Point3(50, 681.6 - .27, 81.6), 600, std::make_shared<LightPower>(RGB(12, 12, 12))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(50, 681.6 - .5, 81.6), 600, std::make_shared<LightPower>(RGB(12, 12, 12))));
    // scene.add_shape(std::make_shared<Sphere>(Point3(50, 70, 50), 10, std::make_shared<LightPower>(RGB(12, 12, 12))));

    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(50, 40, 50), RGB(1000, 1000, 1000)));
    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(50, 40, 50), RGB(200, 1000, 1000)));
    // scene.add_light(std::make_shared<PointLight>(&scene, Point3(50, 40, 50), RGB(1000, 1000, 1000)));

    scene.fix();
}

void esferas2(int &width, int &height, Camera &c, Scene &scene) {
    width = 800;
    height = 800;

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background((RGB(0, 0, 0)));

    RGB white(0.75, 0.75, 0.75);
    RGB red(0.85, 0.2, 0.2);
    RGB green(0.2, 0.85, 0.2);
    RGB blue(0.2, 0.2, 0.85);
    RGB power(5, 5, 5);

    box(true, scene, 4, 4, 4, white, white, green, red, white);
    // box(scene, 3, 3, 8, white, white, green, red, white, 2, 2, power, -1);

    // Left
    // scene.add_shape(std::make_shared<Sphere>(Point3(-2, 0, 0), 1, std::make_shared<LambertianDiffuse>(RGB(.75, .25, .25))));
    // Right
    // scene.add_shape(std::make_shared<Sphere>(Point3(2, 0, 0), 1, std::make_shared<LambertianDiffuse>(RGB(.25, .25, .75))));
    // Back
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 0, -2), 1, std::make_shared<LambertianDiffuse>(RGB(.75, .75, .75))));
    // Botom
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, -2, 0), 1, std::make_shared<LambertianDiffuse>(RGB(.75, .75, .75))));
    // Top
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 2, 0), 1, std::make_shared<LambertianDiffuse>(RGB(.75, .75, .75))));
    // Mirror
    // scene.add_shape(std::make_shared<Sphere>(Point3(27, 16.5, 47), 16.5, std::make_shared<PerfectSpecular>(0.9)));
    // scene.add_shape(std::make_shared<Sphere>(Point3(-1, 0, 0), 1, std::make_shared<LambertianDiffuse>(RGB(.75, .25, .25))));
    // Glass
    // scene.add_shape(std::make_shared<Sphere>(Point3(1, 0, 0), 1, std::make_shared<Dielectric>(1.50)));
    // Light
    // scene.add_shape(std::make_shared<Sphere>(Point3(0, 1.5, 0), 0.2, std::make_shared<LightPower>(RGB(12, 12, 12))));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 1.5, 0), RGB(5, 5, 5)));

    scene.fix();
}

// Included scenes

void default_scene(int width, int height, Camera &c, Scene &scene) {

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.5f, 0.5f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.1f, 0.1f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1f, 0.8f, 0.1f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.5f, 0.5f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.5f, 0.5f, 0.5f))));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1.25, -2, -1.5), 1, std::make_shared<Dielectric>(1.5f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(1.25, -2, 1), 1, std::make_shared<Plastic>(Plastic(RGB(0.7f, 0.0f, 0.6f), 0.1f))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(2, 2.995, -3), Point3(-2, 2.995, 0), Point3(-2, 2.995, -3), std::make_shared<LightPower>(RGB(5.0f, 5.0f, 5.0f))));
    scene.fix();
}

void default_point_light(int width, int height, Camera &c, Scene &scene) {

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.5f, 0.5f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.8f, 0.1f, 0.1f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.1f, 0.8f, 0.1f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.5f, 0.5f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.5f, 0.5f, 0.5f))));

    scene.add_shape(std::make_shared<Sphere>(Point3(-1.25, -2, -1.5), 1, std::make_shared<Dielectric>(1.5f)));
    scene.add_shape(std::make_shared<Sphere>(Point3(1.25, -2, 1), 1, std::make_shared<Plastic>(Plastic(RGB(0.7f, 0.0f, 0.6f), 0.1f))));

    scene.add_light(std::make_shared<PointLight>(&scene, Point3(0, 2, 0), RGB(5, 5, 5)));
    scene.fix();
}

void textures(int width, int height, Camera &c, Scene &scene) {

    Image texture = readPPM("../textures/fire.ppm");
    Image texture2 = readPPM("../textures/grito_simpson.ppm");
    Image texture3 = readPPM("../textures/programer.ppm");

    c = Camera(30.0f, Point3(0, 0, 0), 15.0f, (float)width / (float)height);

    scene.set_background(RGB(0, 0, 0));

    scene.add_shape(std::make_shared<Plane>(Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(RGB(0.9f, 0.8f, 0.6f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.70f, 0.085f, 0.085f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.8f, 0.5f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.68f, 0.93f, 0.93f))));
    scene.add_shape(std::make_shared<Plane>(Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(RGB(0.4f, 0.5f, 0.6))));
    scene.add_shape(std::make_shared<Sphere>(Point3(0, 0, 0), 1.5, std::make_shared<Texture>(TextureMappingUV(texture))));

    scene.add_shape(std::make_shared<Quadrilateral>(Point3(2.995, 1.5, 1), Point3(2.995, -1.5, -3), Point3(2.995, 1.5, -3), std::make_shared<Texture>(TextureMappingUV(texture3))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(-2.995, 1.5, -3), Point3(-2.995, -1.5, 1), Point3(-2.995, 1.5, 1), std::make_shared<Texture>(TextureMappingUV(texture2))));
    scene.add_shape(std::make_shared<Quadrilateral>(Point3(2, 2.995, -3), Point3(-2, 2.995, 0), Point3(-2, 2.995, -3), std::make_shared<LightPower>(RGB(5.0f, 5.0f, 5.0f))));

    scene.fix();
}
