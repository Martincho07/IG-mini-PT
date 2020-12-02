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

#include "BRDF.hpp"
#include "geometry.hpp"

enum EVENT {
    DIFFUSE,
    SPECULAR,
    REFRACTION,
    DEAD
};

EVENT randomEvent(const BRDF &material);