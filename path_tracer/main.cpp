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
                 "  Output file options:\n"
                 "    -o, --out_file       Output file name\n"
                 "    -w, --width          Output image width\n"
                 "    -h, --height         Output image height\n"
                 "    -c, --color_res      Output image color resolution\n"
                 "  Rendering options:\n"
                 "    -p, --pixel_rays     Number of points per pixel\n"
                 "    -t, --threads        Number of hardware concurrent threads\n"
                 "    -s, --scene          Scene to render\n"
                 "  -?, --help             Show this help message and quit"
              << std::endl;
}

int main(int argc, char **argv) {
    unsigned int num_threads, pixel_rays, selected_scene, width, height, color_res;

    // options descriptor
    static struct option longopts[] = {
        // {"width", required_argument, 0, 'h'},
        // {"height", required_argument, 0, 'w'},
        {"scene", required_argument, 0, 's'},
        {"pixel_rays", required_argument, 0, 'p'},
        {"threads", required_argument, 0, 't'},
        {"help", no_argument, 0, '?'},
        {"out_file", no_argument, 0, 'o'},
        {"width", no_argument, 0, 'w'},
        {"height", no_argument, 0, 'h'},
        {"color_res", no_argument, 0, 'c'},
        {NULL, 0, NULL, 0}};

    // default option values
    num_threads = std::thread::hardware_concurrency();
    pixel_rays = 100;
    selected_scene = 0;
    width = 800;
    height = 800;
    color_res = 10000000;
    std::string output_file = "image";

    int ch;
    int index;
    while ((ch = getopt_long(argc, argv, "?p:t:h:s:o:w:h:c:", longopts, &index)) != -1) {
        switch (ch) {
        case '?':
            help();
            return 0;
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
        case 'o':
            output_file = optarg;
            break;
        case 'w':
            width = atoi(optarg);
            break;
        case 'h':
            height = atoi(optarg);
            break;
        case 'c':
            output_file = atoi(optarg);
            break;
        default:
            help();
            return 1;
        }
    }

    // Select scene
    Scene scene;
    Camera camera;

    std::cout << "Output image: width: " << width << ", height: " << height << " color res: " << color_res << std::endl;

    switch (selected_scene) {
    case 1:
        // escenaDielectrico(width, height, camera, scene);
        // dielectric_1(width, height, camera, scene);
        // esferas(width, height, camera, scene);
        // esferas2(width, height, camera, scene);
        default_point_light(width, height, camera, scene);
        break;
    case 2:
        // dielectric_2(width, height, camera, scene);
        // escena4(width, height, camera, scene);
        textures(width, height, camera, scene);
        break;
    case 3:
        // escenaBVH(width, height, camera, scene);
        escena_conejos(width, height, camera, scene);
        break;
    case 4:
        // escena_conejos(width, height, camera, scene);
        // escena_dragon(width, height, camera, scene);
        escena_dof(width, height, camera, scene);
        break;
    // case 5:
    //     escena_dragon(width, height, camera, scene);
    //     break;
    // case 6:
    //     // cornellBox(width, height, camera, scene);
    //     difusos_3(width, height, camera, scene);
    //     break;
    // case 7:
    //     phong_250(width, height, camera, scene);
    //     break;
    // case 8:
    //     // escenaDOF(width, height, camera, scene);
    //     escena_dof(width, height, camera, scene);
    //     break;
    // case 9:
    //     dielectric_4(width, height, camera, scene);
    //     break;
    // case 10:
    //     texture_1(width, height, camera, scene);
    //     // texture_2(width, height, camera, scene);
    //     break;
    default:
        default_scene(width, height, camera, scene);
        break;
    }

    // std::cout << "Numero de consumers: " << num_threads << std::endl;
    std::cout << "\nRendering scene " << selected_scene << " (" << pixel_rays << " ppp, " << num_threads << " threads)..."
              << std::endl
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

    std::cout << "\nRendering time: " << diff.count() << " s" << std::endl;
    std::cout << "Number of geometric primitives: " << scene.get_num_shapes() << std::endl;
    std::cout << "Number of pixels: " << height * width << std::endl;
    std::cout << "Maximum: " << max(image) << std::endl;
    std::cout << std::endl;

    writeHDR(image, output_file + ".hdr");
    writePPM(image, output_file + "_hdr.ppm", max(image), color_res);

    // clampAndGammaCurve(image, 10, 2.2);
    // clamping(image);
    writePPM(image, output_file + ".ppm", max(image), 255);
};
