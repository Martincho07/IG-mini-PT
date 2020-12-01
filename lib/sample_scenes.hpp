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
#include "shape.hpp"

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

void escena4(int &width, int &height, Camera &c, std::vector<std::shared_ptr<Shape>> &scene) {
    // Camera l u f
    width = 240;
    height = 240;

    // c = Camera(orig, left, up, front);
    // c = Camera(Point3(0, 0, -10), Vector3(3, 0, 0), Vector3(0, 3, 0), Vector3(0, 0, 10));
    c = Camera(30, Point3(0, 0, -15), (float)width / height);

    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, -1), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.0f, 0.0f)))));
    scene.push_back(std::make_shared<Plane>(RGB(0, 255, 0), Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0.5f, 0.0f)))));
    scene.push_back(std::make_shared<Plane>(RGB(0, 0, 255), Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.0f, 0.0f, 0.8f)))));
    scene.push_back(std::make_shared<Plane>(RGB(0, 255, 255), Vector3(0, 1, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.0f, 0.8f, 0.8f)))));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, -1, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(1.0f, 0, 0)))));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 0), Vector3(0, 0, -1), 5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(2, 0.8, 1)))));
    // scene.push_back(std::make_shared<Plane>(RGB(0, 255, 0), Vector3(-1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 1, 1)))));
    // scene.push_back(std::make_shared<Plane>(RGB(0, 0, 255), Vector3(1, 0, 0), 3, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(1, 1, 0.8)))));

    // scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, -1, 0), 3, std::make_shared<LigthEmission>(LigthEmission(RGB(1.0f, 1.0f, 1.0f)))));
    // scene.push_back(std::make_shared<Sphere>(RGB(0, 80, 255), Point3(0.8, 1, -5), 1, std::make_shared<LigthEmission>(LigthEmission(RGB(1, 1, 1)))));
    scene.push_back(std::make_shared<Plane>(RGB(255, 0, 255), Vector3(0, -1, 0), 3, std::make_shared<LigthEmission>(LigthEmission(RGB(1000, 1000, 1000)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-3, -2, 0), Point3(3, -2, 3), std::make_shared<LigthEmission>(LigthEmission(RGB(1.0f, 1.0f, 1.0f)))));
    // scene.push_back(std::make_shared<Quadrilateral>(RGB(255, 0, 255), Point3(-2, 2.995, -2), Point3(2, 2.995, 2), std::make_shared<LigthEmission>(LigthEmission(RGB(1000, 1000, 1000)))));

    // scene.push_back(std::make_shared<Triangle>(RGB(255, 0, 255), Point3(-3, 2, 0), Point3(3, 3, 8), Point3(3, -1, -1), std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8f, 0, 0.5)))));

    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0, 2), 0.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));
    // scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(-1.5, -1.5, -2), 1.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));
    // scene.push_back(std::make_shared<Sphere>(RGB(0, 80, 255), Point3(0.8, -2.5, -5), 0.5f, std::make_shared<PerfectSpecular>(PerfectSpecular())));

    scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(0, 0, 2), 1, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.5, 0.5, 0.5)))));
    scene.push_back(std::make_shared<Sphere>(RGB(255, 255, 0), Point3(-1.5, -1.5, 0), 1.5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.8, 0.5, 0.5)))));
    scene.push_back(std::make_shared<Sphere>(RGB(0, 80, 255), Point3(0.8, -2.5, -1), 0.5, std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.5, 0, 0.5)))));

    // scene.push_back(std::make_shared<Quadrilateral>(RGB(0, 80, 255), Point3(-2.5, 2.5, -19.5), Point3(2.5, 2.5, 4.5), std::make_shared<LambertianDiffuse>(LambertianDiffuse(RGB(0.0f, 0.0f, 0.8f)))));

    // std::shared_ptr<Sphere> sphere(new Sphere(RGB(255, 102, 254), Point3(0, 0, 5), 0.5f));
    // scene.push_back(sphere);

    // std::shared_ptr<Sphere> sphere2(new Sphere(RGB(0, 255, 0), Point3(0, 0, 7.5), 2.0f));
    // scene.push_back(sphere2);

    // std::shared_ptr<Sphere> sphere3(new Sphere(RGB(0, 0, 255), Point3(4, 10, 7.5), 2.0f));
    // scene.push_back(sphere3);
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