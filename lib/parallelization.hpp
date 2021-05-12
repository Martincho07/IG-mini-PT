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

#include "cbq/ConcurrentBoundedQueue.hpp"
#include "color.hpp"
#include "image.hpp"
#include "integrator.hpp"
#include "pixel.hpp"
#include "random.hpp"
#include "scene.hpp"

#include <iostream>

#define NUM_REGIONS 8
#define CAMERA_PLANE_SIZE 1.0f

// Defines the behaviour of the producer
// Divides the image in rectangles and pushes them
// to the concurrent queue
void producer_task(ConcurrentBoundedQueue<std::vector<Pixel>> &cbq, const Vector3 &u, const Vector3 &r, int width, int height);

// Defines the behaviour of the consumers
// They take rectangles from the queue and calculate
// the color of the pixels inside them
void consumer_task(ConcurrentBoundedQueue<std::vector<Pixel>> &cbq, const Scene &scene, Image &image, std::shared_ptr<Integrator> integrator, int num_rays);
