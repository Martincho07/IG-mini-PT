/*********************************************************************************
 * main
 *
 * File: ray_tracer.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "ConcurrentBoundedQueue.hpp"
#include "Logger.hpp"
#include "Semaphore_V2.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "error.hpp"
#include "file.hpp"
#include "geometry.hpp"
#include "image.hpp"
#include "pixel.hpp"
#include "shape.hpp"
#include "tone_mapping.hpp"

#include <cassert>
#include <chrono>
#include <ctime>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <thread>
#include <utility>
#include <vector>

#define NUM_REGIONS 8
#define CAMERA_PLANE_SIZE 1.0f

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

int getArgValue(int argc, char **argv, int i, int defaultValue) {
    int value = defaultValue;
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        ErrorExit("Missing value after ", argv[i], " argument");
    }
    if (!(std::string(argv[i + 1]) == "D")) {
        try {
            value = std::stof(argv[i + 1]);
        } catch (std::invalid_argument e) {
            ErrorExit("The option value must be a real number: ", argv[i + 1]);
        }
    }
    return value;
}

// Define el comportamiento del producer, que divide
// la imagen en rectandglos y los coloca en una cola
// FIFO
void producer_task(ConcurrentBoundedQueue<std::vector<Pixel>> &cbq, const Vector3 &u, const Vector3 &r, int width, int height) {

    float x_min, x_max, y_min, y_max;

    float init_width = -CAMERA_PLANE_SIZE;
    float init_height = CAMERA_PLANE_SIZE;

    float pixel_width = 2 * (CAMERA_PLANE_SIZE / (float)width);
    float pixel_height = 2 * (CAMERA_PLANE_SIZE / (float)height);

    int width_submatrix = width / NUM_REGIONS;
    int height_submatrix = height / NUM_REGIONS;

    int actual_submatrix = 0;
    int pos = 0;

    std::vector<Pixel> submatrix(width_submatrix * height_submatrix);
    auto init = std::chrono::steady_clock::now();
    for (int i = 0; i < height; i = i + height_submatrix) {

        for (int n = 0; n < width; n = n + width_submatrix) {

            for (int j = i; j < i + height_submatrix; j++) {

                for (int k = n; k < n + width_submatrix; k++) {
                    // Calculo de los limites de las coordenadas x e y de
                    // un pixel
                    x_min = init_width + (k * pixel_width);
                    x_max = init_width + ((k + 1) * pixel_width);
                    y_min = init_height - ((j + 1) * pixel_height);
                    y_max = init_height - (j * pixel_height);
                    submatrix[pos] = Pixel(j, k, x_min, x_max, y_min, y_max);
                    pos++;
                }
            }
            pos = 0;
            // Se encola la submatriz generada
            cbq.enqueue(submatrix);
            actual_submatrix++;
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - init;
    std::cout << "Tiempo de trabajo del producer " << diff.count() << std::endl;
}

// Define el comportamiento de los consumers,
// estos cogen porciones de la imagen original
// y calculan el color de los pixels.
void consumer_task(ConcurrentBoundedQueue<std::vector<Pixel>> *cbq, const std::vector<std::shared_ptr<Shape>> &scene, Image *image, const Camera &c, int id, int num_rays) {

    thread_local std::vector<Pixel> p;
    thread_local RGB color(0, 0, 0);
    thread_local int num_tasks;
    thread_local float x, y;
    thread_local unsigned t_init, t_end;
    thread_local unsigned int seed = 0;

    auto init = std::chrono::steady_clock::now();

    cbq->num_complete(num_tasks);
    while (num_tasks < NUM_REGIONS * NUM_REGIONS) {

        // Se saca de la cola FIFO el primer elemento
        cbq->first(p);
        // Se calcula el color de los pixel de la submatriz
        // desencolada.
        for (const Pixel &pi : p) {

            for (int i = 0; i < num_rays; i++) {

                x = (pi.x_max - pi.x_min) * ((((float)rand_r(&seed)) / (float)RAND_MAX)) + pi.x_min;
                y = (pi.y_max - pi.y_min) * ((((float)rand_r(&seed)) / (float)RAND_MAX)) + pi.y_min;
                color = color + c.generateRay(normalize(Vector3(x, y, 1.0f)), scene);
            }
            color = color / (float)num_rays;

            image->puntOnCoordenate(pi.fila, pi.columna, color);
            color = RGB(0, 0, 0);
        }

        // Se actualiza el numero de tareas realizadas
        cbq->num_complete(num_tasks);
        std::cout << "Completado hilo " << id << ": " << num_tasks << std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - init;
    std::cout << "Tiempo de trabajo del hilo: " << id << " " << diff.count() << std::endl;
}

int main(int argc, char **argv) {

    int width = 1000;
    int height = 1000;
    int width_inc = width / NUM_REGIONS;
    int height_inc = height / NUM_REGIONS;
    float x, y;

    int num_threads, pixel_rays;

    float mod_u = 1;
    float mod_r = 1;

    std::cout << "Relacion modulos: " << mod_r / mod_u << std::endl;
    std::cout << "Relacion pixeles: " << (float)width / (float)height << std::endl;
    assert((mod_r / mod_u) == (float)width / (float)height);

    float acum_width = -mod_r + (mod_r / width);
    float acum_height = mod_u - (mod_u / height);

    float inc_f_width = 2 * (mod_r / width);
    float inc_f_height = 2 * (mod_u / height);

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-' && arg == "-threads") {

            num_threads = getArgValue(argc, argv, i, 1);
            i++;
        } else if (arg[0] == '-' && arg == "-pixel_rays") {

            pixel_rays = getArgValue(argc, argv, i, 1);
            i++;
        }
    }

    std::cout << "Numero de usados hilos: " << num_threads << std::endl;
    unsigned int num_threads_available = std::thread::hardware_concurrency();
    std::cout << "Hasta " << num_threads_available << " hilos pueden ser ejecutados de manera concurrente.\n";

    std::vector<std::shared_ptr<Shape>> scene;
    Camera c;
    escenaPLY(c, scene);

    Image image;

    image.width = width;
    image.height = height;

    // Codigo partiendo la imagen con threads

    ConcurrentBoundedQueue<std::vector<Pixel>> cbq(NUM_REGIONS * NUM_REGIONS);

    // Se inicializa la imagen con in fondo blanco
    for (int i = 0; i < width * height; i++) {

        image.v.push_back(RGB(255, 255, 255));
    }

    // El productor llena la cola para que los consumers
    // cojan elementos y hagan los calculos
    producer_task(cbq, c.u, c.r, width, height);
    auto init = std::chrono::steady_clock::now();
    std::vector<std::thread> consumers(num_threads);

    // Se incializan N consumers
    for (int m = 0; m < num_threads; m++)
        consumers[m] = std::thread(&consumer_task, &cbq, scene, &image, c, m, pixel_rays);

    for (int m = 0; m < num_threads; m++)
        consumers[m].join();

    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = end - init;
    std::cout << "Tiempo de rendering: " << diff.count() << std::endl;
    std::cout << "Numero de geometrias: " << scene.size() << std::endl;
    std::cout << "Numero de pixeles: " << height * width << std::endl;
    writePPM(image, "salida.ppm", 255, 255);
    writeHDR(image, "salida.hdr");
};
