/*********************************************************************************
 * Image
 *
 * File: image.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#pragma once

#include "color.hpp"

#include <fstream>
#include <string>
#include <vector>

struct Image {

    std::vector<RGB> v;
    float m;
    float c;
    int width;
    int height;

    Image(){};

    // Constructors
    Image(const std::vector<RGB> _v, float _c, float _m, int _width, int _height)
        : v(_v), c(_c), m(_m), width(_width), height(_height){};

    // Tone mapping functions
    void clamping(){};

    void equalization(){};

    void equalizeAndClamp(){};

    void gammaCurve(){};

    void clampAndGammaCurve(){};
};
