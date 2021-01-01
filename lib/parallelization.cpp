/*********************************************************************************
 * Parallelization functions
 *
 * File: sample_scenes.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "parallelization.hpp"

void producer_task(ConcurrentBoundedQueue<std::vector<Pixel>> &cbq, const Vector3 &u, const Vector3 &r, int width, int height) {

    float x_min, x_max, y_min, y_max;

    float init_width = -CAMERA_PLANE_SIZE;
    float init_height = CAMERA_PLANE_SIZE;

    float pixel_width = 2 * (CAMERA_PLANE_SIZE / (float)width);
    float pixel_height = 2 * (CAMERA_PLANE_SIZE / (float)height);

    int width_submatrix = width / NUM_REGIONS;
    int height_submatrix = height / NUM_REGIONS;

    int actual_submatrix, pos = 0;

    std::vector<Pixel> submatrix(width_submatrix * height_submatrix);
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
}

// Define el comportamiento de los consumers,
// estos cogen porciones de la imagen original
// y calculan el color de los pixels.
void consumer_task(ConcurrentBoundedQueue<std::vector<Pixel>> *cbq, const std::vector<std::shared_ptr<Shape>> &scene, Image *image, const Camera &c, int num_rays) {

    thread_local std::vector<Pixel> p;
    thread_local RGB color(0, 0, 0);
    thread_local int num_tasks;
    thread_local float x, y;
    thread_local unsigned t_init, t_end;
    thread_local unsigned int seed = 0;

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
                color = color + c.trace_path(x, y, scene);
            }
            color = color / (float)num_rays;

            image->fillPixel(pi.fila, pi.columna, color);
            color = RGB(0.0f, 0.0f, 0.0f);
        }

        // Se actualiza el numero de tareas realizadas
        cbq->num_complete(num_tasks);
    }
}
