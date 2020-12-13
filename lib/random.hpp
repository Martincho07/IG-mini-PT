/*********************************************************************************
 * Random number generation functions 
 *
 * File: random.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 1/12/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "geometry.hpp"
#include <random>

// Return a random real number between 0 and 1
float random_float();

// Return a random real number between 0 and <n>
float random_float(float n);

// Return a random real number between <min> and <max>
float random_float(float min, float max);

// Sampling funcions

// Random direction sampled uniformly on unit hemisphere
Vector3 uniform_hemisphere_sample();

// Random direction sampled uniformly on unit hemisphere for
// phong lobule
Vector3 phong_uniform_hemisphere_sample(float alpha);