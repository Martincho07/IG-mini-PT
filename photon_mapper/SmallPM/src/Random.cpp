/*********************************************************************************
 * Random number generation functions 
 *
 * File: random.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 1/12/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "Random.h"

#include <random>
#include <cmath>

static thread_local std::random_device rd; // obtain a random number from hardware
static thread_local std::mt19937 gen(rd()); // seed the generator
static thread_local std::uniform_real_distribution<Real> distr(0.0f, 1.0f); // define the range

Real random_real()
{
    return distr(gen);
}

/* Scaling a number x in the range [a, b] to [min, max]:
 *
 *     f(x) = ((max-min)(x-a) / (b-a)) + min
 *
 */

Real random_real(Real n)
{
    return n * distr(gen);
}

Real random_real(Real min, Real max)
{
    return (max - min) * distr(gen) + min;
}

int random_int()
{
    return distr(gen);
}

int random_int(int n)
{
    return n * distr(gen);
}

int random_int(int min, int max)
{
    return (max - min) * distr(gen) + min;
}

Vector3 uniform_sphere_sample()
{
    float inclination = acosf(2 * random_real() - 1); // theta
    // float inclination = M_2_PI * random_real();           // theta
    float azimuth = M_2_PI * random_real(); // phi

    return Vector3(sinf(inclination) * sinf(azimuth), sinf(inclination) * cosf(azimuth), cosf(inclination));
    // return Vector3(sinf(inclination) * cosf(azimuth), sinf(inclination) * sinf(azimuth), cosf(inclination));
}

Vector3 _uniform_sphere_sample()
{
    Real x, y, z;
    do
    {
        x = random_real(-1, 1);
        y = random_real(-1, 1);
        z = random_real(-1, 1);
    } while (pow(x, 2) + pow(y, 2) + pow(z, 2) > 1);
    return Vector3(x, y, z);
}
