/*********************************************************************************
 * main
 *
 * File: path_tracer.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "error.hpp"
#include "file.hpp"
#include "parallelization.hpp"
#include "sample_scenes.hpp"
#include "scene.hpp"
#include "shape.hpp"

#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <getopt.h>
#include <iterator>
#include <memory>
#include <ostream>
#include <thread>
#include <utility>
#include <vector>

void help() {
    std::cout << "Usage: path_tracer [options ...]\n\n"
                 "Options:\n"
                 "  -p, --pixel_rays     Number of points per pixel\n"
                 "  -t, --threads        Number of hardware concurrent threads\n"
                 "  -s, --scene          Scene to render\n"
                 "  -h, --help           Show this help message and quit"
              << std::endl;
}

int main(int argc, char **argv) {
    int width, height;
    unsigned int num_threads, pixel_rays, selected_scene;

    // pixel_rays (p)
    // threads

    // options descriptor
    static struct option longopts[] = {
        // {"width", required_argument, 0, 'h'},
        // {"height", required_argument, 0, 'w'},
        {"scene", required_argument, 0, 's'},
        {"pixel_rays", required_argument, 0, 'p'},
        {"threads", required_argument, 0, 't'},
        {"help", no_argument, 0, 'h'},
        {NULL, 0, NULL, 0}};

    // default option values
    num_threads = std::thread::hardware_concurrency();
    pixel_rays = 1;
    selected_scene = 1;

    int ch;
    int index;
    while ((ch = getopt_long(argc, argv, "p:t:hs:", longopts, &index)) != -1) {
        switch (ch) {
        case 'p':
            pixel_rays = atoi(optarg);
            break;
        case 't':
            if (atoi(optarg) > num_threads) {
                std::cerr << "The maximum number of hardware concurrent threads is " << num_threads << "!" << std::endl;
            }
            num_threads = atoi(optarg);
            break;
        case 's':
            selected_scene = atoi(optarg);
            break;
        case 'h':
            help();
            return 0;
        default:
            help();
            return 1;
        }
    }

    // Select scene
    Scene scene;
    Camera camera;

    switch (selected_scene) {
    case 1:
        escenaDielectrico(width, height, camera, scene);
        break;
    case 2:
        escena4(width, height, camera, scene);
        break;
    case 3:
        escenaBVH(width, height, camera, scene);
        break;
    default:
        escena4(width, height, camera, scene);
        break;
    }

    // std::cout << "Numero de consumers: " << num_threads << std::endl;
    std::cout << "Renderizando escena " << selected_scene << " (" << num_threads << " threads)..."
              << std::endl;

    Image image(width, height);
    ConcurrentBoundedQueue<std::vector<Pixel>> cbq(NUM_REGIONS * NUM_REGIONS);

    // Creacion de los N consumers que rederizaran la imagen
    std::vector<std::thread> consumers(num_threads);

    for (int m = 0; m < num_threads; m++)
        consumers[m] = std::thread(&consumer_task, &cbq, scene, &image, camera, pixel_rays);

    // El productor llena la cola para que los consumers
    // cojan elementos y hagan el renderizado
    producer_task(cbq, camera.u, camera.r, width, height);

    auto init = std::chrono::steady_clock::now();

    // Se pone a trabajar a los N consumers
    for (int m = 0; m < num_threads; m++)
        consumers[m].join();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - init;

    std::cout << "Tiempo de renderizado: " << diff.count() << std::endl;
    std::cout << "Numero de geometrias: " << scene.get_num_shapes() << std::endl;
    std::cout << "Numero de pixeles: " << height * width << std::endl;
    std::cout << "Maximo: " << max(image) << std::endl;

    writeHDR(image, "texture.hdr");

    // clampAndGammaCurve(image, 10, 2.2);
    // clamping(image);
    writePPM(image, "texture.ppm", max(image), 255);
};
