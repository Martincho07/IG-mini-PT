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
#include <getopt.h>
#include <memory>
#include <ostream>
#include <thread>
#include <vector>

void help() {
    std::cout << "Usage: path_tracer [options ...]\n\n"
                 "Options:\n"
                 "  Output file options:\n"
                 "    -o, --out_file FILE     Output file name (default image_hdr.ppm)\n"
                 "    -w, --width WIDTH       Output image width (default 800)\n"
                 "    -h, --height HEIGHT     Output image height (default 800)\n"
                 "    -c, --color_res RES     Output image color resolution (default 10000000) \n"
                 "  Rendering options:\n"
                 "    -p, --pixel_rays PPP    Number of points per pixel (default 100)\n"
                 "    -t, --threads N         Number of hardware concurrent threads (default max. threads)\n"
                 "    -s, --scene N           Scene to render\n"
                 "                              [0-10] (default 0)\n"
                 "    -i, --integrator TYPE   Integrator to solve the rendering equation\n"
                 "                              [pathtracing, raytracing, normals] (default pathtracing)\n"
                 "  -?, --help                Show this help message and quit"
              << std::endl;
}

int main(int argc, char **argv) {
    unsigned int num_threads, pixel_rays, selected_scene, width, height, color_res;

    // options descriptor
    static struct option longopts[] = {
        {"scene", required_argument, 0, 's'},
        {"pixel_rays", required_argument, 0, 'p'},
        {"threads", required_argument, 0, 't'},
        {"help", no_argument, 0, '?'},
        {"out_file", no_argument, 0, 'o'},
        {"width", no_argument, 0, 'w'},
        {"height", no_argument, 0, 'h'},
        {"color_res", no_argument, 0, 'c'},
        {"integrator", no_argument, 0, 'i'},
        {NULL, 0, NULL, 0}};

    // default option values
    num_threads = std::thread::hardware_concurrency();
    pixel_rays = 100;
    selected_scene = 0;
    width = 800;
    height = 800;
    color_res = 10000000;
    std::string output_file = "image.ppm";
    std::string integrator_type = "pathtracing";

    int ch;
    int index;
    while ((ch = getopt_long(argc, argv, "?p:t:h:s:o:w:h:c:i:", longopts, &index)) != -1) {
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
            if (output_file.substr(output_file.find_last_of(".") + 1) != "ppm") {
                output_file += ".ppm";
            }
            break;
        case 'w':
            width = atoi(optarg);
            break;
        case 'h':
            height = atoi(optarg);
            break;
        case 'c':
            color_res = atoi(optarg);
            break;
        case 'i':
            integrator_type = optarg;
            break;
        default:
            help();
            return 1;
        }
    }

    std::cout << "Output image: width: " << width << ", height: " << height << ", color res: " << color_res << std::endl;

    // Select scene
    Scene scene;
    std::shared_ptr<Camera> camera;

    switch (selected_scene) {
    case 1:
        default_point_light(width, height, camera, scene);
        break;
    case 2:
        escena_conejos(width, height, camera, scene);
        break;
    case 3:
        escena_dragon(width, height, camera, scene);
        break;
    case 4:
        escena_dof(width, height, camera, scene);
        break;
    case 5:
        // dielectric(width, height, camera, scene);
        // texture_1(width, height, camera, scene);
        // texture_2(width, height, camera, scene);
        break;
    case 6:
        textures(width, height, camera, scene);
        break;
    case 7:
        escena_concurso(width, height, camera, scene);
        break;
    default:
        default_scene(width, height, camera, scene);
        // sudor(width, height, camera, scene);
        break;
    }

    std::shared_ptr<Integrator> integrator;

    if (integrator_type == "pathtracing") {
        integrator = std::make_shared<PathTracingIntegrator>(camera);
    } else if (integrator_type == "raytracing") {
        integrator = std::make_shared<RayTracingIntegrator>(camera);
    } else if (integrator_type == "normals") {
        integrator = std::make_shared<NormalMapIntegrator>(camera);
    } else {
        std::cerr << "Unknown integrator: " << integrator_type << std::endl;
        return 1;
    }

    std::cout << "Camera: o " << camera->o << " r " << camera->r
              << " u " << camera->u << " f " << camera->f << std::endl;

    // std::cout << "Numero de consumers: " << num_threads << std::endl;
    std::cout << "\nRendering scene " << selected_scene << " ("
              << pixel_rays << " ppp, "
              << num_threads << " threads, "
              << integrator_type << " integrator"
              << ")..." << std::endl
              << std::endl;

    Image image(width, height);
    ConcurrentBoundedQueue<std::vector<Pixel>> cbq(NUM_REGIONS * NUM_REGIONS);

    // Creacion de los N consumers que rederizaran la imagen
    std::vector<std::thread> consumers(num_threads);

    for (int m = 0; m < num_threads; m++)
        consumers[m] = std::thread(&consumer_task, std::ref(cbq), scene, std::ref(image), integrator, pixel_rays);

    // El productor llena la cola para que los consumers
    // cojan elementos y hagan el renderizado
    producer_task(cbq, camera->u, camera->r, width, height);

    auto init = std::chrono::steady_clock::now();

    // Se pone a trabajar a los N consumers
    for (int m = 0; m < num_threads; m++)
        consumers[m].join();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - init;

    std::cout << "\nRendering time: " << diff.count() << " s" << std::endl;
    std::cout << "Number of geometric primitives: " << scene.get_num_shapes() << std::endl;
    std::cout << "Number of pixels: " << height * width << std::endl;
    std::cout << "Image range: [" << min(image) << ", " << max(image) << "]" << std::endl;
    std::cout << std::endl;

    writePPM(image, output_file, max(image), color_res);
};
