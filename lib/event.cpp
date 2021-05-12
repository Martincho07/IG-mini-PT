/*********************************************************************************
 * Event
 *
 * File: event.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 1/12/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "event.hpp"
#include "random.hpp"

EVENT random_event(float max_kd, float max_ks, float max_kt) {
    // Russian roulette

    // Choose a number between 0 - 1
    float rand = random_float();

    // Return the event that corresponds to the random number
    if (rand < max_kd) {
        return DIFFUSE_EVENT;
    } else if (rand < max_kd + max_ks) {
        return SPECULAR_EVENT;
    } else if (rand < max_kd + max_ks + max_kt) {
        return REFRACTION_EVENT;
    } else {
        return DEAD_EVENT;
    }
}
