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

void clamping(Image &img) {
    for (RGB &pixel : img.v) {
        if (pixel.r > 255)
            pixel.r = 255;

        if (pixel.g > 255)
            pixel.g = 255;

        if (pixel.b > 255)
            pixel.b = 255;
    }
};

void equalization(Image &img){};

void equalizeAndClamp(Image &img){};

void gammaCurve(Image &img){};

void clampAndGammaCurve(Image &img){};

void toDisk(Image &img) {
    for (RGB &pixel : img.v)
        pixel = pixel * (img.c / img.m);
};
