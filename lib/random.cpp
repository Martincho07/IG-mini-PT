/*********************************************************************************
 * Random number generation functions 
 *
 * File: random.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 1/12/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "random.hpp"
#include "transform.hpp"

static thread_local std::random_device rd;                                   // obtain a random number from hardware
static thread_local std::mt19937 gen(rd());                                  // seed the generator
static thread_local std::uniform_real_distribution<float> distr(0.0f, 1.0f); // define the range

float random_float() {
    return distr(gen);
}

/* Scaling a number x in the range [a, b] to [min, max]:
 *
 *     f(x) = ((max-min)(x-a) / (b-a)) + min
 *
 */

float random_float(float n) {
    return n * distr(gen);
}

float random_float(float min, float max) {
    return (max - min) * distr(gen) + min;
}

Vector3 uniform_hemisphere_sample() {
    float inclination = random_float(0.00001, 1.57079);
    float azimuth = random_float(0.00001, 6.28318);

    Vector3 direction(0.0f, 1.0f, 0.0f);

    return (rotationY(azimuth) * rotationZ(inclination))(direction);
}