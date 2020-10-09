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
#include "math.h"

void clamping(Image &img) {

    for (RGB &pixel : img.v) {

        if (pixel.r > 1.0f)
            pixel.r = 1.0f;

        if (pixel.g > 1.0f)
            pixel.g = 1.0f;

        if (pixel.b > 1.0f)
            pixel.b = 1.0f;
    }
};

void equalization(Image &img, float V){

    for (RGB &pixel : img.v){
        pixel = pixel / V;

    }

};

void equalizeAndClamp(Image &img,  float V){
    equalization(img, V);
    clamping(img);

};

void gammaCurve(Image &img, float V, float gamma){
    equalization(img, V);
    for (RGB &pixel : img.v)
        pixel = pixel ^ gamma;
};

void clampAndGammaCurve(Image &img, float V, float gamma){
    gammaCurve(img,V,gamma);
    clamping(img);

};
