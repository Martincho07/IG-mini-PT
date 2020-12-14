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

#include "Vector3.h"

// Return a random real number between 0 and 1
Real random_real();

// Return a random real number between 0 and <n>
Real random_real(Real n);

// Return a random real number between <min> and <max>
Real random_real(Real min, Real max);

// Return a random real number between 0 and 1
int random_int();

// Return a random real number between 0 and <n>
int random_int(int n);

// Return a random real number between <min> and <max>
int random_int(int min, int max);

// Sampling funcions

// Random direction sampled uniformly on unit hemisphere
Vector3 uniform_sphere_sample();
