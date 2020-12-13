/*********************************************************************************
 * main
 *
 * File: path_tracer.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "BRDF.hpp"
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
#include "random.hpp"
#include "shape.hpp"
#include "tone_mapping.hpp"

#include "sample_scenes.hpp"

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

                x = random_float(pi.x_min, pi.x_max);
                y = random_float(pi.y_min, pi.y_max);
                // color = color + c.generateRay(normalize(Vector3(x, y, 1.0f)), scene);
                color = color + c.generateRay2(x, y, scene);
            }
            color = color / (float)num_rays;
            //if (max(color) == 1.0f)
            // std::cout << max(color) << std::endl;

            image->fillPixel(pi.fila, pi.columna, color);
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
    int width, height;

    std::vector<std::shared_ptr<Shape>> scene;
    Camera c;
    escenaDielectrico(width, height, c, scene);

    int width_inc = width / NUM_REGIONS;
    int height_inc = height / NUM_REGIONS;
    float x, y;

    unsigned int num_threads, pixel_rays;

    float mod_u = 1;
    float mod_r = 1;

    // std::cout << "Relacion modulos: " << mod_r / mod_u << std::endl;
    // std::cout << "Relacion pixeles: " << (float)width / (float)height << std::endl;
    // assert((mod_r / mod_u) == (float)width / (float)height);

    float acum_width = -mod_r + (mod_r / width);
    float acum_height = mod_u - (mod_u / height);

    float inc_f_width = 2 * (mod_r / width);
    float inc_f_height = 2 * (mod_u / height);

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-' && arg == "-pixel_rays") {
            pixel_rays = getArgValue(argc, argv, i, 1);
            i++;
        } else if (i != 0) {
            std::cout << "Opcion: " << arg << " no valida" << std::endl;
            return 1;
        };
    }

    num_threads = std::thread::hardware_concurrency();
    std::cout << "Numero de usados hilos: " << num_threads << std::endl;

    Image image;

    image.width = width;
    image.height = height;

    // Codigo partiendo la imagen con threads

    ConcurrentBoundedQueue<std::vector<Pixel>> cbq(NUM_REGIONS * NUM_REGIONS);

    // Se inicializa la imagen con in fondo blanco
    for (int i = 0; i < width * height; i++) {

        image.v.push_back(RGB(0.0f, 0.0f, 0.0f));
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
    ClampAndGammaCurve clamp(.5f, 2.2f);

    //image.applyToneMappingOperator(clamp);
    std::cout << "Tiempo de rendering: " << diff.count() << std::endl;
    std::cout << "Numero de geometrias: " << scene.size() << std::endl;
    std::cout << "Numero de pixeles: " << height * width << std::endl;

    //image.applyToneMappingOperator(Equalize(max(image)));

    // writePPM(image, "salida.ppm", max(image), 1000000000);
    writePPM(image, "diamante.ppm", max(image), 255);
    writeHDR(image, "diamante.hdr");
};
