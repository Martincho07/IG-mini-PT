/*********************************************************************************
 * Color
 *
 * File: color.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "color.hpp"
#include "math.h"

RGB round(const RGB &c) {
    return RGB(round(c.r), round(c.g), round(c.b));
}
