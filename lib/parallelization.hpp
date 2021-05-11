/*********************************************************************************
 * Parallelization functions
 *
 * File: parallelization.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "camera.hpp"
#include "cbq/ConcurrentBoundedQueue.hpp"
#include "color.hpp"
#include "geometry.hpp"
#include "image.hpp"
#include "pixel.hpp"
#include "random.hpp"
#include "scene.hpp"

#include <iostream>

#define NUM_REGIONS 8
#define CAMERA_PLANE_SIZE 1.0f

// Define el comportamiento del producer, que divide
// la imagen en rectángulos y los coloca en una cola
// FIFO
void producer_task(ConcurrentBoundedQueue<std::vector<Pixel>> &cbq, const Vector3 &u, const Vector3 &r, int width, int height);

// Define el comportamiento de los consumers,
// estos cogen porciones de la imagen original
// y calculan el color de los pixels.
void consumer_task(ConcurrentBoundedQueue<std::vector<Pixel>> *cbq, const Scene &scene, Image *image, const Camera &c, int num_rays);
