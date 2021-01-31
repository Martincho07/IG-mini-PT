/*********************************************************************************
 * Event
 *
 * File: event.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 1/12/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

enum EVENT {
    EMISSION_EVENT,
    DIFFUSE_EVENT,
    SPECULAR_EVENT,
    REFRACTION_EVENT,
    DEAD_EVENT
};

EVENT random_event(float kd, float ks, float kt);
