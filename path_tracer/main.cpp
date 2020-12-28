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
#include "shape.hpp"

#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iterator>
#include <memory>
#include <ostream>
#include <thread>
#include <utility>
#include <vector>

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

int main(int argc, char **argv) {
    int width, height;
    unsigned int num_threads, pixel_rays;

    std::vector<std::shared_ptr<Shape>> scene;
    Camera camera;
    escenaDielectrico(width, height, camera, scene);

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

    Image image(width, height);
    ConcurrentBoundedQueue<std::vector<Pixel>> cbq(NUM_REGIONS * NUM_REGIONS);

    // Creacion de los N consumers que rederizaran la imagen
    num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> consumers(num_threads);
    std::cout << "Numero de consumers: " << num_threads << std::endl;
    for (int m = 0; m < num_threads; m++)
        consumers[m] = std::thread(&consumer_task, &cbq, scene, &image, camera, pixel_rays);

    // El productor llena la cola para que los consumers
    // cojan elementos y hagan el renderizado
    producer_task(cbq, camera.u, camera.r, width, height);
    std::cout << "Renderizando... " << std::endl;
    auto init = std::chrono::steady_clock::now();
    // Se pone a trabajar a los N consumers
    for (int m = 0; m < num_threads; m++)
        consumers[m].join();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - init;

    std::cout << "Tiempo de renderizado: " << diff.count() << std::endl;
    std::cout << "Numero de geometrias: " << scene.size() << std::endl;
    std::cout << "Numero de pixeles: " << height * width << std::endl;
    std::cout << "Maximo: " << max(image) << std::endl;
    writePPM(image, "texture.ppm", max(image), 255);
    writeHDR(image, "texture.hdr");
};
