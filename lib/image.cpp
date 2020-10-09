/*********************************************************************************
 * Image
 *
 * File: image.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 6/10/2020
 * Coms: Informática Gráfica, 2020-2021
 **********************************************************************************/

#include "image.hpp"

const int LDR_LIMIT = 255;

void clamping(Image &img) {

    img.m = 1.0f;

    for (RGB &pixel : img.v) {
        if (pixel.r > 1.0f)
            pixel.r = 1.0f;

        if (pixel.g > 1.0f)
            pixel.g = 1.0f;

        if (pixel.b > 1.0f)
            pixel.b = 1.0f;
    }
};

void equalization(Image &img){};

void equalizeAndClamp(Image &img){};

void gammaCurve(Image &img){};

void clampAndGammaCurve(Image &img){};

void toDisk(Image &img) {
    for (RGB &pixel : img.v)
        pixel = pixel * (LDR_LIMIT / img.m);
};
